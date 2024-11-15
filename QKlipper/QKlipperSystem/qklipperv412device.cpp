#include "qklipperv412device.h"

QKlipperV412Device::QKlipperV412Device()
    : QVariant{}
{}

QKlipperV412Device::QKlipperV412Device(const QKlipperV412Device &value)
{
    m_name = value.m_name;
    m_path = value.m_path;
    m_cameraName = value.m_cameraName;
    m_driver = value.m_driver;
    m_altName = value.m_altName;
    m_hardwareBus = value.m_hardwareBus;
    m_version = value.m_version;
    m_hardwarePath = value.m_hardwarePath;
    m_pathById = value.m_pathById;
    m_usbLocation = value.m_usbLocation;

    m_capabilities = value.m_capabilities;
    m_modes = value.m_modes;
}

QKlipperV412Device &QKlipperV412Device::operator=(const QKlipperV412Device &value)
{
    m_name = value.m_name;
    m_path = value.m_path;
    m_cameraName = value.m_cameraName;
    m_driver = value.m_driver;
    m_altName = value.m_altName;
    m_hardwareBus = value.m_hardwareBus;
    m_version = value.m_version;
    m_hardwarePath = value.m_hardwarePath;
    m_pathById = value.m_pathById;
    m_usbLocation = value.m_usbLocation;

    m_capabilities = value.m_capabilities;
    m_modes = value.m_modes;

    return *this;
}

bool QKlipperV412Device::operator==(const QKlipperV412Device &value)
{
    if(m_name != value.m_name) return false;
    if(m_path != value.m_path) return false;
    if(m_cameraName != value.m_cameraName) return false;
    if(m_driver != value.m_driver) return false;
    if(m_altName != value.m_altName) return false;
    if(m_hardwareBus != value.m_hardwareBus) return false;
    if(m_version != value.m_version) return false;
    if(m_hardwarePath != value.m_hardwarePath) return false;
    if(m_pathById != value.m_pathById) return false;
    if(m_usbLocation != value.m_usbLocation) return false;

    if(m_capabilities != value.m_capabilities) return false;

    for(QKlipperV412Mode mode : value.m_modes)
    {
        if(!m_modes.contains(mode))
            return false;
    }

    return true;
}

bool QKlipperV412Device::operator!=(const QKlipperV412Device &value)
{
    for(QKlipperV412Mode mode : value.m_modes)
    {
        if(!m_modes.contains(mode))
            return true;
    }

    if(m_name == value.m_name &&
        m_path == value.m_path &&
        m_cameraName == value.m_cameraName &&
        m_driver == value.m_driver &&
        m_altName == value.m_altName &&
        m_hardwareBus == value.m_hardwareBus &&
        m_version == value.m_version &&
        m_hardwarePath == value.m_hardwarePath &&
        m_pathById == value.m_pathById &&
        m_usbLocation == value.m_usbLocation &&
        m_capabilities == value.m_capabilities)
        return false;

    return true;
}

QString QKlipperV412Device::name() const
{
    return m_name;
}

void QKlipperV412Device::setName(const QString &name)
{
    m_name = name;
}

QString QKlipperV412Device::path() const
{
    return m_path;
}

void QKlipperV412Device::setPath(const QString &path)
{
    m_path = path;
}

QString QKlipperV412Device::cameraName() const
{
    return m_cameraName;
}

void QKlipperV412Device::setCameraName(const QString &cameraName)
{
    m_cameraName = cameraName;
}

QString QKlipperV412Device::driver() const
{
    return m_driver;
}

void QKlipperV412Device::setDriver(const QString &driver)
{
    m_driver = driver;
}

QString QKlipperV412Device::altName() const
{
    return m_altName;
}

void QKlipperV412Device::setAltName(const QString &altName)
{
    m_altName = altName;
}

QString QKlipperV412Device::hardwareBus() const
{
    return m_hardwareBus;
}

void QKlipperV412Device::setHardwareBus(const QString &hardwareBus)
{
    m_hardwareBus = hardwareBus;
}

QString QKlipperV412Device::version() const
{
    return m_version;
}

void QKlipperV412Device::setVersion(const QString &version)
{
    m_version = version;
}

QString QKlipperV412Device::hardwarePath() const
{
    return m_hardwarePath;
}

void QKlipperV412Device::setHardwarePath(const QString &hardwarePath)
{
    m_hardwarePath = hardwarePath;
}

QString QKlipperV412Device::pathById() const
{
    return m_pathById;
}

void QKlipperV412Device::setPathById(const QString &pathById)
{
    m_pathById = pathById;
}

QString QKlipperV412Device::usbLocation() const
{
    return m_usbLocation;
}

void QKlipperV412Device::setUsbLocation(const QString &usbLocation)
{
    m_usbLocation = usbLocation;
}

QStringList QKlipperV412Device::capabilities() const
{
    return m_capabilities;
}

void QKlipperV412Device::setCapabilities(const QStringList &capabilities)
{
    m_capabilities = capabilities;
}

QList<QKlipperV412Mode> QKlipperV412Device::modes() const
{
    return m_modes;
}

void QKlipperV412Device::setModes(const QList<QKlipperV412Mode> &modes)
{
    bool changed = false;

    for(QKlipperV412Mode mode : modes)
    {
        if(!m_modes.contains(mode))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_modes = modes;
}
