#include "flo.h"

Settings *Flo::m_settings = nullptr;
QKlipperInstancePool *Flo::m_printerPool = nullptr;
Flo *Flo::m_instance = nullptr;

Flo::Flo(QObject *parent)
    : QObject{parent}
{
    m_settings = Settings::instance();
    m_printerPool = QKlipperInstancePool::pool();
}

QString Flo::generatId()
{
    return QUuid::createUuid().toString();
}

Flo *Flo::instance()
{
    if(m_instance == nullptr)
        m_instance = new Flo();

    return m_instance;
}

void Flo::start()
{
    on_loading();
    loadingProgress(QString("Loading Settings"), 0);

    Settings::load();

    //load the printers

    on_loadingFinished();
}

QKlipperInstancePool *Flo::printerPool()
{
    return m_printerPool;
}

Settings *Flo::settings()
{
    return m_settings;
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
