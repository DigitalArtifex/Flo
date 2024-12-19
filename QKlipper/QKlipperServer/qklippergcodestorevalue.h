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

#ifndef QKLIPPERGCODESTOREVALUE_H
#define QKLIPPERGCODESTOREVALUE_H

#include <QObject>
#include <QVariant>
#include <QList>

class QKlipperGCodeStoreValue
{
public:
    enum GCodeType {
        Command,
        Response
    };

    QKlipperGCodeStoreValue() = default;
    ~QKlipperGCodeStoreValue() = default;

    QKlipperGCodeStoreValue(const QKlipperGCodeStoreValue &value)
    {
        m_gcodeType = value.m_gcodeType;
        m_message = value.m_message;
        m_time = value.m_time;
    }

    QKlipperGCodeStoreValue &operator=(const QKlipperGCodeStoreValue &value)
    {
        m_gcodeType = value.m_gcodeType;
        m_message = value.m_message;
        m_time = value.m_time;

        return *this;
    }

    bool operator==(const QKlipperGCodeStoreValue &value) const
    {
        if(m_gcodeType == value.m_gcodeType &&
            m_time == value.m_time &&
            m_message == value.m_message)
            return true;

        return false;
    }

    bool operator!=(const QKlipperGCodeStoreValue &value) const { return !(*this == value); }

    QString message() const { return m_message; }

    GCodeType gcodeType() const { return m_gcodeType; }

    qreal time() const { return m_time; }

    void setMessage(const QString &message) { m_message = message; }

    void setGcodeType(GCodeType gcodeType) { m_gcodeType = gcodeType; }

    void setTime(qreal time) { m_time = time; }

private:

    QString m_message;
    GCodeType m_gcodeType = Response;
    qreal m_time;
};


Q_DECLARE_METATYPE(QKlipperGCodeStoreValue)
#endif // QKLIPPERGCODESTOREVALUE_H
