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

#ifndef QKLIPPERLIBCAMERADEVICE_H
#define QKLIPPERLIBCAMERADEVICE_H

#include <QObject>

#include "qklipperlibcameramode.h"

class QKlipperSystem;
class QKlipperConsole;
/*!
 * \brief Filled by machine.peripherals.serial
 */
class QKlipperLibcameraDevice : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:

    explicit QKlipperLibcameraDevice(QObject *parent = nullptr);

    QKlipperLibcameraDevice(const QKlipperLibcameraDevice &value);
    QKlipperLibcameraDevice(QKlipperLibcameraDevice &&value);
    QKlipperLibcameraDevice &operator=(const QKlipperLibcameraDevice &value);
    QKlipperLibcameraDevice &operator=(QKlipperLibcameraDevice &&value);
    bool operator ==(const QKlipperLibcameraDevice &value) const;
    bool operator==(QKlipperLibcameraDevice &&value);
    bool operator!=(const QKlipperLibcameraDevice &value);
    bool operator!=(QKlipperLibcameraDevice &&value);

    QString id() const;

    QString model() const;

    QList<QKlipperLibCameraMode> modes() const;

public slots:
    void setId(const QString &id);

    void setModel(const QString &model);

    void setModes(const QList<QKlipperLibCameraMode> &modes);

private slots:

signals:

    void idChanged();

    void modelChanged();

    void modesChanged();

private:

    QString m_id;
    QString m_model;

    QList<QKlipperLibCameraMode> m_modes;
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString model READ model WRITE setModel NOTIFY modelChanged FINAL)
    Q_PROPERTY(QList<QKlipperLibCameraMode> modes READ modes WRITE setModes NOTIFY modesChanged FINAL)
};

#endif // QKLIPPERLIBCAMERADEVICE_H
