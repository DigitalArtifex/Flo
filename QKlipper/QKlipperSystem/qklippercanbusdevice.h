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

#ifndef QKLIPPERCANBUSDEVICE_H
#define QKLIPPERCANBUSDEVICE_H

#include <QObject>
#include <QMap>

class QKlipperSystem;
class QKlipperConsole;

/*!
 * \brief Filled by machine.system_info
 */
class QKlipperCanBusDevice : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperCanBusDevice(QObject *parent = nullptr);

    QKlipperCanBusDevice(const QKlipperCanBusDevice &value);
    QKlipperCanBusDevice(QKlipperCanBusDevice &&value);
    QKlipperCanBusDevice &operator=(const QKlipperCanBusDevice &value);
    QKlipperCanBusDevice &operator=(QKlipperCanBusDevice &&value);
    bool operator==(const QKlipperCanBusDevice &value);
    bool operator==(QKlipperCanBusDevice &&value);
    bool operator!=(const QKlipperCanBusDevice &value);
    bool operator!=(QKlipperCanBusDevice &&value);

    qint16 queueLength() const;

    qint32 bitrate() const;

    QString driver() const;

public slots:
    void setQueueLength(qint16 queueLength);

    void setBitrate(qint32 bitrate);

    void setDriver(const QString &driver);

private slots:

signals:

    void queueLengthChanged();

    void bitrateChanged();

    void driverChanged();

private:
    qint16 m_queueLength = 0;
    qint32 m_bitrate = 0;

    QString m_driver;

    Q_PROPERTY(qint16 queueLength READ queueLength WRITE setQueueLength NOTIFY queueLengthChanged FINAL)
    Q_PROPERTY(qint32 bitrate READ bitrate WRITE setBitrate NOTIFY bitrateChanged FINAL)
    Q_PROPERTY(QString driver READ driver WRITE setDriver NOTIFY driverChanged FINAL)
};

typedef QMap<QString, QKlipperCanBusDevice> QKlipperCanBusDeviceMap;
#endif // QKLIPPERCANBUSDEVICE_H
