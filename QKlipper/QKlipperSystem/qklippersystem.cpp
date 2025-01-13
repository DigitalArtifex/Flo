#include "qklippersystem.h"
#include <QKlipper/qklipper.h>

QKlipperSystem::QKlipperSystem(QObject *parent)
    : QObject{parent}
{
    m_throttleState = new QKlipperThrottleState(this);
    m_memoryStats = new QKlipperMemoryStats(this);
    m_virtualizationState = new QKlipperVirtualizationState(this);
    m_canBus = new QKlipperCanBus(this);
    m_updateManager = new QKlipperUpdateManager(this);
    m_virtualSDCard = new QKlipperVirtualSDCard(this);
}

QKlipperSystem::~QKlipperSystem()
{
    if(m_throttleState)
        m_throttleState->deleteLater();
    if(m_memoryStats)
        m_memoryStats->deleteLater();
    if(m_virtualizationState)
        m_virtualizationState->deleteLater();
    if(m_canBus)
        m_canBus->deleteLater();
    if(m_updateManager)
        m_updateManager->deleteLater();
    if(m_virtualSDCard)
        m_virtualSDCard->deleteLater();

    foreach(QKlipperCanBus *bus, m_canBusses)
        bus->deleteLater();
}

qint64 QKlipperSystem::driveCapacity() const
{
    return m_driveCapacity;
}

void QKlipperSystem::setDriveCapacity(qint64 driveCapacity)
{
    if (m_driveCapacity == driveCapacity)
        return;

    m_driveCapacity = driveCapacity;
    emit driveCapacityChanged();
}


bool QKlipperSystem::stopService(QString serviceName)
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(parent());
    QKlipperConsole *console = instance ? instance->console() : nullptr;

    if(console && console->isConnected())
    {
        QKlipperError error;
        console->machineServiceStop(serviceName, &error);

        if(error.type() == QKlipperError::NoError)
            return true;
    }

    return false;
}

bool QKlipperSystem::startService(QString serviceName)
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(parent());
    QKlipperConsole *console = instance ? instance->console() : nullptr;

    if(console && console->isConnected())
    {
        QKlipperError error;
        console->machineServiceStart(serviceName, &error);

        if(error.type() == QKlipperError::NoError)
            return true;
    }

    return false;
}

bool QKlipperSystem::restartService(QString serviceName)
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(parent());
    QKlipperConsole *console = instance ? instance->console() : nullptr;

    if(console && console->isConnected())
    {
        QKlipperError error;
        console->machineServiceRestart(serviceName, &error);

        if(error.type() == QKlipperError::NoError)
            return true;
    }

    return false;
}

void QKlipperSystem::shutdown()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(parent());
    QKlipperConsole *console = instance ? instance->console() : nullptr;

    if(console)
    {
        QKlipperError error;
        console->machineShutdown(&error);

        if(error.type() != QKlipperError::NoError) return;

        emit machineShutdown();
    }
}

void QKlipperSystem::restart()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(parent());
    QKlipperConsole *console = instance ? instance->console() : nullptr;

    if(console)
    {
        QKlipperError error;
        console->machineReboot(&error);

        if(error.type() != QKlipperError::NoError) return;

        emit machineRestart();
    }
}

QKlipperSystem::State QKlipperSystem::state() const
{
    return m_state;
}

void QKlipperSystem::setState(State state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged();
}

QKlipperUpdateManager *QKlipperSystem::updateManager() const
{
    return m_updateManager;
}

void QKlipperSystem::setUpdateManager(QKlipperUpdateManager *updateManager)
{
    if (m_updateManager == updateManager)
        return;

    m_updateManager = updateManager;
    emit updateManagerChanged();
}

qint64 QKlipperSystem::driveUsage() const
{
    return m_driveUsage;
}

void QKlipperSystem::setDriveUsage(qint64 driveUsage)
{
    if (m_driveUsage == driveUsage)
        return;

    m_driveUsage = driveUsage;
    emit driveUsageChanged();
}

