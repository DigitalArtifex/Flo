#ifndef QKLIPPERINSTANCEPOOL_H
#define QKLIPPERINSTANCEPOOL_H

#include "QKlipper/QKlipperInstance/qklipperinstance.h"
#include <QObject>
#include <QMap>

typedef QList<QKlipperInstance*> QKlipperInstanceList;

class QKlipperInstancePool : public QObject
{
    Q_OBJECT
public:

    static QKlipperInstance *klipperInstance(const QString &id);
    static QKlipperInstanceList klipperInstances();
    static QStringList klipperInstanceIds();

    static void addInstance(QKlipperInstance* instance);
    static void removeInstance(QKlipperInstance *instance);

    static qint64 klipperInstancesOnline();

    static QKlipperInstancePool *pool();
    QKlipperInstance *operator[](const QString &name);

    static QList<QKlipperPrintJob*> printJobs();
    static QMultiMap<QString, QKlipperPrintJob*> printJobMap();

signals:
    void instanceAdded(QKlipperInstance *);
    void instanceRemoved(QKlipperInstance *);
    void printJobAdded(QKlipperInstance *, QKlipperPrintJob *);
    void printJobRemoved(QKlipperInstance *, QKlipperPrintJob *);
    void instanceError(QKlipperInstance *, QKlipperError&);

private slots:
    void onPrintJobAdded(QKlipperInstance *instance, QKlipperPrintJob *job);
    void onPrintJobRemoved(QKlipperInstance *instance, QKlipperPrintJob *job);
    void onInstanceError(QKlipperInstance *instance, QKlipperError &error);

private:
    void add(QKlipperInstance *instance);
    void remove(QKlipperInstance *instance);

    explicit QKlipperInstancePool(QObject *parent = nullptr);

    static QMap<QString, QKlipperInstance*> m_instanceMap;
    static QMultiMap<QString, QKlipperPrintJob*> m_jobMap;
    static QKlipperInstancePool *m_instance;
};

#endif // QKLIPPERINSTANCEPOOL_H
