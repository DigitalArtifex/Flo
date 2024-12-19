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

#ifndef QKLIPPERV412DEVICE_H
#define QKLIPPERV412DEVICE_H

#include <QVariant>

#include "qklipperv412mode.h"

class QKlipperSystem;
class QKlipperConsole;

class QKlipperV412Device
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:

    QKlipperV412Device() = default;
    ~QKlipperV412Device() = default;

    QKlipperV412Device(const QKlipperV412Device &value)
    {
        m_name = value.m_name;
        m_path = value.m_path;
        m_cameraName = value.m_cameraName;
        m_driver = value.m_driver;
        m_altName = value.m_altName;
        m_hardwareBus = value.m_hardwareBus;
        m_version = value.m_version;
        m_hardwarePath = value.m_hardwarePath;
        m_pathById = value.m_pathById;
        m_usbLocation = value.m_usbLocation;

        m_capabilities = value.m_capabilities;
        m_modes = value.m_modes;
    }

    QKlipperV412Device &operator=(const QKlipperV412Device &value)
    {
        m_name = value.m_name;
        m_path = value.m_path;
        m_cameraName = value.m_cameraName;
        m_driver = value.m_driver;
        m_altName = value.m_altName;
        m_hardwareBus = value.m_hardwareBus;
        m_version = value.m_version;
        m_hardwarePath = value.m_hardwarePath;
        m_pathById = value.m_pathById;
        m_usbLocation = value.m_usbLocation;

        m_capabilities = value.m_capabilities;
        m_modes = value.m_modes;

        return *this;
    }

    bool operator==(const QKlipperV412Device &value) const
    {
        if(m_name != value.m_name) return false;
        if(m_path != value.m_path) return false;
        if(m_cameraName != value.m_cameraName) return false;
        if(m_driver != value.m_driver) return false;
        if(m_altName != value.m_altName) return false;
        if(m_hardwareBus != value.m_hardwareBus) return false;
        if(m_version != value.m_version) return false;
        if(m_hardwarePath != value.m_hardwarePath) return false;
        if(m_pathById != value.m_pathById) return false;
        if(m_usbLocation != value.m_usbLocation) return false;

        if(m_capabilities != value.m_capabilities) return false;

        if(m_modes != value.m_modes) return false;

        return true;
    }

    bool operator!=(const QKlipperV412Device &value) const { return !(*this == value); }

    QString name() const { return m_name; }

    QString path() const { return m_path; }

    QString cameraName() const { return m_cameraName; }

    QString driver() const { return m_driver; }

    QString altName() const { return m_altName; }

    QString hardwareBus() const { return m_hardwareBus; }

    QString version() const { return m_version; }

    QString hardwarePath() const { return m_hardwarePath; }

    QString pathById() const { return m_pathById; }

    QString usbLocation() const { return m_usbLocation; }

    QStringList capabilities() const { return m_capabilities; }

    QList<QKlipperV412Mode> modes() const { return m_modes; }

protected:
    void setName(const QString &name) { m_name = name; }

    void setPath(const QString &path) { m_path = path; }

    void setCameraName(const QString &cameraName) { m_cameraName = cameraName; }

    void setDriver(const QString &driver) { m_driver = driver; }

    void setAltName(const QString &altName) { m_altName = altName; }

    void setHardwareBus(const QString &hardwareBus) { m_hardwareBus = hardwareBus; }

    void setVersion(const QString &version) { m_version = version; }

    void setHardwarePath(const QString &hardwarePath) { m_hardwarePath = hardwarePath; }

    void setPathById(const QString &pathById) { m_pathById = pathById; }

    void setUsbLocation(const QString &usbLocation) { m_usbLocation = usbLocation; }

    void setCapabilities(const QStringList &capabilities) { m_capabilities = capabilities; }

    void setModes(const QList<QKlipperV412Mode> &modes) { m_modes = modes; }

private:
    QString m_name;
    QString m_path;
    QString m_cameraName;
    QString m_driver;
    QString m_altName;
    QString m_hardwareBus;
    QString m_version;
    QString m_hardwarePath;
    QString m_pathById;
    QString m_usbLocation;

    QStringList m_capabilities;
    QList<QKlipperV412Mode> m_modes;
};

#endif // QKLIPPERV412DEVICE_H
