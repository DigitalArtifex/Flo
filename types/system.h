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

    /*!
     * \brief Filled by machine.peripherals.canbus
     */
    struct User
    {
        QString username;
        QString source;

        qreal createdOn;
    };

    struct AccessDetails
    {
        bool isLoggedIn = false;

        QString token;
        QString refreshToken;

        User user;
    };

    /*!
     * \brief Filled by server.webcams.list
     */
    struct Webcam
    {
        QString name;
        QString location;
        QString service;
        QString iconString;
        QString streamUrl;
        QString snapshotUrl;
        QString aspectRatio;
        QString source;
        QString uid;

        qint16 targetFps = 0;
        qint16 targetFpsIdle = 0;
        qint16 rotation = 0;

        bool enabled = false;
        bool flipVertical = false;
        bool flipHorizontal = false;
    };

    /*!
     * \brief Filled by server.announcements.list
     */
    struct Announcement
    {
        QString entryId;
        QString url;
        QString title;
        QString description;
        QString priority;
        QString feed;
        QString source;

        qreal date = 0;
        qreal dateDismissed = 0;
        qreal dateDismissedWake = 0;

        bool dismissed = false;
    };

    /*!
     * \brief Filled by server.announcements.list
     */
    struct UpdateState
    {
        struct CommitState
        {
            QString sha;
            QString author;
            QString date;
            QString subject;
            QString message;
            QString tag;
        };

        struct SystemState
        {
            qint32 packageCount = 0;
            QStringList packages;
        };

        struct PackageState
        {
            bool debugEnabled = false;
            bool isValid = false;
            bool isDirty = false;
            bool corrupt = false;
            bool detached = false;
            bool pristine = false;

            QString channel;
            QString configuredType;
            QString detectedType;
            QString remoteAlias;
            QString branch;
            QString owner;
            QString repoName;
            QString version;
            QString rollbackVersion;
            QString remoteVersion;
            QString currentHash;
            QString remoteHash;
            QString fullVersionString;
            QString recoveryUrl;
            QString remoteUrl;

            QStringList warnings;
            QStringList anomalies;
            QStringList infoTags;
            QStringList gitMessages;

            QList<CommitState> commitsBehind;
        };

        bool busy = false;

        qint32 githubRateLimit = 0;
        qint32 githubRequestsRemaining = 0;
        qint32 githubLimitResetTime = 0;

        SystemState systemState;
        QMap<QString, PackageState> packageStates;
    };

    struct JobQueue
    {
        enum QueueState
        {
            Ready,
            Paused,
            Loading,
            Starting,
            Error
        };

        struct Job
        {
            QString filename;
            QString id;

            qreal timeAdded;
            qreal timeInQueue;
        };

        QList<Job> queue;
        QueueState queueState = Error;
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

    AccessDetails accessDetails() const;
    void setAccessDetails(const AccessDetails &accessDetails);

    QList<User> userList() const;

    QList<Webcam> webcams() const;

    QList<Announcement> announcements() const;

    UpdateState updateState() const;
    void setUpdateState(const UpdateState &updateState);

    JobQueue jobQueue() const;

    void setJobQueue(const JobQueue &jobQueue);

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
    QList<Webcam>                    _webcams;

    //Filled by machine.peripherals.canbus
    QMap<qint32,CanBus>              _canBusses;

    AccessDetails                    _accessDetails;
    QList<User>                      _userList;

    UpdateState                      _updateState;

    JobQueue                         _jobQueue;

    QList<Announcement>              _announcements;

    QString                          _pythonVersion;
};

#endif // SYSTEM_H
