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

#ifndef QKLIPPERCANBUS_H
#define QKLIPPERCANBUS_H

#include <QObject>

#include "qklippercanbusdevice.h"
#include "qklippercanbusinterface.h"

class QKlipperSystem;
class QKlipperConsole;

/*!
 * \brief Filled by machine.peripherals.canbus
 */
class QKlipperCanBus : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:

    explicit QKlipperCanBus(QObject *parent = nullptr);

    QList<QKlipperCanBusInterface> interfaces() const;

    QKlipperCanBusDeviceMap devices() const;

public slots:
    void setInterfaces(const QList<QKlipperCanBusInterface> &interfaces);

    void setDevices(const QKlipperCanBusDeviceMap &devices);

private slots:

signals:

    void interfacesChanged();

    void devicesChanged();

private:
    QList<QKlipperCanBusInterface> m_interfaces;
    QKlipperCanBusDeviceMap m_devices;

    Q_PROPERTY(QList<QKlipperCanBusInterface> interfaces READ interfaces WRITE setInterfaces NOTIFY interfacesChanged FINAL)
    Q_PROPERTY(QKlipperCanBusDeviceMap devices READ devices WRITE setDevices NOTIFY devicesChanged FINAL)
};

#endif // QKLIPPERCANBUS_H
