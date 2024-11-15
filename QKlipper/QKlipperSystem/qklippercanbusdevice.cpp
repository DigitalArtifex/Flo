#include "qklippercanbusdevice.h"

QKlipperCanBusDevice::QKlipperCanBusDevice(QObject *parent)
    : QObject{parent}
{

}

QKlipperCanBusDevice::QKlipperCanBusDevice(const QKlipperCanBusDevice &value)
{
    m_bitrate = value.m_bitrate;
    m_driver = value.m_driver;
    m_queueLength = value.m_queueLength;
}

QKlipperCanBusDevice::QKlipperCanBusDevice(QKlipperCanBusDevice &&value)
{
    m_bitrate = value.m_bitrate;
    m_driver = value.m_driver;
    m_queueLength = value.m_queueLength;
}

QKlipperCanBusDevice &QKlipperCanBusDevice::operator=(const QKlipperCanBusDevice &value)
{
    m_bitrate = value.m_bitrate;
    m_driver = value.m_driver;
    m_queueLength = value.m_queueLength;

    return *this;
}

QKlipperCanBusDevice &QKlipperCanBusDevice::operator=(QKlipperCanBusDevice &&value)
{
    m_bitrate = value.m_bitrate;
    m_driver = value.m_driver;
    m_queueLength = value.m_queueLength;

    return *this;
}

bool QKlipperCanBusDevice::operator==(const QKlipperCanBusDevice &value)
{
    if(m_bitrate != value.m_bitrate) return false;
    if(m_driver != value.m_driver) return false;
    if(m_queueLength != value.m_queueLength) return false;

    return true;
}

bool QKlipperCanBusDevice::operator==(QKlipperCanBusDevice &&value)
{
    if(m_bitrate != value.m_bitrate) return false;
    if(m_driver != value.m_driver) return false;
    if(m_queueLength != value.m_queueLength) return false;

    return true;
}

bool QKlipperCanBusDevice::operator!=(const QKlipperCanBusDevice &value)
{
    if(m_bitrate == value.m_bitrate &&
        m_driver == value.m_driver &&
        m_queueLength == value.m_queueLength)
        return false;

    return true;
}

bool QKlipperCanBusDevice::operator!=(QKlipperCanBusDevice &&value)
{
    if(m_bitrate == value.m_bitrate &&
        m_driver == value.m_driver &&
        m_queueLength == value.m_queueLength)
        return false;

    return true;
}

qint16 QKlipperCanBusDevice::queueLength() const
{
    return m_queueLength;
}

void QKlipperCanBusDevice::setQueueLength(qint16 queueLength)
{
    if (m_queueLength == queueLength)
        return;

    m_queueLength = queueLength;
    emit queueLengthChanged();
}

qint32 QKlipperCanBusDevice::bitrate() const
{
    return m_bitrate;
}

void QKlipperCanBusDevice::setBitrate(qint32 bitrate)
{
    if (m_bitrate == bitrate)
        return;
    m_bitrate = bitrate;
    emit bitrateChanged();
}

QString QKlipperCanBusDevice::driver() const
{
    return m_driver;
}

void QKlipperCanBusDevice::setDriver(const QString &driver)
{
    if (m_driver == driver)
        return;
    m_driver = driver;
    emit driverChanged();
}
