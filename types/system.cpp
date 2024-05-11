#include "system.h"

System::System(QObject *parent)
    : QObject{parent}
{
}

System::~System()
{
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

QList<System::MoonrakerStatsEntry> System::moonrakerStats() const
{
    return _moonrakerStats;
}

QMap<QString, System::NetworkStatsEntry> System::networkStats() const
{
    return _networkStats;
}

System::ThrottleState System::throttleState() const
{
    return _throttleState;
}

void System::setThrottleState(const ThrottleState &throttleState)
{
    _throttleState = throttleState;
}

System::MemoryStats System::memoryStats() const
{
    return _memoryStats;
}

void System::setMemoryStats(const MemoryStats &memoryStats)
{
    _memoryStats = memoryStats;
}

qreal System::uptime() const
{
    return _uptime;
}

void System::setUptime(qreal uptime)
{
    _uptime = uptime;
}

qint32 System::connectionCount() const
{
    return _connectionCount;
}

void System::setConnectionCount(qint32 connectionCount)
{
    _connectionCount = connectionCount;
}

QList<System::UsbPeripheral> System::usbPeripherals() const
{
    return _usbPeripherals;
}

QList<System::SerialPeripheral> System::serialPeripherals() const
{
    return _serialPeripherals;
}

QList<System::V412Device> System::v412Devices() const
{
    return _v412Devices;
}

QList<System::LibcameraDevice> System::libcameraDevices() const
{
    return _libcameraDevices;
}

QMap<qint32, System::CanBus> System::canBusses() const
{
    return _canBusses;
}

System::AccessDetails System::accessDetails() const
{
    return _accessDetails;
}

void System::setAccessDetails(const AccessDetails &accessDetails)
{
    _accessDetails = accessDetails;
}

QList<System::User> System::userList() const
{
    return _userList;
}

QList<System::Webcam> System::webcams() const
{
    return _webcams;
}

QList<System::Announcement> System::announcements() const
{
    return _announcements;
}

System::UpdateState System::updateState() const
{
    return _updateState;
}

void System::setUpdateState(const UpdateState &updateState)
{
    _updateState = updateState;
}

System::JobQueue System::jobQueue() const
{
    return _jobQueue;
}

void System::setJobQueue(const JobQueue &jobQueue)
{
    _jobQueue = jobQueue;
}

System::VirtualSDCard System::virtualSDCard() const
{
    return _virtualSDCard;
}

void System::setVirtualSDCard(const VirtualSDCard &virtualSDCard)
{
    _virtualSDCard = virtualSDCard;
}
