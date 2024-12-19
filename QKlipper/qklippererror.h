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

#ifndef QKlipperError_H
#define QKlipperError_H

#include <QObject>
#include <QUuid>

class QKlipperError
{
public:

    enum Type
    {
        Unspecified = 0,
        Command = 1,
        Socket = 2,
        File = 3,
        Klipper = 4,
        Moonraker = 5,
        NoError = 6
    };

    explicit QKlipperError() { m_id = QUuid::createUuid().toString(); }
    ~QKlipperError() = default;

    QKlipperError(const QKlipperError &value)
    {
        m_id = value.m_id;
        m_errorString = value.m_errorString;
        m_errorTitle = value.m_errorTitle;
        m_origin = value.m_origin;
        m_type = value.m_type;
    }

    bool operator==(const QKlipperError &value) const
    {
        if(m_id != value.m_id)
            return false;

        if(m_errorString != value.m_errorString)
            return false;

        if(m_origin != value.m_origin)
            return false;

        if(m_type != value.m_type)
            return false;

        if(m_errorTitle != value.m_errorTitle)
            return false;

        return true;
    }

    bool operator!=(const QKlipperError &value) const { return !(*this == value); }

    QString errorString() const { return m_errorString; }
    void setErrorString(const QString &errorString) { m_errorString = errorString; }

    QString origin() const { return m_origin; }
    void setOrigin(const QString &origin) { m_origin = origin; }

    Type type() const { return m_type; }
    void setType(Type type) { m_type = type; }

    QString errorTitle() const { return m_errorTitle; }
    void setErrorTitle(const QString &errorTitle) { m_errorTitle = errorTitle; }

    QString id() const { return m_id; }
    void setId(const QString &id) { m_id = id; }

private:
    QString m_id;
    QString m_errorTitle;
    QString m_errorString;
    QString m_origin;
    Type m_type = NoError;
};

typedef QList<QKlipperError> QKlipperErrorList;

#endif // QKlipperError_H
