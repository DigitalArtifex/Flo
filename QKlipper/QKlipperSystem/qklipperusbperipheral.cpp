#include "qklipperusbperipheral.h"

QKlipperUsbPeripheral::QKlipperUsbPeripheral()
    : QVariant{}
{}

QKlipperUsbPeripheral::QKlipperUsbPeripheral(const QKlipperUsbPeripheral &value)
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

QKlipperUsbPeripheral &QKlipperUsbPeripheral::operator=(const QKlipperUsbPeripheral &value)
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

bool QKlipperUsbPeripheral::operator==(const QKlipperUsbPeripheral &value)
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

bool QKlipperUsbPeripheral::operator!=(const QKlipperUsbPeripheral &value)
{
    if(m_busNumber == value.m_busNumber &&
        m_deviceNumber == value.m_deviceNumber &&
        m_location == value.m_location &&
        m_vendorId == value.m_vendorId &&
        m_productId == value.m_productId &&
        m_manufacturer == value.m_manufacturer &&
        m_product == value.m_product &&
        m_className == value.m_className &&
        m_subclassName == value.m_subclassName &&
        m_protocol == value.m_protocol &&
        m_description == value.m_description)
        return false;

    return true;
}

qint32 QKlipperUsbPeripheral::busNumber() const
{
    return m_busNumber;
}

void QKlipperUsbPeripheral::setBusNumber(qint32 busNumber)
{
    m_busNumber = busNumber;
}

qint32 QKlipperUsbPeripheral::deviceNumber() const
{
    return m_deviceNumber;
}

void QKlipperUsbPeripheral::setDeviceNumber(qint32 deviceNumber)
{
    m_deviceNumber = deviceNumber;
}

QString QKlipperUsbPeripheral::location() const
{
    return m_location;
}

void QKlipperUsbPeripheral::setLocation(const QString &location)
{
    m_location = location;
}

QString QKlipperUsbPeripheral::vendorId() const
{
    return m_vendorId;
}

void QKlipperUsbPeripheral::setVendorId(const QString &vendorId)
{
    m_vendorId = vendorId;
}

QString QKlipperUsbPeripheral::productId() const
{
    return m_productId;
}

void QKlipperUsbPeripheral::setProductId(const QString &productId)
{
    m_productId = productId;
}

QString QKlipperUsbPeripheral::manufacturer() const
{
    return m_manufacturer;
}

void QKlipperUsbPeripheral::setManufacturer(const QString &manufacturer)
{
    m_manufacturer = manufacturer;
}

QString QKlipperUsbPeripheral::product() const
{
    return m_product;
}

void QKlipperUsbPeripheral::setProduct(const QString &product)
{
    m_product = product;
}

QString QKlipperUsbPeripheral::className() const
{
    return m_className;
}

void QKlipperUsbPeripheral::setClassName(const QString &className)
{
    m_className = className;
}

QString QKlipperUsbPeripheral::subclassName() const
{
    return m_subclassName;
}

void QKlipperUsbPeripheral::setSubclassName(const QString &subclassName)
{
    m_subclassName = subclassName;
}

QString QKlipperUsbPeripheral::protocol() const
{
    return m_protocol;
}

void QKlipperUsbPeripheral::setProtocol(const QString &protocol)
{
    m_protocol = protocol;
}

QString QKlipperUsbPeripheral::description() const
{
    return m_description;
}

void QKlipperUsbPeripheral::setDescription(const QString &description)
{
    m_description = description;
}
