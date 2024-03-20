#include "system.h"

System::System(QObject *parent)
    : QObject{parent}
{

}

void System::setCpuCount(int count)
{
    _cpuCount = count;
}

void System::setCpuList(QList<qreal> cpus)
{
    _cpuUsages.clear();
    _cpuUsages.append(cpus);
}

void System::setCpuInfo(QString info)
{
    _cpuInfo = info;
}

int System::cpuCount()
{
    return _cpuCount;
}

qreal System::cpuLoad()
{
    qreal load = 0;

    foreach(qreal i, _cpuUsages)
        load += i;

    load /= _cpuCount;

    return load;
}

QString System::cpuInfo()
{
    return _cpuInfo;
}

void System::setMemoryUsage(long memory)
{
    _memoryUsage = memory;
}

void System::setMemoryCapacity(long memory)
{
    _memoryCapacity = memory;
}

qreal System::memoryCapacity()
{
    return _memoryCapacity;
}

qreal System::memoryUsage()
{
    return _memoryUsage;
}

qreal System::memoryLoad()
{
    return (_memoryCapacity/_memoryUsage);
}

void System::setHostname(QString hostname)
{
    _hostname = hostname;
}

QString System::hostname()
{
    return _hostname;
}
