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

#ifndef QKLIPPERSDINFO_H
#define QKLIPPERSDINFO_H

#include <QObject>
class QKlipperSystem;
class QKlipperConsole;
/*!
 * \brief Filled by machine.system_info
 */
class QKlipperSdInfo
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperSdInfo() = default;
    ~QKlipperSdInfo() = default;

    QKlipperSdInfo(const QKlipperSdInfo &value)
    {
        m_availableBytes = value.m_availableBytes;
        m_totalBytes = value.m_totalBytes;
        m_usedBytes = value.m_usedBytes;
        m_capacityString = value.m_capacityString;
        m_manufacturer = value.m_manufacturer;
        m_manufacturerDate = value.m_manufacturerDate;
        m_manufacturerId = value.m_manufacturerId;
        m_oemId = value.m_oemId;
        m_productName = value.m_productName;
        m_serialNumber = value.m_serialNumber;
        m_productRevision = value.m_productRevision;
    }

    QKlipperSdInfo &operator=(const QKlipperSdInfo &value)
    {
        m_availableBytes = value.m_availableBytes;
        m_totalBytes = value.m_totalBytes;
        m_usedBytes = value.m_usedBytes;
        m_capacityString = value.m_capacityString;
        m_manufacturer = value.m_manufacturer;
        m_manufacturerDate = value.m_manufacturerDate;
        m_manufacturerId = value.m_manufacturerId;
        m_oemId = value.m_oemId;
        m_productName = value.m_productName;
        m_serialNumber = value.m_serialNumber;
        m_productRevision = value.m_productRevision;

        return *this;
    }

    bool operator==(const QKlipperSdInfo &value)
    {
        if(m_availableBytes != value.m_availableBytes) return false;
        if(m_totalBytes != value.m_totalBytes) return false;
        if(m_usedBytes != value.m_usedBytes) return false;
        if(m_capacityString != value.m_capacityString) return false;
        if(m_manufacturer != value.m_manufacturer) return false;
        if(m_manufacturerDate != value.m_manufacturerDate) return false;
        if(m_manufacturerId != value.m_manufacturerId) return false;
        if(m_oemId != value.m_oemId) return false;
        if(m_productName != value.m_productName) return false;
        if(m_serialNumber != value.m_serialNumber) return false;
        if(m_productRevision != value.m_productRevision) return false;

        return false;
    }

    bool operator!=(const QKlipperSdInfo &value) { return !(*this == value); }

    qint64 totalBytes() const { return m_totalBytes; }

    qint64 usedBytes() const { return m_usedBytes; }

    qint64 availableBytes() const { return m_availableBytes; }

    QString manufacturerId() const { return m_manufacturerId; }

    QString manufacturer() const { return m_manufacturer; }

    QString oemId() const { return m_oemId; }

    QString productName() const { return m_productName; }

    QString productRevision() const { return m_productRevision; }

    QString serialNumber() const { return m_serialNumber; }

    QString manufacturerDate() const { return m_manufacturerDate; }

    QString capacityString() const { return m_capacityString; }

protected:

    void setTotalBytes(qint64 totalBytes) { m_totalBytes = totalBytes; }

    void setUsedBytes(qint64 usedBytes) { m_usedBytes = usedBytes; }

    void setAvailableBytes(qint64 availableBytes) { m_availableBytes = availableBytes; }

    void setManufacturerId(const QString &manufacturerId) { m_manufacturerId = manufacturerId; }

    void setManufacturer(const QString &manufacturer) { m_manufacturer = manufacturer; }

    void setOemId(const QString &oemId) { m_oemId = oemId; }

    void setProductName(const QString &productName) { m_productName = productName; }

    void setProductRevision(const QString &productRevision) { m_productRevision = productRevision; }

    void setSerialNumber(const QString &serialNumber) { m_serialNumber = serialNumber; }

    void setManufacturerDate(const QString &manufacturerDate) { m_manufacturerDate = manufacturerDate; }

    void setCapacityString(const QString &capacityString) { m_capacityString = capacityString; }

private:
    qint64 m_totalBytes = 0;
    qint64 m_usedBytes = 0;
    qint64 m_availableBytes = 0;

    QString m_manufacturerId;
    QString m_manufacturer;
    QString m_oemId;
    QString m_productName;
    QString m_productRevision;
    QString m_serialNumber;
    QString m_manufacturerDate;
    QString m_capacityString;
};

Q_DECLARE_METATYPE(QKlipperSdInfo)

#endif // QKLIPPERSDINFO_H
