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
class QKlipperUsbPeripheral
{
        friend QKlipperSystem;
        friend QKlipperConsole;
    public:
        QKlipperUsbPeripheral() = default;
        ~QKlipperUsbPeripheral() = default;

        QKlipperUsbPeripheral(const QKlipperUsbPeripheral &value)
        {
            m_busNumber = value.m_busNumber;
            m_deviceNumber = value.m_deviceNumber;

            m_location = value.m_location;
            m_vendorId = value.m_vendorId;
            m_productId = value.m_productId;
            m_manufacturer = value.m_manufacturer;
            m_product = value.m_product;
            m_className = value.m_className;
            m_subclassName = value.m_subclassName;
            m_protocol = value.m_protocol;
            m_description = value.m_description;
        }

        QKlipperUsbPeripheral &operator=(const QKlipperUsbPeripheral &value)
        {
            m_busNumber = value.m_busNumber;
            m_deviceNumber = value.m_deviceNumber;

            m_location = value.m_location;
            m_vendorId = value.m_vendorId;
            m_productId = value.m_productId;
            m_manufacturer = value.m_manufacturer;
            m_product = value.m_product;
            m_className = value.m_className;
            m_subclassName = value.m_subclassName;
            m_protocol = value.m_protocol;
            m_description = value.m_description;

            return *this;
        }

        bool operator==(const QKlipperUsbPeripheral &value) const
        {
            if(m_busNumber != value.m_busNumber) return false;
            if(m_deviceNumber != value.m_deviceNumber) return false;

            if(m_location != value.m_location) return false;
            if(m_vendorId != value.m_vendorId) return false;
            if(m_productId != value.m_productId) return false;
            if(m_manufacturer != value.m_manufacturer) return false;
            if(m_product != value.m_product) return false;
            if(m_className != value.m_className) return false;
            if(m_subclassName != value.m_subclassName) return false;
            if(m_protocol != value.m_protocol) return false;
            if(m_description != value.m_description) return false;

            return true;
        }

        bool operator!=(const QKlipperUsbPeripheral &value) const { return !(*this == value); }

        qint32 busNumber() const { return m_busNumber; }

        qint32 deviceNumber() const { return m_deviceNumber; }

        QString location() const { return m_location; }

        QString vendorId() const { return m_vendorId; }
        QString productId() const { return m_productId; }
        QString manufacturer() const { return m_manufacturer; }
        QString product() const { return m_product; }
        QString className() const { return m_className; }
        QString subclassName() const { return m_subclassName; }
        QString protocol() const { return m_protocol; }
        QString description() const { return m_description; }

        void setBusNumber(qint32 busNumber) { m_busNumber = busNumber; }
        void setDeviceNumber(qint32 deviceNumber) { m_deviceNumber = deviceNumber; }
        void setLocation(const QString &location) { m_location = location; }
        void setVendorId(const QString &vendorId) { m_vendorId = vendorId; }
        void setProductId(const QString &productId) { m_productId = productId; }
        void setManufacturer(const QString &manufacturer) { m_manufacturer = manufacturer; }
        void setProduct(const QString &product) { m_product = product; }
        void setClassName(const QString &className) { m_className = className; }
        void setSubclassName(const QString &subclassName) { m_subclassName = subclassName; }
        void setProtocol(const QString &protocol) { m_protocol = protocol; }
        void setDescription(const QString &description) { m_description = description; }

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

Q_DECLARE_METATYPE(QKlipperUsbPeripheral)
#endif // QKLIPPERUSBPERIPHERAL_H
