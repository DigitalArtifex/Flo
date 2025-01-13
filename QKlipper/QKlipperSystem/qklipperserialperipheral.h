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

#ifndef QKLIPPERSERIALPERIPHERAL_H
#define QKLIPPERSERIALPERIPHERAL_H

#include <QVariant>
class QKlipperSystem;
class QKlipperConsole;
/*!
 * \brief Filled by machine.peripherals.serial
 */
class QKlipperSerialPeripheral
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperSerialPeripheral() = default;
    ~QKlipperSerialPeripheral() = default;

    QKlipperSerialPeripheral(const QKlipperSerialPeripheral &value)
    {
        m_type = value.m_type;
        m_path = value.m_path;
        m_name = value.m_name;
        m_driver = value.m_driver;
        m_hardwarePath = value.m_hardwarePath;
        m_pathById = value.m_pathById;
        m_usbLocation = value.m_usbLocation;
    }
    QKlipperSerialPeripheral &operator=(const QKlipperSerialPeripheral &value)
    {
        m_type = value.m_type;
        m_path = value.m_path;
        m_name = value.m_name;
        m_driver = value.m_driver;
        m_hardwarePath = value.m_hardwarePath;
        m_pathById = value.m_pathById;
        m_usbLocation = value.m_usbLocation;

        return *this;
    }
    bool operator==(const QKlipperSerialPeripheral &value) const
    {
        if(m_type != value.m_type) return false;
        if(m_path != value.m_path) return false;
        if(m_name != value.m_name) return false;
        if(m_driver != value.m_driver) return false;
        if(m_hardwarePath != value.m_hardwarePath) return false;
        if(m_pathById != value.m_pathById) return false;
        if(m_usbLocation != value.m_usbLocation) return false;

        return true;
    }
    bool operator!=(const QKlipperSerialPeripheral &value) const { return !(*this == value); }

    QString type() const { return m_type; }

    QString path() const { return m_path; }

    QString name() const { return m_name; }

    QString driver() const { return m_driver; }

    QString hardwarePath() const { return m_hardwarePath; }

    QString pathById() const { return m_pathById; }

    QString usbLocation() const { return m_usbLocation; }

protected:
    void setType(const QString &type) { m_type = type; }

    void setPath(const QString &path) { m_path = path; }

    void setName(const QString &name) { m_name = name; }

    void setDriver(const QString &driver) { m_driver = driver; }

    void setHardwarePath(const QString &hardwarePath) { m_hardwarePath = hardwarePath; }

    void setPathById(const QString &pathById) { m_pathById = pathById; }

    void setUsbLocation(const QString &usbLocation) { m_usbLocation = usbLocation; }

private:
    QString m_type;
    QString m_path;
    QString m_name;
    QString m_driver;
    QString m_hardwarePath;
    QString m_pathById;
    QString m_usbLocation;
};

Q_DECLARE_METATYPE(QKlipperSerialPeripheral)
#endif // QKLIPPERSERIALPERIPHERAL_H
