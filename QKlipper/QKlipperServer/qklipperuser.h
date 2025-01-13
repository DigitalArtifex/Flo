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

#ifndef QKLIPPERUSER_H
#define QKLIPPERUSER_H

#include <QObject>

class QKlipperSystem;
class QKlipperConsole;

class QKlipperUser
{

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperUser() = default;
    ~QKlipperUser() = default;
    QKlipperUser(const QKlipperUser &user)
    {
        m_username = user.m_username;
        m_createdOn = user.m_createdOn;
        m_source = user.m_source;
    }

    bool operator==(const QKlipperUser &user) const
    {
        if(m_username != user.m_username)
            return false;
        if(m_createdOn != user.m_createdOn)
            return false;
        if(m_source != user.m_source)
            return false;

        return true;
    }
    bool operator!=(const QKlipperUser &user) const { return !(*this == user); }

    QKlipperUser &operator=(const QKlipperUser &user)
    {
        m_username = user.m_username;
        m_createdOn = user.m_createdOn;
        m_source = user.m_source;

        return (*this);
    }

    QString username() const { return m_username; }

    QString source() const { return m_source; }

    qreal createdOn() const { return m_createdOn; }

    void setUsername(const QString &username) { m_username = username; }

    void setSource(const QString &source) { m_source = source; }

    void setCreatedOn(qreal createdOn) { m_createdOn = createdOn; }

private:
    QString m_username;
    QString m_source;

    qreal m_createdOn;
};

typedef QList<QKlipperUser> QKlipperUserList;

Q_DECLARE_METATYPE(QKlipperUser)

#endif // QKLIPPERUSER_H
