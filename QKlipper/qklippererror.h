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
    Q_GADGET
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

    explicit QKlipperError();

    bool operator==(const QKlipperError &value);
    bool operator==(QKlipperError &&value);

    bool operator!=(const QKlipperError &value);
    bool operator!=(QKlipperError &&value);

    QString errorString() const;
    void setErrorString(const QString &errorString);

    QString origin() const;
    void setOrigin(const QString &origin);

    Type type() const;
    void setType(Type type);

    QString errorTitle() const;
    void setErrorTitle(const QString &errorTitle);

    QString id() const;
    void setId(const QString &id);

private:
    QString m_id;
    QString m_errorTitle;
    QString m_errorString;
    QString m_origin;
    Type m_type = NoError;
};

typedef QList<QKlipperError> QKlipperErrorList;

#endif // QKlipperError_H
