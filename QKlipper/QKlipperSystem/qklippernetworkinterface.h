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

#ifndef QKLIPPERNETWORKINTERFACE_H
#define QKLIPPERNETWORKINTERFACE_H

#include <QObject>
class QKlipperSystem;
class QKlipperConsole;

#include "qklippernetworkaddress.h"

/*!
 * \brief Filled by machine.system_info
 */
class QKlipperNetworkInterface
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:

    QKlipperNetworkInterface() = default;
    ~QKlipperNetworkInterface() = default;

    QKlipperNetworkInterface(const QKlipperNetworkInterface &value)
    {
        m_ipAddresses = value.m_ipAddresses;
        m_macAddress = value.m_macAddress;
    }
    QKlipperNetworkInterface &operator=(const QKlipperNetworkInterface &value)
    {
        m_ipAddresses = value.m_ipAddresses;
        m_macAddress = value.m_macAddress;

        return *this;
    }
    bool operator==(const QKlipperNetworkInterface &value)
    {
        if(m_ipAddresses != value.m_ipAddresses) return false;

        if(m_macAddress != value.m_macAddress) return false;

        return true;
    }

    bool operator!=(const QKlipperNetworkInterface &value) { return !(*this == value); }

    QString macAddress() const { return m_macAddress; }

    QList<QKlipperNetworkAddress> ipAddresses() const { return m_ipAddresses; }

protected:
    void setMacAddress(const QString &macAddress) { m_macAddress = macAddress; }

    void setIpAddresses(const QList<QKlipperNetworkAddress> &ipAddresses) { m_ipAddresses = ipAddresses; }

private:
    QString m_macAddress;
    QList<QKlipperNetworkAddress> m_ipAddresses;
};

Q_DECLARE_METATYPE(QKlipperNetworkInterface)
#endif // QKLIPPERNETWORKINTERFACE_H
