#include "qklipperlibcameradevice.h"

QKlipperLibcameraDevice::QKlipperLibcameraDevice(QObject *parent)
    : QObject{parent}
{}

QKlipperLibcameraDevice::QKlipperLibcameraDevice(const QKlipperLibcameraDevice &value): QObject{value.parent()}
{
    m_id = value.m_id;
    m_model = value.m_model;
    m_modes = value.m_modes;
}

QKlipperLibcameraDevice::QKlipperLibcameraDevice(QKlipperLibcameraDevice &&value)
{
    m_id = value.m_id;
    m_model = value.m_model;
    m_modes = value.m_modes;
}

QKlipperLibcameraDevice &QKlipperLibcameraDevice::operator=(const QKlipperLibcameraDevice &value)
{
    m_id = value.m_id;
    m_model = value.m_model;
    m_modes = value.m_modes;

    return *this;
}

QKlipperLibcameraDevice &QKlipperLibcameraDevice::operator=(QKlipperLibcameraDevice &&value)
{
    m_id = value.m_id;
    m_model = value.m_model;
    m_modes = value.m_modes;

    return *this;
}

bool QKlipperLibcameraDevice::operator==(const QKlipperLibcameraDevice &value) const
{
    if(m_id != value.m_id) return false;
    if(m_model != value.m_model) return false;

    foreach(const QKlipperLibCameraMode &mode, value.modes())
    {
        if(!m_modes.contains(mode))
            return false;
    }

    return true;
}

bool QKlipperLibcameraDevice::operator==(QKlipperLibcameraDevice &&value)
{
    if(m_id != value.m_id) return false;
    if(m_model != value.m_model) return false;

    foreach(QKlipperLibCameraMode mode, value.m_modes)
    {
        if(!m_modes.contains(mode))
            return false;
    }

    return true;
}

bool QKlipperLibcameraDevice::operator!=(const QKlipperLibcameraDevice &value)
{
    foreach(QKlipperLibCameraMode mode, value.m_modes)
    {
        if(!m_modes.contains(mode))
            return true;
    }

    if(m_id == value.m_id &&
        m_model == value.m_model &&
        m_modes.count() == value.m_modes.count())
        return false;

    return true;
}

bool QKlipperLibcameraDevice::operator!=(QKlipperLibcameraDevice &&value)
{
    foreach(QKlipperLibCameraMode mode, value.m_modes)
    {
        if(!m_modes.contains(mode))
            return true;
    }

    if(m_id == value.m_id &&
        m_model == value.m_model &&
        m_modes.count() == value.m_modes.count())
        return false;

    return true;
}

QString QKlipperLibcameraDevice::id() const
{
    return m_id;
}

void QKlipperLibcameraDevice::setId(const QString &id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

QString QKlipperLibcameraDevice::model() const
{
    return m_model;
}

void QKlipperLibcameraDevice::setModel(const QString &model)
{
    if (m_model == model)
        return;

    m_model = model;
    emit modelChanged();
}

QList<QKlipperLibCameraMode> QKlipperLibcameraDevice::modes() const
{
    return m_modes;
}

void QKlipperLibcameraDevice::setModes(const QList<QKlipperLibCameraMode> &modes)
{
    bool changed = false;

    foreach(QKlipperLibCameraMode mode, modes)
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
    emit modesChanged();
}
