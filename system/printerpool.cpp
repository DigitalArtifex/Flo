#include "printerpool.h"
#include "../types/printer.h"
#include "../system/settings.h"

QMap<QString,Printer*> PrinterPool::_printerPool;
PrinterPool *PrinterPool::_instance = nullptr;

PrinterPool::PrinterPool() : QObject()
{

}

Printer *PrinterPool::getPrinterById(QString id)
{
    if(_printerPool.contains(id))
        return _printerPool[id];
    else
        return nullptr;
}

void PrinterPool::addPrinter(PrinterDefinition definition)
{
    Printer *printer = new Printer(definition);
    connect(printer, SIGNAL(printerError(QString,QString,Printer*)), _instance, SLOT(on_printerError(QString,QString,Printer*)));

    if(definition.autoConnect)
        printer->connectMoonraker();

    _printerPool.insert(definition.id,printer);
    Settings::addPrinter(definition);

    instance()->on_printerAdded(printer);
}

void PrinterPool::removePrinter(PrinterDefinition definition)
{
    Printer *printer = _printerPool[definition.id];
    _printerPool.remove(definition.id);

    delete printer;
    Settings::removePrinter(definition);

    instance()->on_printerRemoved(printer);
}

void PrinterPool::updatePrinter(PrinterDefinition definition)
{
    if(_printerPool.contains(definition.id))
    {
        _printerPool[definition.id]->update(definition);
        Settings::updatePrinter(definition);
        Settings::save();
    }
}

void PrinterPool::loadPrinters(QObject *parent)
{
    PrinterDefinitionList printerDefinitions = Settings::printers();
    bool hasDefault = false;

    foreach(PrinterDefinition definition, printerDefinitions)
    {
        if(definition.id.isEmpty())
            continue;

        if(_printerPool.contains(definition.id))
            continue;

        if(definition.defaultPrinter && !hasDefault)
            hasDefault = true;
        else if(definition.defaultPrinter)
            definition.defaultPrinter = false;

        Printer *printer = new Printer(definition, parent);
        connect(printer, SIGNAL(printerError(QString,QString,Printer*)), _instance, SLOT(on_printerError(QString,QString,Printer*)));
        connect(printer->currentJob(), SIGNAL(started(PrintJob*)), _instance, SLOT(on_printJob_started(PrintJob*)));
        connect(printer->currentJob(), SIGNAL(finished(PrintJob*)), _instance, SLOT(on_printJob_finished(PrintJob*)));

        if(definition.autoConnect)
            printer->connectMoonraker();

        _printerPool.insert(definition.id,printer);

        instance()->on_printerAdded(printer);
    }

    if(!hasDefault && !_printerPool.isEmpty())
    {
        Settings::setDefaultPrinter(_printerPool[0]->definition());
    }
}

bool PrinterPool::contains(QString id)
{
    return _printerPool.contains(id);
}

long PrinterPool::printersOnline()
{
    long online = 0;
    QStringList keys = _printerPool.keys();

    foreach(QString key, keys)
    {
        if(_printerPool[key]->status() != Printer::Offline)
            online++;
    }

    return online;
}

long PrinterPool::printersAvailable()
{
    return _printerPool.count();
}

long PrinterPool::printersRunning()
{
    long running = 0;
    QStringList keys = _printerPool.keys();

    foreach(QString key, keys)
    {
        if(_printerPool[key]->status() == Printer::Printing)
            running++;
        else if(_printerPool[key]->status() == Printer::Paused)
                running++;
    }

    return running;
}

QList<PrintJob *> PrinterPool::printJobs()
{
    QList<PrintJob*> jobs;
    QStringList keys = _printerPool.keys();

    foreach(QString key, keys)
    {
        if(_printerPool[key]->status() == Printer::Printing)
            jobs.append(_printerPool[key]->currentJob());
        else if(_printerPool[key]->status() == Printer::Paused)
            jobs.append(_printerPool[key]->currentJob());
    }

    return jobs;
}

PrinterPool *PrinterPool::instance()
{
    if(_instance == nullptr)
        _instance = new PrinterPool();

    return _instance;
}

void PrinterPool::on_printerAdded(Printer *printer)
{
    emit(printerAdded(printer));
}

void PrinterPool::on_printerRemoved(Printer *printer)
{
    emit(printerRemoved(printer));
}

void PrinterPool::on_printerUpdated(Printer *printer)
{
    emit(printerUpdated(printer));
}

void PrinterPool::on_printerError(QString title, QString message, Printer *printer)
{
    emit printerError(title,message,printer);
}

void PrinterPool::on_printJob_started(PrintJob *printJob)
{
    emit printJobStarted(printJob);
}

void PrinterPool::on_printJob_finished(PrintJob *printJob)
{
    emit printJobFinished(printJob);
}
