#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QMap>

class System : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief Filled by machine.system_info
     */
    struct ServiceState
    {
        QString activeState;
        QString subState;
    };

    /*!
     * \brief Filled by machine.system_info
     */
    struct VirtualizationState
    {
        QString type;
        QString identifier;
    };

    /*!
     * \brief Filled by machine.system_info
     */
    struct NetworkInterface
    {
        struct IpAddress {
            QString family;
            QString address;

            bool isLinkLocal = false;
        };

        QString macAddress;

        QList<IpAddress> ipAddresses;
    };

    /*!
     * \brief Filled by machine.system_info
     */
    struct CanBusDevice
    {
        qint16 queueLength = 0;
        qint32 bitrate = 0;

        QString driver;
    };

    /*!
     * \brief Filled by machine.system_info
     */
    struct CpuInfo
    {
        qint32 cpuCount = 0;
        qint32 bitCount = 0;
        qint64 totalMemory = 0;

        qreal temp = 0;
        qreal usage = 0;

        QString processor;
        QString description;
        QString serialNumber;
        QString hardwareDescription;
        QString model;
        QString memoryUnits;

        QList<qreal> coreUsage;
    };

    /*!
     * \brief Filled by machine.system_info
     */
    struct SdInfo
    {
        qint64 totalBytes = 0;
        qint64 usedBytes = 0;
        qint64 availableBytes = 0;

        QString manufacturerId;
        QString manufacturer;
        QString oemId;
        QString productName;
        QString productRevision;
        QString serialNumber;
        QString manufacturerDate;
        QString capacityString;
    };

    /*!
     * \brief Filled by machine.system_info
     */
    struct DistributionInfo
    {
        QString name;
        QString id;
        QString version;
        QString versionMajor;
        QString versionMinor;
        QString versionBuildNumber;
        QString style;
        QString codename;
    };

    /*!
     * \brief Filled by machine.proc_stats
     */
    struct MoonrakerStatsEntry
    {
        qreal time = 0;
        qreal cpuUsage = 0;
        qreal memory = 0;

        QString memoryUnits;
    };

    /*!
     * \brief Filled by machine.proc_stats
     */
    struct NetworkStatsEntry
    {
        qreal rxBytes = 0;
        qreal txBytes = 0;
        qreal bandwidth = 0;
    };

    /*!
     * \brief Filled by machine.proc_stats
     */
    struct MemoryStats
    {
        qreal total = 0;
        qreal used = 0;
        qreal average = 0;
    };

    /*!
     * \brief Filled by machine.proc_stats
     */
    struct ThrottleState
    {
        qint32 bits = 0;

        QStringList flags;
    };

    /*!
     * \brief Filled by machine.peripherals.usb
     */
    struct UsbPeripheral
    {
        qint32 busNumber = 0;
        qint32 deviceNumber = 0;

        QString location;
        QString vendorId;
        QString productId;
        QString manufacturer;
        QString product;
        QString className;
        QString subclassName;
        QString protocol;
        QString description;
    };

    /*!
     * \brief Filled by machine.peripherals.serial
     */
    struct SerialPeripheral
    {
        QString type;
        QString path;
        QString name;
        QString driver;
        QString hardwarePath;
        QString pathById;
        QString usbLocation;
    };

    /*!
     * \brief Filled by machine.peripherals.serial
     */
    struct V412Device
    {
        struct Mode
        {
            QString description;
            QString format;

            QStringList flags;
            QStringList resolutions;
        };

        QString name;
        QString path;
        QString cameraName;
        QString driver;
        QString altName;
        QString hardwareBus;
        QString version;
        QString hardwarePath;
        QString pathById;
        QString usbLocation;

        QStringList capabilities;
        QList<Mode> modes;
    };

    /*!
     * \brief Filled by machine.peripherals.serial
     */
    struct LibcameraDevice
    {
        struct Mode
        {
            QString format;
            QStringList resolutions;
        };

        QString id;
        QString model;

        QList<Mode> modes;
    };

    /*!
     * \brief Filled by machine.peripherals.canbus
     */
    struct CanBus
    {
        struct Interface
        {
            QString uuid;
            QString application;
        };

        QList<Interface> interfaces;
    };

    explicit System(QObject *parent = nullptr);
    ~System();

    void setHostname(QString hostname);
    QString hostname();

    qint64 driveCapacity() const;
    void setDriveCapacity(qint64 driveCapacity);

    qint64 driveUsage() const;
    void setDriveUsage(qint64 driveUsage);

    qint64 driveFree() const;
    void setDriveFree(qint64 driveFree);

    QStringList availableServices() const;
    void setAvailableServices(const QStringList &availableServices);

    QMap<QString, ServiceState> serviceStates() const;

    QString pythonVersion() const;
    void setPythonVersion(const QString &pythonVersion);

    CpuInfo cpuInfo() const;
    void setCpuInfo(CpuInfo cpuInfo);

    DistributionInfo distributionInfo() const;
    void setDistributionInfo(const DistributionInfo &distributionInfo);

    VirtualizationState virtualizationState() const;
    void setVirtualizationState(const VirtualizationState &virtualizationState);

    QMap<QString, NetworkInterface> networkInterfaces() const;
    void setNetworkInterfaces(const QMap<QString, NetworkInterface> &networkInterfaces);

    QMap<QString, CanBusDevice> canBus() const;
    void setCanBus(const QMap<QString, CanBusDevice> &canBus);

    SdInfo sdInfo() const;
    void setSdInfo(const SdInfo &sdInfo);

    QList<MoonrakerStatsEntry> moonrakerStats() const;

    QMap<QString, NetworkStatsEntry> networkStats() const;

    ThrottleState throttleState() const;
    void setThrottleState(const ThrottleState &throttleState);

    MemoryStats memoryStats() const;
    void setMemoryStats(const MemoryStats &memoryStats);

    qreal uptime() const;
    void setUptime(qreal uptime);

    qint32 connectionCount() const;
    void setConnectionCount(qint32 connectionCount);

    QList<UsbPeripheral> usbPeripherals() const;

    QList<SerialPeripheral> serialPeripherals() const;

    QList<V412Device> v412Devices() const;

    QList<LibcameraDevice> libcameraDevices() const;

    QMap<qint32, CanBus> canBusses() const;

