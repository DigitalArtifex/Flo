#include "system.h"

System::System(QObject *parent)
    : QObject{parent}
{
}

System::~System()
{
}

void System::setCpuCount(qint16 count)
{
    _cpuCount = count;
}

void System::setCpuList(QList<qreal> cpus)
{
    _cpuUsages.clear();
    _cpuUsages.append(cpus);
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

void System::setMemoryUsage(qint64 memory)
{
    _memoryUsage = memory;
}

void System::setMemoryCapacity(qint64 memory)
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

qint64 System::driveCapacity() const
{
    return _driveCapacity;
}

void System::setDriveCapacity(qint64 driveCapacity)
{
    _driveCapacity = driveCapacity;
}

qint64 System::driveUsage() const
{
    return _driveUsage;
}

void System::setDriveUsage(qint64 driveUsage)
{
    _driveUsage = driveUsage;
}

qint64 System::driveFree() const
{
    return _driveFree;
}

void System::setDriveFree(qint64 driveFree)
{
    _driveFree = driveFree;
}

QStringList System::availableServices() const
{
    return _availableServices;
}

void System::setAvailableServices(const QStringList &availableServices)
{
    _availableServices = availableServices;
}

QMap<QString, System::ServiceState> System::serviceStates() const
{
    return _serviceStates;
}

QString System::pythonVersion() const
{
    return _pythonVersion;
}

void System::setPythonVersion(const QString &pythonVersion)
{
    _pythonVersion = pythonVersion;
}

System::CpuInfo System::cpuInfo() const
{
    return _cpuInfo;
}

void System::setCpuInfo(CpuInfo cpuInfo)
{
    _cpuInfo = cpuInfo;
}

System::DistributionInfo System::distributionInfo() const
{
    return _distributionInfo;
}

void System::setDistributionInfo(const DistributionInfo &distributionInfo)
{
    _distributionInfo = distributionInfo;
}

System::VirtualizationState System::virtualizationState() const
{
    return _virtualizationState;
}

void System::setVirtualizationState(const VirtualizationState &virtualizationState)
{
    _virtualizationState = virtualizationState;
}

QMap<QString, System::NetworkInterface> System::networkInterfaces() const
{
    return _networkInterfaces;
}

void System::setNetworkInterfaces(const QMap<QString, NetworkInterface> &networkInterfaces)
{
    _networkInterfaces = networkInterfaces;
}

QMap<QString, System::CanBusDevice> System::canBus() const
{
    return _canBus;
}

void System::setCanBus(const QMap<QString, CanBusDevice> &canBus)
{
    _canBus = canBus;
}

System::SdInfo System::sdInfo() const
{
    return _sdInfo;
}

void System::setSdInfo(const SdInfo &sdInfo)
{
    _sdInfo = sdInfo;
}
