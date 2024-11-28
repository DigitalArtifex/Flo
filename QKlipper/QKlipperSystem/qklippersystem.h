/*
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERSYSTEM_H
#define QKLIPPERSYSTEM_H

#include <QObject>
#include <QMap>
#include <QMultiMap>

#include "qklippercanbus.h"
#include "qklippercanbusdevice.h"
#include "qklippercpuinfo.h"
#include "qklipperdistributioninfo.h"
#include "qklipperlibcameradevice.h"
#include "qklippermemorystats.h"
#include "qklippermoonrakerstatsentry.h"
#include "qklippernetworkinterface.h"
#include "qklippernetworkstatsentry.h"
#include "qklippersdinfo.h"
#include "qklipperserialperipheral.h"
#include "qklipperservicestate.h"
#include "qklipperthrottlestate.h"
#include "qklipperupdatemanager.h"
#include "qklipperusbperipheral.h"
#include "qklipperv412device.h"
#include "qklippervirtualizationstate.h"
#include "qklippervirtualsdcard.h"
#include "qklipperwebcam.h"
#include "qklipperpowerdevice.h"
#include "qklipperledstrip.h"

class QKlipperConsole;

class QKlipperSystem : public QObject
{
    Q_OBJECT

        friend QKlipperConsole;
    public:

        enum State
        {
            Idle = 0,
            Updating = 1
        };

        explicit QKlipperSystem(QObject *parent = nullptr);
        ~QKlipperSystem();

        qint64 driveCapacity() const;

        qint64 driveUsage() const;

        qint64 driveFree() const;

        QString hostname() const;

        QList<QKlipperMoonrakerStatsEntry> moonrakerStats() const;

        QMap<QString, QKlipperNetworkStatsEntry> networkStats() const;

        QKlipperThrottleState *throttleState() const;

        QKlipperMemoryStats *memoryStats() const;

        qreal uptime() const;

        qint32 connectionCount() const;

        QKlipperCpuInfo cpuInfo() const;

        QKlipperSdInfo sdInfo() const;

        QKlipperDistributionInfo distributionInfo() const;

        QKlipperVirtualizationState *virtualizationState() const;

        QMap<QString, QKlipperNetworkInterface> networkInterfaces() const;

        QKlipperCanBus *canBus() const;

        QStringList availableServices() const;

        QMap<QString, QKlipperServiceState> serviceStates() const;

        QList<QKlipperUsbPeripheral> usbPeripherals() const;

        QList<QKlipperSerialPeripheral> serialPeripherals() const;

        QList<QKlipperV412Device> v412Devices() const;

        QList<QKlipperLibcameraDevice> libcameraDevices() const;

        QList<QKlipperWebcam> webcams() const;

        QMap<qint32, QKlipperCanBus *> canBusses() const;

        QKlipperVirtualSDCard *virtualSDCard() const;

        QString pythonVersion() const;

        QKlipperUpdateManager *updateManager() const;

        State state() const;

        QKlipperPowerDeviceList powerDevices() const;

        QKlipperLedStripList ledStrips() const;

    public slots:
        Q_INVOKABLE bool stopService(QString serviceName);
        Q_INVOKABLE bool startService(QString serviceName);
        Q_INVOKABLE bool restartService(QString serviceName);

        void setPowerDevices(const QKlipperPowerDeviceList &powerDevices);
        void setPowerDevice(QKlipperPowerDevice *powerDevice);

        void setLedStrips(const QKlipperLedStripList &ledStrips);
        void setLedStrip(QKlipperLedStrip *strip);

    private slots:

        void setUpdateManager(QKlipperUpdateManager *updateManager);

        void setState(State state);
        void setDriveCapacity(qint64 driveCapacity);

        void setDriveUsage(qint64 driveUsage);

        void setDriveFree(qint64 driveFree);

        void setHostname(const QString &hostname);

        void setMoonrakerStats(const QList<QKlipperMoonrakerStatsEntry> &moonrakerStats);

        void setNetworkStats(const QMap<QString, QKlipperNetworkStatsEntry> &networkStats);

        void setThrottleState(QKlipperThrottleState *throttleState);

        void setMemoryStats(QKlipperMemoryStats *memoryStats);

        void setUptime(qreal uptime);

        void setConnectionCount(qint32 connectionCount);

        void setCpuInfo(const QKlipperCpuInfo &cpuInfo);

        void setSdInfo(const QKlipperSdInfo &sdInfo);

        void setDistributionInfo(const QKlipperDistributionInfo &distributionInfo);

        void setVirtualizationState(QKlipperVirtualizationState *virtualizationState);

        void setNetworkInterfaces(const QMap<QString, QKlipperNetworkInterface> &networkInterfaces);

        void setCanBus(QKlipperCanBus *canBus);

        void setAvailableServices(const QStringList &availableServices);

        void setServiceStates(const QMap<QString, QKlipperServiceState> &serviceStates);

        void setUsbPeripherals(const QList<QKlipperUsbPeripheral> &usbPeripherals);

        void setSerialPeripherals(const QList<QKlipperSerialPeripheral> &serialPeripherals);

        void setV412Devices(const QList<QKlipperV412Device> &v412Devices);

        void setLibcameraDevices(const QList<QKlipperLibcameraDevice> &libcameraDevices);

        void setWebcams(const QList<QKlipperWebcam> &webcams);

        void setCanBusses(const QMap<qint32, QKlipperCanBus *> &canBusses);

        void setVirtualSDCard(QKlipperVirtualSDCard *virtualSDCard);

        void setPythonVersion(const QString &pythonVersion);

    signals:

        void driveCapacityChanged();

        void driveUsageChanged();

        void driveFreeChanged();

        void hostnameChanged();

        void moonrakerStatsChanged();

        void networkStatsChanged();

        void throttleStateChanged();

        void memoryStatsChanged();

        void uptimeChanged();

        void connectionCountChanged();

        void cpuInfoChanged();

        void sdInfoChanged();

        void distributionInfoChanged();

        void virtualizationStateChanged();

        void networkInterfacesChanged();

        void canBusChanged();

        void availableServicesChanged();

        void serviceStatesChanged();

        void usbPeripheralsChanged();

        void serialPeripheralsChanged();

        void v412DevicesChanged();

        void libcameraDevicesChanged();

        void webcamsChanged();

        void canBussesChanged();

        void updateStateChanged();

        void virtualSDCardChanged();

        void pythonVersionChanged();

        void updateManagerChanged();

        void stateChanged();

        void powerDevicesChanged();

        void ledStripsChanged();

    private:
        qint64                                    m_driveCapacity = 0;
        qint64                                    m_driveUsage = 0;
        qint64                                    m_driveFree = 0;

        QString                                   m_hostname;

        //Filled by machine.proc_stats
        QList<QKlipperMoonrakerStatsEntry>        m_moonrakerStats;
        QMap<QString, QKlipperNetworkStatsEntry>  m_networkStats;
        QKlipperThrottleState                    *m_throttleState;
        QKlipperMemoryStats                      *m_memoryStats;

        qreal                                     m_uptime = 0;
        qint32                                    m_connectionCount = 0;

        //Filled by machine.system_info
        QKlipperCpuInfo                           m_cpuInfo;
        QKlipperSdInfo                            m_sdInfo;
        QKlipperDistributionInfo                  m_distributionInfo;
        QKlipperVirtualizationState              *m_virtualizationState;
        QMap<QString, QKlipperNetworkInterface>   m_networkInterfaces;
        QKlipperCanBus                           *m_canBus;

        QStringList                               m_availableServices;
        QMap<QString,QKlipperServiceState>        m_serviceStates;

        //Filled by machine.peripherals.usb
        QList<QKlipperUsbPeripheral>              m_usbPeripherals;

        //Filled by machine.peripherals.serial
        QList<QKlipperSerialPeripheral>           m_serialPeripherals;

        //Filled by machine.peripherals.video
        QList<QKlipperV412Device>                 m_v412Devices;
        QList<QKlipperLibcameraDevice>            m_libcameraDevices;
        QList<QKlipperWebcam>                     m_webcams;

        //Filled by machine.peripherals.canbus
        QMap<qint32,QKlipperCanBus*>              m_canBusses;

        QKlipperUpdateManager                    *m_updateManager;

        QKlipperVirtualSDCard                    *m_virtualSDCard;

        QString                                   m_pythonVersion;
        State                                     m_state;
        QKlipperPowerDeviceList m_powerDevices;
        QKlipperLedStripList m_ledStrips;

        Q_PROPERTY(qint64 driveCapacity READ driveCapacity WRITE setDriveCapacity NOTIFY driveCapacityChanged FINAL)
        Q_PROPERTY(qint64 driveUsage READ driveUsage WRITE setDriveUsage NOTIFY driveUsageChanged FINAL)
        Q_PROPERTY(qint64 driveFree READ driveFree WRITE setDriveFree NOTIFY driveFreeChanged FINAL)

        Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged FINAL)

        Q_PROPERTY(QList<QKlipperMoonrakerStatsEntry> moonrakerStats READ moonrakerStats WRITE setMoonrakerStats NOTIFY moonrakerStatsChanged FINAL)
        Q_PROPERTY(QMap<QString, QKlipperNetworkStatsEntry> networkStats READ networkStats WRITE setNetworkStats NOTIFY networkStatsChanged FINAL)
        Q_PROPERTY(QKlipperThrottleState *throttleState READ throttleState WRITE setThrottleState NOTIFY throttleStateChanged FINAL)
        Q_PROPERTY(QKlipperMemoryStats *memoryStats READ memoryStats WRITE setMemoryStats NOTIFY memoryStatsChanged FINAL)

        Q_PROPERTY(qreal uptime READ uptime WRITE setUptime NOTIFY uptimeChanged FINAL)
        Q_PROPERTY(qint32 connectionCount READ connectionCount WRITE setConnectionCount NOTIFY connectionCountChanged FINAL)

        Q_PROPERTY(QKlipperCpuInfo cpuInfo READ cpuInfo WRITE setCpuInfo NOTIFY cpuInfoChanged FINAL)
        Q_PROPERTY(QKlipperSdInfo sdInfo READ sdInfo WRITE setSdInfo NOTIFY sdInfoChanged FINAL)
        Q_PROPERTY(QKlipperDistributionInfo distributionInfo READ distributionInfo WRITE setDistributionInfo NOTIFY distributionInfoChanged FINAL)
        Q_PROPERTY(QKlipperVirtualizationState *virtualizationState READ virtualizationState WRITE setVirtualizationState NOTIFY virtualizationStateChanged FINAL)
        Q_PROPERTY(QMap<QString, QKlipperNetworkInterface> networkInterfaces READ networkInterfaces WRITE setNetworkInterfaces NOTIFY networkInterfacesChanged FINAL)
        Q_PROPERTY(QKlipperCanBus *canBus READ canBus WRITE setCanBus NOTIFY canBusChanged FINAL)

        Q_PROPERTY(QStringList availableServices READ availableServices WRITE setAvailableServices NOTIFY availableServicesChanged FINAL)
        Q_PROPERTY(QMap<QString, QKlipperServiceState> serviceStates READ serviceStates WRITE setServiceStates NOTIFY serviceStatesChanged FINAL)

        Q_PROPERTY(QList<QKlipperUsbPeripheral> usbPeripherals READ usbPeripherals WRITE setUsbPeripherals NOTIFY usbPeripheralsChanged FINAL)
        Q_PROPERTY(QList<QKlipperSerialPeripheral> serialPeripherals READ serialPeripherals WRITE setSerialPeripherals NOTIFY serialPeripheralsChanged FINAL)
        Q_PROPERTY(QList<QKlipperV412Device> v412Devices READ v412Devices WRITE setV412Devices NOTIFY v412DevicesChanged FINAL)
        Q_PROPERTY(QList<QKlipperLibcameraDevice> libcameraDevices READ libcameraDevices WRITE setLibcameraDevices NOTIFY libcameraDevicesChanged FINAL)
        Q_PROPERTY(QList<QKlipperWebcam> webcams READ webcams WRITE setWebcams NOTIFY webcamsChanged FINAL)
        Q_PROPERTY(QMap<qint32, QKlipperCanBus *> canBusses READ canBusses WRITE setCanBusses NOTIFY canBussesChanged FINAL)
        Q_PROPERTY(QKlipperVirtualSDCard *virtualSDCard READ virtualSDCard WRITE setVirtualSDCard NOTIFY virtualSDCardChanged FINAL)
        Q_PROPERTY(QString pythonVersion READ pythonVersion WRITE setPythonVersion NOTIFY pythonVersionChanged FINAL)
        Q_PROPERTY(QKlipperUpdateManager *updateManager READ updateManager WRITE setUpdateManager NOTIFY updateManagerChanged FINAL)
        Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged FINAL)
        Q_PROPERTY(QKlipperPowerDeviceList powerDevices READ powerDevices WRITE setPowerDevices NOTIFY powerDevicesChanged FINAL)
        Q_PROPERTY(QKlipperLedStripList ledStrips READ ledStrips WRITE setLedStrips NOTIFY ledStripsChanged FINAL)
};

#endif // QKLIPPERSYSTEM_H
