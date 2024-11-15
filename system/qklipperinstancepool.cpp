#include "qklipperinstancepool.h"

QMap<QString, QKlipperInstance*> QKlipperInstancePool::m_instanceMap;
QKlipperInstancePool *QKlipperInstancePool::m_instance = nullptr;
QMultiMap<QString, QKlipperPrintJob*> QKlipperInstancePool::m_jobMap;

QKlipperInstancePool::QKlipperInstancePool(QObject *parent)
    : QObject{parent}
{

}

QKlipperInstance *QKlipperInstancePool::klipperInstance(const QString &id)
{
    if(m_instanceMap.contains(id))
        return m_instanceMap[id];

    return nullptr;
}

QKlipperInstanceList QKlipperInstancePool::klipperInstances()
{
    return m_instanceMap.values();
}

QStringList QKlipperInstancePool::klipperInstanceIds()
{
    QStringList ids;
    QMapIterator<QString,QKlipperInstance*> iterator(m_instanceMap);

    while(iterator.hasNext())
    {
        iterator.next();
        ids += iterator.value()->id();
    }

    return ids;
}

void QKlipperInstancePool::addInstance(QKlipperInstance *instance)
{
    pool()->add(instance);
    connect(instance, SIGNAL(printJobAdded(QKlipperInstance*,QKlipperPrintJob*)), m_instance, SLOT(onPrintJobAdded(QKlipperInstance*,QKlipperPrintJob*)));
    connect(instance, SIGNAL(printJobRemoved(QKlipperInstance*,QKlipperPrintJob*)), m_instance, SLOT(onPrintJobRemoved(QKlipperInstance*,QKlipperPrintJob*)));
}

void QKlipperInstancePool::removeInstance(QKlipperInstance *instance)
{
    pool()->remove(instance);
}

qint64 QKlipperInstancePool::klipperInstancesOnline()
{
    qint64 online = 0;
    QMapIterator<QString,QKlipperInstance*> iterator(m_instanceMap);

    while(iterator.hasNext())
    {
        iterator.next();

        if(iterator.value()->console()->isConnected())
            online++;
    }

    return online;
}

QKlipperInstancePool *QKlipperInstancePool::pool()
{
    if(!m_instance)
        m_instance = new QKlipperInstancePool();

    return m_instance;
}

QKlipperInstance *QKlipperInstancePool::operator[](const QString &name)
{
    return m_instanceMap[name];
}

QList<QKlipperPrintJob *> QKlipperInstancePool::printJobs()
{
    return m_jobMap.values();
}

QMultiMap<QString, QKlipperPrintJob *> QKlipperInstancePool::printJobMap()
{
    return m_jobMap;
}

void QKlipperInstancePool::onPrintJobAdded(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    QList<QKlipperPrintJob*> jobs = m_jobMap.values(instance->id());

    if(!jobs.contains(job))
    {
        m_jobMap.insert(instance->id(), job);
        emit printJobAdded(instance, job);
    }
}

void QKlipperInstancePool::onPrintJobRemoved(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    QList<QKlipperPrintJob*> jobs = m_jobMap.values(instance->id());

    if(jobs.contains(job))
    {
        m_jobMap.remove(instance->id(), job);
        emit printJobRemoved(instance, job);
    }
}

void QKlipperInstancePool::onInstanceError(QKlipperInstance *instance, QKlipperError &error)
{
    emit instanceError(instance, error);
}

void QKlipperInstancePool::add(QKlipperInstance *instance)
{
    if(!m_instanceMap.contains(instance->id()))
    {
        m_instanceMap.insert(instance->id(), instance);

        emit instanceAdded(instance);
    }
}

void QKlipperInstancePool::remove(QKlipperInstance *instance)
{
    if(m_instanceMap.contains(instance->id()))
    {
        m_instanceMap.remove(instance->id());

        emit instanceRemoved(instance);
    }
}
