#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

class System : public QObject
{
    Q_OBJECT
public:
    explicit System(QObject *parent = nullptr);

    void setCpuCount(qint16 count);
    void setCpuList(QList<qreal> cpus);
    void setCpuInfo(QString info);
    int cpuCount();
    qreal cpuLoad();
    QString cpuInfo();

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
    QString _cpuInfo;
};

#endif // SYSTEM_H
