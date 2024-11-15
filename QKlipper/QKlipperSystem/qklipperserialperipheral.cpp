#include "qklipperserialperipheral.h"

QKlipperSerialPeripheral::QKlipperSerialPeripheral()
    : QVariant{}
{}

QKlipperSerialPeripheral::QKlipperSerialPeripheral(const QKlipperSerialPeripheral &value)
{
    m_type = value.m_type;
    m_path = value.m_path;
    m_name = value.m_name;
    m_driver = value.m_driver;
    m_hardwarePath = value.m_hardwarePath;
    m_pathById = value.m_pathById;
    m_usbLocation = value.m_usbLocation;
}

QKlipperSerialPeripheral &QKlipperSerialPeripheral::operator=(const QKlipperSerialPeripheral &value)
{
    m_type = value.m_type;
    m_path = value.m_path;
    m_name = value.m_name;
    m_driver = value.m_driver;
    m_hardwarePath = value.m_hardwarePath;
    m_pathById = value.m_pathById;
    m_usbLocation = value.m_usbLocation;

    return *this;
}

bool QKlipperSerialPeripheral::operator==(const QKlipperSerialPeripheral &value)
{
    if(m_type != value.m_type) return false;
    if(m_path != value.m_path) return false;
    if(m_name != value.m_name) return false;
    if(m_driver != value.m_driver) return false;
    if(m_hardwarePath != value.m_hardwarePath) return false;
    if(m_pathById != value.m_pathById) return false;
    if(m_usbLocation != value.m_usbLocation) return false;

    return true;
}

bool QKlipperSerialPeripheral::operator!=(const QKlipperSerialPeripheral &value)
{
    if(m_type == value.m_type &&
        m_path == value.m_path &&
        m_name == value.m_name &&
        m_driver == value.m_driver &&
        m_hardwarePath == value.m_hardwarePath &&
        m_pathById == value.m_pathById &&
        m_usbLocation == value.m_usbLocation)
        return false;

    return true;
}

QString QKlipperSerialPeripheral::type() const
{
    return m_type;
}

void QKlipperSerialPeripheral::setType(const QString &type)
{
    m_type = type;
}

QString QKlipperSerialPeripheral::path() const
{
    return m_path;
}

void QKlipperSerialPeripheral::setPath(const QString &path)
{
    m_path = path;
}

QString QKlipperSerialPeripheral::name() const
{
    return m_name;
}

void QKlipperSerialPeripheral::setName(const QString &name)
{
    m_name = name;
}

QString QKlipperSerialPeripheral::driver() const
{
    return m_driver;
}

void QKlipperSerialPeripheral::setDriver(const QString &driver)
{
    m_driver = driver;
}

QString QKlipperSerialPeripheral::hardwarePath() const
{
    return m_hardwarePath;
}

void QKlipperSerialPeripheral::setHardwarePath(const QString &hardwarePath)
{
    m_hardwarePath = hardwarePath;
}

QString QKlipperSerialPeripheral::pathById() const
{
    return m_pathById;
}

void QKlipperSerialPeripheral::setPathById(const QString &pathById)
{
    m_pathById = pathById;
}

QString QKlipperSerialPeripheral::usbLocation() const
{
    return m_usbLocation;
}

void QKlipperSerialPeripheral::setUsbLocation(const QString &usbLocation)
{
    m_usbLocation = usbLocation;
}
