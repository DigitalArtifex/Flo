#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

class System : public QObject
{
    Q_OBJECT
public:
    explicit System(QObject *parent = nullptr);

    void setCpuCount(int count);
    void setCpuList(QList<qreal> cpus);
    void setCpuInfo(QString info);
    int cpuCount();
    qreal cpuLoad();
    QString cpuInfo();

    void setMemoryUsage(long memory);
    void setMemoryCapacity(long memory);
    qreal memoryCapacity();
    qreal memoryUsage();
    qreal memoryLoad();

    void setHostname(QString hostname);
    QString hostname();

signals:

private:
    long _memoryCapacity;
    long _memoryUsage;
    int _cpuCount;
    QList<qreal> _cpuUsages;

    QString _hostname;
    QString _cpuInfo;
};

#endif // SYSTEM_H
