#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QMultiMap>

class QAbstractKlipperConsole;
class Printer;

class System : public QObject
{
    Q_OBJECT

    friend class QAbstractKlipperConsole;
public:

    /*!
     * \brief Filled by machine.system_info
     */
    struct ServiceState
    {
        QString activeState;
        QString subState;
        QString name;
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
        QMultiMap<QString, PackageState> packageStates;
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

    struct VirtualSDCard
    {
        QString filePath;

        qint64 fileSize;
        qint64 filePosition;

        bool active = false;

        qreal progress = 0;
    };

    /*!
     * \brief The MCU class
     */
    struct MCU
    {
        qint64 baudRate = 0;
        qreal maxStepperError = 0;

        QString serial;

        qint64 bytesInvalid = 0;
        qint64 bytesRead = 0;
        qint64 bytesRetransmitted = 0;
        qint64 bytesWritten = 0;
        qint64 bytesUpcoming = 0;
        qint64 bytesAvailable = 0;

        qint64 frequency = 0;

        qreal awake = 0.0;
        qreal taskAverage = 0.0;
        qreal devAverage = 0.0;

        qint64 sequenceRecieved = 0;
        qint64 sequenceSent = 0;
        qint64 sequenceRetransmitted = 0;
    };

    /*!
     * \brief The SafeZHome class
     */
    struct SafeZHome
    {
        qreal homeXPosition = 0;
        qreal homeYPosition = 0;
        qreal speed = 0;
        qreal zHop = 0;
        qreal zHopSpeed = 0;

        bool moveToPrevious = false;
    };

    explicit System(Printer *printer, QObject *parent = nullptr);
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

    VirtualSDCard virtualSDCard() const;
    void setVirtualSDCard(const VirtualSDCard &virtualSDCard);

    MCU mcu() const;
    void setMcu(const MCU &mcu);

    SafeZHome safeZHome() const;
    void setSafeZHome(const SafeZHome &safeZHome);

    void restart();

    void startService(QString service);
    void stopService(QString service);
    void restartService(QString service);
    void updateServices();
    void setServiceStates(QList<ServiceState> serviceStates);
    void updateProcStats();

    void createUser(QString username, QString password);
    void deleteUser(System::User user);

public slots:
    void setNetworkStats(const QMap<QString, NetworkStatsEntry> &NetworkStats);
    void setUserList(const QList<User> &userList);

signals:
    void updated();
    void serviceStatesUpdate();
    void virtualSDCardUpdate();
    void sdInfoUpdate();
    void updateStateUpdate();

    //switching naming convention to Changed
    void networkStatsChanged();
    void mcuChanged();
    void userListChanged();

    void userCreated(User user);
    void userDeleted(User user);
    void userUpdated(User user);

protected:
    void update();

private slots:
    void on_systemUserCreated(User user);
    void on_systemUserDeleted(User user);
    void on_systemUserUpdated(User user);

private:
    qint64                           m_driveCapacity = 0;
    qint64                           m_driveUsage = 0;
    qint64                           m_driveFree = 0;

    QString                          m_hostname;

    //Filled by machine.proc_stats
    QList<MoonrakerStatsEntry>       m_moonrakerStats;
    QMap<QString, NetworkStatsEntry> m_networkStats;
    ThrottleState                    m_throttleState;
    MemoryStats                      m_memoryStats;

    qreal                            m_uptime = 0;
    qint32                           m_connectionCount = 0;

    //Filled by machine.system_info
    CpuInfo                          m_cpuInfo;
    SdInfo                           m_sdInfo;
    DistributionInfo                 m_distributionInfo;
    VirtualizationState              m_virtualizationState;
    QMap<QString, NetworkInterface>  m_networkInterfaces;
    QMap<QString, CanBusDevice>      m_canBus;

    QStringList                      m_availableServices;
    QMap<QString,ServiceState>       m_serviceStates;

    //Filled by machine.peripherals.usb
    QList<UsbPeripheral>             m_usbPeripherals;

    //Filled by machine.peripherals.serial
    QList<SerialPeripheral>          m_serialPeripherals;

    //Filled by machine.peripherals.video
    QList<V412Device>                m_v412Devices;
    QList<LibcameraDevice>           m_libcameraDevices;
    QList<Webcam>                    m_webcams;

    //Filled by machine.peripherals.canbus
    QMap<qint32,CanBus>              m_canBusses;

    AccessDetails                    m_accessDetails;
    QList<User>                      m_userList;

    UpdateState                      m_updateState;

    JobQueue                         m_jobQueue;

    QList<Announcement>              m_announcements;

    VirtualSDCard                    m_virtualSDCard;

    QString                          m_pythonVersion;
    MCU                              m_mcu;
    SafeZHome                        m_safeZHome;

    QAbstractKlipperConsole         *m_console = nullptr;
};

#endif // SYSTEM_H
