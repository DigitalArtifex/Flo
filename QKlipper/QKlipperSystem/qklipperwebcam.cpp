#include "qklipperwebcam.h"

QKlipperWebcam::QKlipperWebcam()
    : QVariant{}
{}

QKlipperWebcam::QKlipperWebcam(const QKlipperWebcam &value)
{
    m_name = value.m_name;
    m_location = value.m_location;
    m_service = value.m_service;
    m_iconString = value.m_iconString;
    m_streamUrl = value.m_streamUrl;
    m_snapshotUrl = value.m_snapshotUrl;
    m_aspectRatio = value.m_aspectRatio;
    m_source = value.m_source;
    m_uid = value.m_uid;

    m_targetFps = value.m_targetFps;
    m_targetFpsIdle = value.m_targetFpsIdle;
    m_rotation = value.m_rotation;

    m_enabled = value.m_enabled;
    m_flipVertical = value.m_flipVertical;
    m_flipHorizontal = value.m_flipHorizontal;
}

QKlipperWebcam &QKlipperWebcam::operator=(const QKlipperWebcam &value)
{
    m_name = value.m_name;
    m_location = value.m_location;
    m_service = value.m_service;
    m_iconString = value.m_iconString;
    m_streamUrl = value.m_streamUrl;
    m_snapshotUrl = value.m_snapshotUrl;
    m_aspectRatio = value.m_aspectRatio;
    m_source = value.m_source;
    m_uid = value.m_uid;

    m_targetFps = value.m_targetFps;
    m_targetFpsIdle = value.m_targetFpsIdle;
    m_rotation = value.m_rotation;

    m_enabled = value.m_enabled;
    m_flipVertical = value.m_flipVertical;
    m_flipHorizontal = value.m_flipHorizontal;

    return *this;
}

bool QKlipperWebcam::operator==(const QKlipperWebcam &value)
{
    if(m_name != value.m_name) return false;
    if(m_location != value.m_location) return false;
    if(m_service != value.m_service) return false;
    if(m_iconString != value.m_iconString) return false;
    if(m_streamUrl != value.m_streamUrl) return false;
    if(m_snapshotUrl != value.m_snapshotUrl) return false;
    if(m_aspectRatio != value.m_aspectRatio) return false;
    if(m_source != value.m_source) return false;
    if(m_uid != value.m_uid) return false;

    if(m_targetFps != value.m_targetFps) return false;
    if(m_targetFpsIdle != value.m_targetFpsIdle) return false;
    if(m_rotation != value.m_rotation) return false;

    if(m_enabled != value.m_enabled) return false;
    if(m_flipVertical != value.m_flipVertical) return false;
    if(m_flipHorizontal != value.m_flipHorizontal) return false;

    return true;
}

bool QKlipperWebcam::operator!=(const QKlipperWebcam &value)
{
    if(m_name == value.m_name &&
        m_location == value.m_location &&
        m_service == value.m_service &&
        m_iconString == value.m_iconString &&
        m_streamUrl == value.m_streamUrl &&
        m_snapshotUrl == value.m_snapshotUrl &&
        m_aspectRatio == value.m_aspectRatio &&
        m_source == value.m_source &&
        m_uid == value.m_uid &&
        m_targetFps == value.m_targetFps &&
        m_targetFpsIdle == value.m_targetFpsIdle &&
        m_rotation == value.m_rotation &&
        m_enabled == value.m_enabled &&
        m_flipVertical == value.m_flipVertical &&
        m_flipHorizontal == value.m_flipHorizontal)
        return false;

    return true;
}

QString QKlipperWebcam::name() const
{
    return m_name;
}

void QKlipperWebcam::setName(const QString &name)
{
    m_name = name;
}

QString QKlipperWebcam::location() const
{
    return m_location;
}

void QKlipperWebcam::setLocation(const QString &location)
{
    m_location = location;
}

QString QKlipperWebcam::service() const
{
    return m_service;
}

void QKlipperWebcam::setService(const QString &service)
{
    m_service = service;
}

QString QKlipperWebcam::iconString() const
{
    return m_iconString;
}

void QKlipperWebcam::setIconString(const QString &iconString)
{
    m_iconString = iconString;
}

QString QKlipperWebcam::streamUrl() const
{
    return m_streamUrl;
}

void QKlipperWebcam::setStreamUrl(const QString &streamUrl)
{
    m_streamUrl = streamUrl;
}

QString QKlipperWebcam::snapshotUrl() const
{
    return m_snapshotUrl;
}

void QKlipperWebcam::setSnapshotUrl(const QString &snapshotUrl)
{
    m_snapshotUrl = snapshotUrl;
}

QString QKlipperWebcam::aspectRatio() const
{
    return m_aspectRatio;
}

void QKlipperWebcam::setAspectRatio(const QString &aspectRatio)
{
    m_aspectRatio = aspectRatio;
}

QString QKlipperWebcam::source() const
{
    return m_source;
}

void QKlipperWebcam::setSource(const QString &source)
{
    m_source = source;
}

QString QKlipperWebcam::uid() const
{
    return m_uid;
}

void QKlipperWebcam::setUid(const QString &uid)
{
    m_uid = uid;
}

qint16 QKlipperWebcam::targetFps() const
{
    return m_targetFps;
}

void QKlipperWebcam::setTargetFps(qint16 targetFps)
{
    m_targetFps = targetFps;
}

qint16 QKlipperWebcam::rotation() const
{
    return m_rotation;
}

void QKlipperWebcam::setRotation(qint16 rotation)
{
    m_rotation = rotation;
}

bool QKlipperWebcam::enabled() const
{
    return m_enabled;
}

void QKlipperWebcam::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool QKlipperWebcam::flipVertical() const
{
    return m_flipVertical;
}

void QKlipperWebcam::setFlipVertical(bool flipVertical)
{
    m_flipVertical = flipVertical;
}

bool QKlipperWebcam::flipHorizontal() const
{
    return m_flipHorizontal;
}

void QKlipperWebcam::setFlipHorizontal(bool flipHorizontal)
{
    m_flipHorizontal = flipHorizontal;
}

qint16 QKlipperWebcam::targetFpsIdle() const
{
    return m_targetFpsIdle;
}

void QKlipperWebcam::setTargetFpsIdle(qint16 targetFpsIdle)
{
    m_targetFpsIdle = targetFpsIdle;
}
