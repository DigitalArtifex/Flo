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

class QKlipperV412Device : public QVariant
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:

    QKlipperV412Device();

    QKlipperV412Device(const QKlipperV412Device &value);
    QKlipperV412Device &operator=(const QKlipperV412Device &value);
    bool operator==(const QKlipperV412Device &value);
    bool operator!=(const QKlipperV412Device &value);

    QString name() const;

    QString path() const;

    QString cameraName() const;

    QString driver() const;

    QString altName() const;

    QString hardwareBus() const;

    QString version() const;

    QString hardwarePath() const;

    QString pathById() const;

    QString usbLocation() const;

    QStringList capabilities() const;

    QList<QKlipperV412Mode> modes() const;

    void setName(const QString &name);

    void setPath(const QString &path);

    void setCameraName(const QString &cameraName);

    void setDriver(const QString &driver);

    void setAltName(const QString &altName);

    void setHardwareBus(const QString &hardwareBus);

    void setVersion(const QString &version);

    void setHardwarePath(const QString &hardwarePath);

    void setPathById(const QString &pathById);

    void setUsbLocation(const QString &usbLocation);

    void setCapabilities(const QStringList &capabilities);

    void setModes(const QList<QKlipperV412Mode> &modes);

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
