#include "flo.h"

PrinterPool *Flo::_printerPool = nullptr;
Settings *Flo::_settings = nullptr;

Flo *Flo::_instance = nullptr;

Flo::Flo(QObject *parent)
    : QObject{parent}
{
    _settings = Settings::instance();
    _printerPool = PrinterPool::instance();
}

QString Flo::generatId()
{
    return QUuid::createUuid().toString();
}

Flo *Flo::instance()
{
    if(_instance == nullptr)
        _instance = new Flo();

    return _instance;
}

void Flo::start(QObject *parent)
{
        on_loading();
        loadingProgress(QString("Loading Settings"), 0);

        Settings::load();

        loadingProgress(QString("Loading Printers"), 30);
        PrinterPool::loadPrinters(parent);

        on_loadingFinished();
}

PrinterPool *Flo::printerPool()
{
    return _printerPool;
}

Settings *Flo::settings()
{
    return _settings;
}

void Flo::on_loading()
{
    emit(loading());
}

void Flo::on_loadingProgress(QString message, qreal progress)
{
    emit(loadingProgress(message, progress));
}

void Flo::on_loadingFinished()
{
    emit(loadingFinished());
}
