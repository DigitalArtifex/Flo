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

#ifndef QKLIPPERWEBCAM_H
#define QKLIPPERWEBCAM_H

#include <QObject>
#include <QVariant>

class QKlipperSystem;
class QKlipperConsole;

class QKlipperWebcam
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperWebcam() = default;
    ~QKlipperWebcam() = default;

    QKlipperWebcam(const QKlipperWebcam &value)
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

    QKlipperWebcam &operator=(const QKlipperWebcam &value)
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

    bool operator==(const QKlipperWebcam &value) const
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

    bool operator!=(const QKlipperWebcam &value) const { return !(*this == value); }

    QString name() const { return m_name; }

    QString location() const { return m_location; }

    QString service() const { return m_service; }

    QString iconString() const { return m_iconString; }

    QString streamUrl() const { return m_streamUrl; }

    QString snapshotUrl() const { return m_snapshotUrl; }

    QString aspectRatio() const { return m_aspectRatio; }

    QString source() const { return m_source; }

    QString uid() const { return m_uid; }

    qint16 targetFps() const { return m_targetFps; }

    qint16 rotation() const { return m_rotation; }

    bool enabled() const { return m_enabled; }

    bool flipVertical() const { return m_flipVertical; }

    bool flipHorizontal() const { return m_flipHorizontal; }

    qint16 targetFpsIdle() const { return m_targetFpsIdle; }

    void setName(const QString &name) { m_name = name; }

    void setLocation(const QString &location) { m_location = location; }

    void setService(const QString &service) { m_service = service; }

    void setIconString(const QString &iconString) { m_iconString = iconString; }

    void setStreamUrl(const QString &streamUrl) { m_streamUrl = streamUrl; }

    void setSnapshotUrl(const QString &snapshotUrl) { m_snapshotUrl = snapshotUrl; }

    void setAspectRatio(const QString &aspectRatio) { m_aspectRatio = aspectRatio; }

    void setSource(const QString &source) { m_source = source; }

    void setUid(const QString &uid) { m_uid = uid; }

    void setTargetFps(qint16 targetFps) { m_targetFps = targetFps; }

    void setRotation(qint16 rotation) { m_rotation = rotation; }

    void setEnabled(bool enabled) { m_enabled = enabled; }

    void setFlipVertical(bool flipVertical) { m_flipVertical = flipVertical; }

    void setFlipHorizontal(bool flipHorizontal) { m_flipHorizontal = flipHorizontal; }

    void setTargetFpsIdle(qint16 targetFpsIdle) { m_targetFpsIdle = targetFpsIdle; }

private:
    QString m_name;
    QString m_location;
    QString m_service;
    QString m_iconString;
    QString m_streamUrl;
    QString m_snapshotUrl;
    QString m_aspectRatio;
    QString m_source;
    QString m_uid;

    qint16 m_targetFps = 0;
    qint16 m_targetFpsIdle = 0;
    qint16 m_rotation = 0;

    bool m_enabled = false;
    bool m_flipVertical = false;
    bool m_flipHorizontal = false;
};

Q_DECLARE_METATYPE(QKlipperWebcam)
typedef QList<QKlipperWebcam> QKlipperWebcamList;

#endif // QKLIPPERWEBCAM_H
