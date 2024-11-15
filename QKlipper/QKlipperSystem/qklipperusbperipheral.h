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

#ifndef QKLIPPERUSBPERIPHERAL_H
#define QKLIPPERUSBPERIPHERAL_H

#include <QVariant>

class QKlipperSystem;
class QKlipperConsole;

/*!
 * \brief Filled by machine.peripherals.usb
 */
class QKlipperUsbPeripheral : public QVariant
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperUsbPeripheral();

    QKlipperUsbPeripheral(const QKlipperUsbPeripheral &value);
    QKlipperUsbPeripheral &operator=(const QKlipperUsbPeripheral &value);
    bool operator==(const QKlipperUsbPeripheral &value);
    bool operator!=(const QKlipperUsbPeripheral &value);

    qint32 busNumber() const;
    qint32 deviceNumber() const;
    QString location() const;
    QString vendorId() const;
    QString productId() const;
    QString manufacturer() const;
    QString product() const;
    QString className() const;
    QString subclassName() const;
    QString protocol() const;
    QString description() const;

    void setBusNumber(qint32 busNumber);
    void setDeviceNumber(qint32 deviceNumber);
    void setLocation(const QString &location);
    void setVendorId(const QString &vendorId);
    void setProductId(const QString &productId);
    void setManufacturer(const QString &manufacturer);
    void setProduct(const QString &product);
    void setClassName(const QString &className);
    void setSubclassName(const QString &subclassName);
    void setProtocol(const QString &protocol);
    void setDescription(const QString &description);

private:
    qint32 m_busNumber = 0;
    qint32 m_deviceNumber = 0;

    QString m_location;
    QString m_vendorId;
    QString m_productId;
    QString m_manufacturer;
    QString m_product;
    QString m_className;
    QString m_subclassName;
    QString m_protocol;
    QString m_description;
};

#endif // QKLIPPERUSBPERIPHERAL_H
