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

#ifndef QKLIPPERCANBUSINTERFACE_H
#define QKLIPPERCANBUSINTERFACE_H

#include <QVariant>

class QKlipperCanBusInterface : public QVariant
{
public:
    QString uuid;
    QString application;

    QKlipperCanBusInterface() : QVariant()
    {

    }

    QKlipperCanBusInterface(const QKlipperCanBusInterface &interface) : QVariant()
    {
        uuid = interface.uuid;
        application = interface.application;
    }

    bool operator==(const QKlipperCanBusInterface &interface)
    {
        if(uuid != interface.uuid) return false;
        if(application != interface.application) return false;

        return true;
    }

    bool operator!=(const QKlipperCanBusInterface &interface)
    {
        if(uuid == interface.uuid) return false;
        if(application == interface.application) return false;

        return true;
    }
};

Q_DECLARE_METATYPE(QKlipperCanBusInterface)
#endif // QKLIPPERCANBUSINTERFACE_H
