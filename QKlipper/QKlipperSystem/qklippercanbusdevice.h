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
class QKlipperCanBusDevice
{

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperCanBusDevice() = default;
    ~QKlipperCanBusDevice() = default;

    QKlipperCanBusDevice(const QKlipperCanBusDevice &value)
    {
        m_bitrate = value.m_bitrate;
        m_driver = value.m_driver;
        m_queueLength = value.m_queueLength;
    }

    QKlipperCanBusDevice &operator=(const QKlipperCanBusDevice &value)
    {
        m_bitrate = value.m_bitrate;
        m_driver = value.m_driver;
        m_queueLength = value.m_queueLength;

        return *this;
    }

    bool operator==(const QKlipperCanBusDevice &value) const
    {
        if(m_bitrate != value.m_bitrate) return false;
        if(m_driver != value.m_driver) return false;
        if(m_queueLength != value.m_queueLength) return false;

        return true;
    }

    bool operator!=(const QKlipperCanBusDevice &value) const { return !(*this == value); }

    qint16 queueLength() const { return m_queueLength; }

    qint32 bitrate() const { return m_bitrate; }

    QString driver() const { return m_driver; }

protected:
    void setQueueLength(qint16 queueLength) { m_queueLength = queueLength; }

    void setBitrate(qint32 bitrate) { m_bitrate = bitrate; }

    void setDriver(const QString &driver) { m_driver = driver; }

private:
    qint16 m_queueLength = 0;
    qint32 m_bitrate = 0;

    QString m_driver;
};

Q_DECLARE_METATYPE(QKlipperCanBusDevice)
typedef QMap<QString, QKlipperCanBusDevice> QKlipperCanBusDeviceMap;
#endif // QKLIPPERCANBUSDEVICE_H