qint64 QKlipperSystem::driveFree() const
{
    return m_driveFree;
}

void QKlipperSystem::setDriveFree(qint64 driveFree)
{
    if (m_driveFree == driveFree)
        return;
    m_driveFree = driveFree;
    emit driveFreeChanged();
}

QString QKlipperSystem::hostname() const
{
    return m_hostname;
}

void QKlipperSystem::setHostname(const QString &hostname)
{
    if (m_hostname == hostname)
        return;
    m_hostname = hostname;
    emit hostnameChanged();
}

QList<QKlipperMoonrakerStatsEntry> QKlipperSystem::moonrakerStats() const
{
    return m_moonrakerStats;
}

void QKlipperSystem::setMoonrakerStats(const QList<QKlipperMoonrakerStatsEntry> &moonrakerStats)
{
    bool changed = false;

    foreach(QKlipperMoonrakerStatsEntry entry, moonrakerStats)
    {
        if(!m_moonrakerStats.contains(entry))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_moonrakerStats = moonrakerStats;
    emit moonrakerStatsChanged();
}

QMap<QString, QKlipperNetworkStatsEntry> QKlipperSystem::networkStats() const
{
    return m_networkStats;
}

void QKlipperSystem::setNetworkStats(const QMap<QString, QKlipperNetworkStatsEntry> &networkStats)
{
    bool changed = false;
    QStringList keys = networkStats.keys();

    foreach(QString key, keys)
    {
        if(m_networkStats.contains(key))
        {
            if(m_networkStats[key] != networkStats[key])
            {
                changed = true;
                break;
            }
        }
        else
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_networkStats = networkStats;
    emit networkStatsChanged();
}

QKlipperThrottleState *QKlipperSystem::throttleState() const
{
    return m_throttleState;
}

void QKlipperSystem::setThrottleState(QKlipperThrottleState *throttleState)
{
    if (m_throttleState == throttleState)
        return;

    m_throttleState = throttleState;
    emit throttleStateChanged();
}

QKlipperMemoryStats *QKlipperSystem::memoryStats() const
{
    return m_memoryStats;
}

void QKlipperSystem::setMemoryStats(QKlipperMemoryStats *memoryStats)
{
    if (m_memoryStats == memoryStats)
        return;

    m_memoryStats = memoryStats;
    emit memoryStatsChanged();
}

qreal QKlipperSystem::uptime() const
{
    return m_uptime;
}

void QKlipperSystem::setUptime(qreal uptime)
{
    if (qFuzzyCompare(m_uptime, uptime))
        return;

    m_uptime = uptime;
    emit uptimeChanged();
}

qint32 QKlipperSystem::connectionCount() const
{
    return m_connectionCount;
}

void QKlipperSystem::setConnectionCount(qint32 connectionCount)
{
    if (m_connectionCount == connectionCount)
        return;

    m_connectionCount = connectionCount;
    emit connectionCountChanged();
}

QKlipperCpuInfo QKlipperSystem::cpuInfo() const
{
    return m_cpuInfo;
}

void QKlipperSystem::setCpuInfo(const QKlipperCpuInfo &cpuInfo)
{
    if (m_cpuInfo == cpuInfo)
        return;
    m_cpuInfo = cpuInfo;
    emit cpuInfoChanged();
}

QKlipperSdInfo QKlipperSystem::sdInfo() const
{
    return m_sdInfo;
}

void QKlipperSystem::setSdInfo(const QKlipperSdInfo &sdInfo)
{
    if (m_sdInfo == sdInfo)
        return;
    m_sdInfo = sdInfo;
    emit sdInfoChanged();
}

QKlipperDistributionInfo QKlipperSystem::distributionInfo() const
{
    return m_distributionInfo;
}

void QKlipperSystem::setDistributionInfo(const QKlipperDistributionInfo &distributionInfo)
{
    if (m_distributionInfo == distributionInfo)
        return;
    m_distributionInfo = distributionInfo;
    emit distributionInfoChanged();
}

QKlipperVirtualizationState *QKlipperSystem::virtualizationState() const
{
    return m_virtualizationState;
}

void QKlipperSystem::setVirtualizationState(QKlipperVirtualizationState *virtualizationState)
{
    if (m_virtualizationState == virtualizationState)
        return;
    m_virtualizationState = virtualizationState;
    emit virtualizationStateChanged();
}

QMap<QString, QKlipperNetworkInterface> QKlipperSystem::networkInterfaces() const
{
    return m_networkInterfaces;
}

void QKlipperSystem::setNetworkInterfaces(const QMap<QString, QKlipperNetworkInterface> &networkInterfaces)
{
    bool changed = false;
    QStringList keys = networkInterfaces.keys();

    foreach(QString key, keys)
    {
        if(m_networkInterfaces.contains(key))
        {
            if(m_networkInterfaces[key] != networkInterfaces[key])
            {
                changed = true;
                break;
            }
        }
        else
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_networkInterfaces = networkInterfaces;
    emit networkInterfacesChanged();
}

QKlipperCanBus *QKlipperSystem::canBus() const
{
    return m_canBus;
}

void QKlipperSystem::setCanBus(QKlipperCanBus *canBus)
{
    if (m_canBus == canBus)
        return;

    m_canBus = canBus;
    emit canBusChanged();
}

QStringList QKlipperSystem::availableServices() const
{
    return m_availableServices;
}

void QKlipperSystem::setAvailableServices(const QStringList &availableServices)
{
    if (m_availableServices == availableServices)
        return;

    m_availableServices = availableServices;
    emit availableServicesChanged();
}

void QKlipperSystem::addService(QKlipperService *state)
{
    if(m_services.contains(state->name()) && m_services[state->name()] != state)
    {
        QKlipperService *oldState = m_services[state->name()];
        m_services.remove(state->name());

        oldState->deleteLater();
    }

    m_services[state->name()] = state;

    emit servicesChanged();
}

void QKlipperSystem::deleteService(QString name)
{
    if(m_services.contains(name))
    {
        QKlipperService *oldState = m_services[name];
        m_services.remove(name);

        oldState->deleteLater();
    }
}

QKlipperService* QKlipperSystem::service(const QString &name) const
{
    if(m_services.contains(name))
        return m_services[name];

    return nullptr;
}

QList<QKlipperUsbPeripheral> QKlipperSystem::usbPeripherals() const
{
    return m_usbPeripherals;
}

void QKlipperSystem::setUsbPeripherals(const QList<QKlipperUsbPeripheral> &usbPeripherals)
{
    bool changed = false;

    foreach(QKlipperUsbPeripheral device, usbPeripherals)
    {
        if(!m_usbPeripherals.contains(device))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_usbPeripherals = usbPeripherals;
    emit usbPeripheralsChanged();
}

QList<QKlipperSerialPeripheral> QKlipperSystem::serialPeripherals() const
{
    return m_serialPeripherals;
}

void QKlipperSystem::setSerialPeripherals(const QList<QKlipperSerialPeripheral> &serialPeripherals)
{
    bool changed = false;

    foreach(QKlipperSerialPeripheral device, serialPeripherals)
    {
        if(!m_serialPeripherals.contains(device))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_serialPeripherals = serialPeripherals;
    emit serialPeripheralsChanged();
}

QList<QKlipperV412Device> QKlipperSystem::v412Devices() const
{
    return m_v412Devices;
}

void QKlipperSystem::setV412Devices(const QList<QKlipperV412Device> &v412Devices)
{
    bool changed = false;

    foreach(QKlipperV412Device device, v412Devices)
    {
        if(!m_v412Devices.contains(device))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_v412Devices = v412Devices;
    emit v412DevicesChanged();
}

QList<QKlipperLibcameraDevice> QKlipperSystem::libcameraDevices() const
{
    return m_libcameraDevices;
}

void QKlipperSystem::setLibcameraDevices(const QList<QKlipperLibcameraDevice> &libcameraDevices)
{
    bool changed = false;

    foreach(QKlipperLibcameraDevice device, libcameraDevices)
    {
        if(!m_libcameraDevices.contains(device))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_libcameraDevices = libcameraDevices;
    emit libcameraDevicesChanged();
}

QList<QKlipperWebcam> QKlipperSystem::webcams() const
{
    return m_webcams;
}

void QKlipperSystem::setWebcams(const QList<QKlipperWebcam> &webcams)
{
    bool changed = false;

    foreach(QKlipperWebcam device, webcams)
    {
        if(!m_webcams.contains(device))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_webcams = webcams;
    emit webcamsChanged();
}

QMap<qint32, QKlipperCanBus *> QKlipperSystem::canBusses() const
{
    return m_canBusses;
}

void QKlipperSystem::setCanBusses(const QMap<qint32, QKlipperCanBus *> &canBusses)
{
    if (m_canBusses == canBusses)
        return;

    m_canBusses = canBusses;
    emit canBussesChanged();
}

QKlipperVirtualSDCard *QKlipperSystem::virtualSDCard() const
{
    return m_virtualSDCard;
}

void QKlipperSystem::setVirtualSDCard(QKlipperVirtualSDCard *virtualSDCard)
{
    if (m_virtualSDCard == virtualSDCard)
        return;
    m_virtualSDCard = virtualSDCard;
    emit virtualSDCardChanged();
}

QString QKlipperSystem::pythonVersion() const
{
    return m_pythonVersion;
}

void QKlipperSystem::setPythonVersion(const QString &pythonVersion)
{
    if (m_pythonVersion == pythonVersion)
        return;
    m_pythonVersion = pythonVersion;
    emit pythonVersionChanged();
}

QKlipperSensorMap QKlipperSystem::sensors() const
{
    return m_sensors;
}

void QKlipperSystem::setSensors(const QKlipperSensorMap &sensors)
{
    if (m_sensors == sensors)
        return;

    m_sensors = sensors;
    emit sensorsChanged();
}

void QKlipperSystem::addSensor(QKlipperSensor *sensor)
{
    if(m_sensors.contains(sensor->id()))
        return;

    m_sensors.insert(sensor->id(), sensor);
    emit sensorsChanged();
}

QMap<QString, QKlipperService *> QKlipperSystem::services() const
{
    return m_services;
}

void QKlipperSystem::setServices(const QMap<QString, QKlipperService *> &services)
{
    if (m_services == services)
        return;

    m_services = services;
    emit servicesChanged();
}



QKlipperLedStripList QKlipperSystem::ledStrips() const
{
    return m_ledStrips;
}

void QKlipperSystem::setLedStrips(const QKlipperLedStripList &ledStrips)
{
    if (m_ledStrips == ledStrips)
        return;

    m_ledStrips = ledStrips;
    emit ledStripsChanged();
}

void QKlipperSystem::setLedStrip(QKlipperLedStrip *strip)
{
    if(!m_ledStrips.contains(strip->name()))
    {
        m_ledStrips.insert(strip->name(), strip);
        emit ledStripsChanged();
    }
}

QKlipperPowerDeviceList QKlipperSystem::powerDevices() const
{
    return m_powerDevices;
}

void QKlipperSystem::setPowerDevices(const QKlipperPowerDeviceList &powerDevices)
{
    if (m_powerDevices == powerDevices)
        return;

    m_powerDevices = powerDevices;
    emit powerDevicesChanged();
}

void QKlipperSystem::setPowerDevice(QKlipperPowerDevice *powerDevice)
{
    if(!m_powerDevices.contains(powerDevice->name()))
    {
        m_powerDevices.insert(powerDevice->name(), powerDevice);
        emit powerDevicesChanged();
    }
}

