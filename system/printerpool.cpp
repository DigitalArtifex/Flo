#include "printerpool.h"
#include "../types/printer.h"
#include "../system/settings.h"

QMap<QString,Printer*> PrinterPool::m_printerPool;
PrinterPool *PrinterPool::m_instance = nullptr;

PrinterPool::PrinterPool() : QObject()
{

}

Printer *PrinterPool::getPrinterById(QString id)
{
    if(m_printerPool.contains(id))
        return m_printerPool[id];
    else
        return nullptr;
}

QStringList PrinterPool::keys()
{
    return m_printerPool.keys();
}

void PrinterPool::addPrinter(PrinterDefinition definition)
{
    Printer *printer = new Printer(definition);
    connect(printer, SIGNAL(printerError(QString,QString,Printer*)), m_instance, SLOT(on_printerError(QString,QString,Printer*)));

    if(definition.autoConnect)
        printer->connectMoonraker();

    m_printerPool.insert(definition.id,printer);
    Settings::addPrinter(definition);

    instance()->on_printerAdded(printer);
}

void PrinterPool::removePrinter(PrinterDefinition definition)
{
    Printer *printer = m_printerPool[definition.id];
    m_printerPool.remove(definition.id);

    delete printer;
    Settings::removePrinter(definition);

    instance()->on_printerRemoved(printer);
}

void PrinterPool::updatePrinter(PrinterDefinition definition)
{
    if(m_printerPool.contains(definition.id))
    {
        //m_printerPool[definition.id]->update(definition);
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

        if(m_printerPool.contains(definition.id))
            continue;

        if(definition.defaultPrinter && !hasDefault)
            hasDefault = true;
        else if(definition.defaultPrinter)
            definition.defaultPrinter = false;

        Printer *printer = new Printer(definition, parent);
        connect(printer, SIGNAL(printerError(QString,QString,Printer*)), m_instance, SLOT(on_printerError(QString,QString,Printer*)));
        connect(printer->currentJob(), SIGNAL(started(PrintJob*)), m_instance, SLOT(on_printJob_started(PrintJob*)));
        connect(printer->currentJob(), SIGNAL(finished(PrintJob*)), m_instance, SLOT(on_printJob_finished(PrintJob*)));

        if(definition.autoConnect)
            printer->connectMoonraker();

        m_printerPool.insert(definition.id,printer);

        instance()->on_printerAdded(printer);
    }

    if(!hasDefault && !m_printerPool.isEmpty())
    {
        Settings::setDefaultPrinter(m_printerPool.first()->definition());
    }
}

bool PrinterPool::contains(QString id)
{
    return m_printerPool.contains(id);
}

long PrinterPool::printersOnline()
{
    long online = 0;
    QStringList keys = m_printerPool.keys();

    foreach(QString key, keys)
    {
        if(m_printerPool[key]->status() != Printer::Offline)
            online++;
    }

    return online;
}

long PrinterPool::printersAvailable()
{
    return m_printerPool.count();
}

long PrinterPool::printersRunning()
{
    long running = 0;
    QStringList keys = m_printerPool.keys();

    foreach(QString key, keys)
    {
        if(m_printerPool[key]->status() == Printer::Printing)
            running++;
        else if(m_printerPool[key]->status() == Printer::Paused)
                running++;
    }

    return running;
}

QList<PrintJob *> PrinterPool::printJobs()
{
    QList<PrintJob*> jobs;
    QStringList keys = m_printerPool.keys();

    foreach(QString key, keys)
    {
        if(m_printerPool[key]->status() == Printer::Printing)
            jobs.append(m_printerPool[key]->currentJob());
        else if(m_printerPool[key]->status() == Printer::Paused)
            jobs.append(m_printerPool[key]->currentJob());
    }

    return jobs;
}

PrinterPool *PrinterPool::instance()
{
    if(m_instance == nullptr)
        m_instance = new PrinterPool();

    return m_instance;
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
