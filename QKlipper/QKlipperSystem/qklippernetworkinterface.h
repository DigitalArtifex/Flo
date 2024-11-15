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
class QKlipperNetworkInterface : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:

    explicit QKlipperNetworkInterface(QObject *parent = nullptr);

    QKlipperNetworkInterface(const QKlipperNetworkInterface &value);
    QKlipperNetworkInterface(QKlipperNetworkInterface &&value);
    QKlipperNetworkInterface &operator=(const QKlipperNetworkInterface &value);
    QKlipperNetworkInterface &operator=(QKlipperNetworkInterface &&value);
    bool operator==(const QKlipperNetworkInterface &value);
    bool operator==(QKlipperNetworkInterface &&value);
    bool operator!=(const QKlipperNetworkInterface &value);
    bool operator!=(QKlipperNetworkInterface &&value);

    QString macAddress() const;

    QList<QKlipperNetworkAddress> ipAddresses() const;

public slots:
    void setMacAddress(const QString &macAddress);

    void setIpAddresses(const QList<QKlipperNetworkAddress> &ipAddresses);

private slots:

signals:

    void macAddressChanged();

    void ipAddressesChanged();

private:
    QString m_macAddress;
    QList<QKlipperNetworkAddress> m_ipAddresses;
    Q_PROPERTY(QString macAddress READ macAddress WRITE setMacAddress NOTIFY macAddressChanged FINAL)
    Q_PROPERTY(QList<QKlipperNetworkAddress> ipAddresses READ ipAddresses WRITE setIpAddresses NOTIFY ipAddressesChanged FINAL)
};

#endif // QKLIPPERNETWORKINTERFACE_H
