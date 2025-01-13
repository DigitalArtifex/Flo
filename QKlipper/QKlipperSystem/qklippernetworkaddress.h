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

#ifndef QKLIPPERNETWORKADDRESS_H
#define QKLIPPERNETWORKADDRESS_H

#include <QObject>

class QKlipperNetworkAddress
{
    public:
        QString family;
        QString address;

        bool isLinkLocal = false;

        QKlipperNetworkAddress() = default;
        ~QKlipperNetworkAddress() = default;

        QKlipperNetworkAddress(const QKlipperNetworkAddress &value)
        {
            family = value.family;
            address = value.address;
            isLinkLocal = value.isLinkLocal;
        }

        QKlipperNetworkAddress &operator=(const QKlipperNetworkAddress &value)
        {
            family = value.family;
            address = value.address;
            isLinkLocal = value.isLinkLocal;

            return *this;
        }

        bool operator==(const QKlipperNetworkAddress &address) const
        {
            if(this->family != address.family) return false;
            if(this->address != address.address) return false;
            if(this->isLinkLocal != address.isLinkLocal) return false;

            return true;
        }

        bool operator!=(const QKlipperNetworkAddress &address) const { return !(*this == address); }
};

Q_DECLARE_METATYPE(QKlipperNetworkAddress)
#endif // QKLIPPERNETWORKADDRESS_H
