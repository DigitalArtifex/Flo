#include "system.h"
#include "printer.h"

System::System(Printer *printer, QObject *parent)
    : QObject{parent}
{
    m_console = printer->console();
}

System::~System()
{

}

void System::setHostname(QString hostname)
{
    m_hostname = hostname;
}

QString System::hostname()
{
    return m_hostname;
}

qint64 System::driveCapacity() const
{
    return m_driveCapacity;
}

void System::setDriveCapacity(qint64 driveCapacity)
{
    m_driveCapacity = driveCapacity;
}

qint64 System::driveUsage() const
{
    return m_driveUsage;
}

void System::setDriveUsage(qint64 driveUsage)
{
    m_driveUsage = driveUsage;
}

qint64 System::driveFree() const
{
    return m_driveFree;
}

void System::setDriveFree(qint64 driveFree)
{
    m_driveFree = driveFree;
}

QStringList System::availableServices() const
{
    return m_serviceStates.keys();
}

void System::setAvailableServices(const QStringList &availableServices)
{
    m_availableServices = availableServices;
}

QMap<QString, System::ServiceState> System::serviceStates() const
{
    return m_serviceStates;
}

QString System::pythonVersion() const
{
    return m_pythonVersion;
}

void System::setPythonVersion(const QString &pythonVersion)
{
    m_pythonVersion = pythonVersion;
}

System::CpuInfo System::cpuInfo() const
{
    return m_cpuInfo;
}

void System::setCpuInfo(CpuInfo cpuInfo)
{
    m_cpuInfo = cpuInfo;
}

System::DistributionInfo System::distributionInfo() const
{
    return m_distributionInfo;
}

void System::setDistributionInfo(const DistributionInfo &distributionInfo)
{
    m_distributionInfo = distributionInfo;
}

System::VirtualizationState System::virtualizationState() const
{
    return m_virtualizationState;
}

void System::setVirtualizationState(const VirtualizationState &virtualizationState)
{
    m_virtualizationState = virtualizationState;
}

QMap<QString, System::NetworkInterface> System::networkInterfaces() const
{
    return m_networkInterfaces;
}

void System::setNetworkInterfaces(const QMap<QString, NetworkInterface> &networkInterfaces)
{
    m_networkInterfaces = networkInterfaces;
}

QMap<QString, System::CanBusDevice> System::canBus() const
{
    return m_canBus;
}

void System::setCanBus(const QMap<QString, CanBusDevice> &canBus)
{
    m_canBus = canBus;
}

System::SdInfo System::sdInfo() const
{
    return m_sdInfo;
}

void System::setSdInfo(const SdInfo &sdInfo)
{
    m_sdInfo = sdInfo;

    emit sdInfoUpdate();
}

QList<System::MoonrakerStatsEntry> System::moonrakerStats() const
{
    return m_moonrakerStats;
}

QMap<QString, System::NetworkStatsEntry> System::networkStats() const
{
    return m_networkStats;
}

System::ThrottleState System::throttleState() const
{
    return m_throttleState;
}

void System::setThrottleState(const ThrottleState &throttleState)
{
    m_throttleState = throttleState;
}

System::MemoryStats System::memoryStats() const
{
    return m_memoryStats;
}

void System::setMemoryStats(const MemoryStats &memoryStats)
{
    m_memoryStats = memoryStats;
}

qreal System::uptime() const
{
    return m_uptime;
}

void System::setUptime(qreal uptime)
{
    m_uptime = uptime;
}

qint32 System::connectionCount() const
{
    return m_connectionCount;
}

void System::setConnectionCount(qint32 connectionCount)
{
    m_connectionCount = connectionCount;
}

QList<System::UsbPeripheral> System::usbPeripherals() const
{
    return m_usbPeripherals;
}

QList<System::SerialPeripheral> System::serialPeripherals() const
{
    return m_serialPeripherals;
}

QList<System::V412Device> System::v412Devices() const
{
    return m_v412Devices;
}

QList<System::LibcameraDevice> System::libcameraDevices() const
{
    return m_libcameraDevices;
}

QMap<qint32, System::CanBus> System::canBusses() const
{
    return m_canBusses;
}

System::AccessDetails System::accessDetails() const
{
    return m_accessDetails;
}

void System::setAccessDetails(const AccessDetails &accessDetails)
{
    m_accessDetails = accessDetails;
}

QList<System::User> System::userList() const
{
    return m_userList;
}

QList<System::Webcam> System::webcams() const
{
    return m_webcams;
}

QList<System::Announcement> System::announcements() const
{
    return m_announcements;
}

System::UpdateState System::updateState() const
{
    return m_updateState;
}

void System::setUpdateState(const UpdateState &updateState)
{
    m_updateState = updateState;

    emit updateStateUpdate();
}

System::JobQueue System::jobQueue() const
{
    return m_jobQueue;
}

void System::setJobQueue(const JobQueue &jobQueue)
{
    m_jobQueue = jobQueue;
}

System::VirtualSDCard System::virtualSDCard() const
{
    return m_virtualSDCard;
}

void System::setVirtualSDCard(const VirtualSDCard &virtualSDCard)
{
    m_virtualSDCard = virtualSDCard;

    emit virtualSDCardUpdate();
}

System::MCU System::mcu() const
{
    return m_mcu;
}

void System::setMcu(const MCU &mcu)
{
    m_mcu = mcu;

    emit mcuChanged();
}

System::SafeZHome System::safeZHome() const
{
    return m_safeZHome;
}

void System::setSafeZHome(const SafeZHome &safeZHome)
{
    m_safeZHome = safeZHome;
}

void System::restart()
{
    if(Printer *printer = qobject_cast<Printer*>(parent()))
    {
        qDebug() << printer->name() + QString(": Restarting firmware");
        printer->console()->restartFirmware();
    }
}

void System::startService(QString service)
{
    if(m_console->isMoonrakerConnected())
        m_console->machineServiceStart(service);
}

void System::stopService(QString service)
{
    if(m_console->isMoonrakerConnected())
        m_console->machineServiceStop(service);
}

void System::restartService(QString service)
{
    if(m_console->isMoonrakerConnected())
        m_console->machineServiceRestart(service);
}

void System::updateServices()
{
    if(m_console->isMoonrakerConnected())
        m_console->machineSystemInfo();
}

void System::setServiceStates(QList<ServiceState> serviceStates)
{
    m_serviceStates.clear();

    foreach(ServiceState state, serviceStates)
        m_serviceStates[state.name] = state;

    emit serviceStatesUpdate();
}

void System::updateProcStats()
{
    m_console->machineProcStats();
}

void System::createUser(QString username, QString password)
{
    m_console->accessCreateUser(username, password);
}

void System::update()
{
    emit updated();
}

void System::setUserList(const QList<User> &userList)
{
    m_userList = userList;

    emit userListChanged();
}

void System::setNetworkStats(const QMap<QString, NetworkStatsEntry> &NetworkStats)
{
    m_networkStats = NetworkStats;

    emit networkStatsChanged();
}
