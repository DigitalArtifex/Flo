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

        QString processor;
        QString description;
        QString serialNumber;
        QString hardwareDescription;
        QString model;
        QString memoryUnits;
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

    explicit System(QObject *parent = nullptr);
    ~System();

    void setCpuCount(qint16 count);
    void setCpuList(QList<qreal> cpus);
    int cpuCount();
    qreal cpuLoad();

    void setMemoryUsage(qint64 memory);
    void setMemoryCapacity(qint64 memory);

    qreal memoryCapacity();
    qreal memoryUsage();
    qreal memoryLoad();

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

signals:


private:
    qint64 _driveCapacity = 0;
    qint64 _driveUsage = 0;
    qint64 _driveFree = 0;
    qint64 _memoryCapacity = 0;
    qint64 _memoryUsage = 0;

    qint16 _cpuCount = 0;

    QList<qreal> _cpuUsages;

    QString _hostname;

    CpuInfo _cpuInfo;
    SdInfo _sdInfo;
    DistributionInfo _distributionInfo;
    VirtualizationState _virtualizationState;
    QMap<QString, NetworkInterface> _networkInterfaces;
    QMap<QString, CanBusDevice> _canBus;

    QStringList _availableServices;
    QMap<QString,ServiceState> _serviceStates;

    QString _pythonVersion;
};

#endif // SYSTEM_H