signals:


private:
    qint64                           _driveCapacity = 0;
    qint64                           _driveUsage = 0;
    qint64                           _driveFree = 0;

    QString                          _hostname;

    //Filled by machine.proc_stats
    QList<MoonrakerStatsEntry>       _moonrakerStats;
    QMap<QString, NetworkStatsEntry> _networkStats;
    ThrottleState                    _throttleState;
    MemoryStats                      _memoryStats;

    qreal                            _uptime = 0;
    qint32                           _connectionCount = 0;

    //Filled by machine.system_info
    CpuInfo                          _cpuInfo;
    SdInfo                           _sdInfo;
    DistributionInfo                 _distributionInfo;
    VirtualizationState              _virtualizationState;
    QMap<QString, NetworkInterface>  _networkInterfaces;
    QMap<QString, CanBusDevice>      _canBus;

    QStringList                      _availableServices;
    QMap<QString,ServiceState>       _serviceStates;

    //Filled by machine.peripherals.usb
    QList<UsbPeripheral>             _usbPeripherals;

    //Filled by machine.peripherals.serial
    QList<SerialPeripheral>          _serialPeripherals;

    //Filled by machine.peripherals.video
    QList<V412Device>                _v412Devices;
    QList<LibcameraDevice>           _libcameraDevices;

    //Filled by machine.peripherals.canbus
    QMap<qint32,CanBus>              _canBusses;

    QString                          _pythonVersion;
};

#endif // SYSTEM_H
