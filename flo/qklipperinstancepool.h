/*
* Flo :: QKlipperInstancePool
*
* Provides a means of containing and monitoring multiple QKlipperInstances
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
