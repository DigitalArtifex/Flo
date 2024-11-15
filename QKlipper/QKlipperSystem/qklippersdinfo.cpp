#include "qklippersdinfo.h"

QKlipperSdInfo::QKlipperSdInfo(QObject *parent)
    : QObject{parent}
{

}

QKlipperSdInfo::QKlipperSdInfo(const QKlipperSdInfo &value)
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

QKlipperSdInfo::QKlipperSdInfo(QKlipperSdInfo &&value)
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

QKlipperSdInfo &QKlipperSdInfo::operator=(const QKlipperSdInfo &value)
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

bool QKlipperSdInfo::operator==(const QKlipperSdInfo &value)
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

bool QKlipperSdInfo::operator==(QKlipperSdInfo &&value)
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

bool QKlipperSdInfo::operator!=(const QKlipperSdInfo &value)
{
    if(m_availableBytes == value.m_availableBytes &&
        m_totalBytes == value.m_totalBytes &&
        m_usedBytes == value.m_usedBytes &&
        m_capacityString == value.m_capacityString &&
        m_manufacturer == value.m_manufacturer &&
        m_manufacturerDate == value.m_manufacturerDate &&
        m_manufacturerId == value.m_manufacturerId &&
        m_oemId == value.m_oemId &&
        m_productName == value.m_productName &&
        m_serialNumber == value.m_serialNumber &&
        m_productRevision == value.m_productRevision)
        return false;

    return false;
}

bool QKlipperSdInfo::operator!=(QKlipperSdInfo &&value)
{
    if(m_availableBytes == value.m_availableBytes &&
        m_totalBytes == value.m_totalBytes &&
        m_usedBytes == value.m_usedBytes &&
        m_capacityString == value.m_capacityString &&
        m_manufacturer == value.m_manufacturer &&
        m_manufacturerDate == value.m_manufacturerDate &&
        m_manufacturerId == value.m_manufacturerId &&
        m_oemId == value.m_oemId &&
        m_productName == value.m_productName &&
        m_serialNumber == value.m_serialNumber &&
        m_productRevision == value.m_productRevision)
        return false;


    return false;
}

QKlipperSdInfo &QKlipperSdInfo::operator=(QKlipperSdInfo &&value)
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

qint64 QKlipperSdInfo::totalBytes() const
{
    return m_totalBytes;
}

void QKlipperSdInfo::setTotalBytes(qint64 totalBytes)
{
    if (m_totalBytes == totalBytes)
        return;
    m_totalBytes = totalBytes;
    emit totalBytesChanged();
}

qint64 QKlipperSdInfo::usedBytes() const
{
    return m_usedBytes;
}

void QKlipperSdInfo::setUsedBytes(qint64 usedBytes)
{
    if (m_usedBytes == usedBytes)
        return;
    m_usedBytes = usedBytes;
    emit usedBytesChanged();
}

qint64 QKlipperSdInfo::availableBytes() const
{
    return m_availableBytes;
}

void QKlipperSdInfo::setAvailableBytes(qint64 availableBytes)
{
    if (m_availableBytes == availableBytes)
        return;
    m_availableBytes = availableBytes;
    emit availableBytesChanged();
}

QString QKlipperSdInfo::manufacturerId() const
{
    return m_manufacturerId;
}

void QKlipperSdInfo::setManufacturerId(const QString &manufacturerId)
{
    if (m_manufacturerId == manufacturerId)
        return;
    m_manufacturerId = manufacturerId;
    emit manufacturerIdChanged();
}

QString QKlipperSdInfo::manufacturer() const
{
    return m_manufacturer;
}

void QKlipperSdInfo::setManufacturer(const QString &manufacturer)
{
    if (m_manufacturer == manufacturer)
        return;
    m_manufacturer = manufacturer;
    emit manufacturerChanged();
}

QString QKlipperSdInfo::oemId() const
{
    return m_oemId;
}

void QKlipperSdInfo::setOemId(const QString &oemId)
{
    if (m_oemId == oemId)
        return;
    m_oemId = oemId;
    emit oemIdChanged();
}

QString QKlipperSdInfo::productName() const
{
    return m_productName;
}

void QKlipperSdInfo::setProductName(const QString &productName)
{
    if (m_productName == productName)
        return;
    m_productName = productName;
    emit productNameChanged();
}

QString QKlipperSdInfo::productRevision() const
{
    return m_productRevision;
}

void QKlipperSdInfo::setProductRevision(const QString &productRevision)
{
    if (m_productRevision == productRevision)
        return;
    m_productRevision = productRevision;
    emit productRevisionChanged();
}

QString QKlipperSdInfo::serialNumber() const
{
    return m_serialNumber;
}

void QKlipperSdInfo::setSerialNumber(const QString &serialNumber)
{
    if (m_serialNumber == serialNumber)
        return;
    m_serialNumber = serialNumber;
    emit serialNumberChanged();
}

QString QKlipperSdInfo::manufacturerDate() const
{
    return m_manufacturerDate;
}

void QKlipperSdInfo::setManufacturerDate(const QString &manufacturerDate)
{
    if (m_manufacturerDate == manufacturerDate)
        return;
    m_manufacturerDate = manufacturerDate;
    emit manufacturerDateChanged();
}

QString QKlipperSdInfo::capacityString() const
{
    return m_capacityString;
}

void QKlipperSdInfo::setCapacityString(const QString &capacityString)
{
    if (m_capacityString == capacityString)
        return;
    m_capacityString = capacityString;
    emit capacityStringChanged();
}
