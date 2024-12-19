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

#ifndef QKLIPPERACCESSDETAILS_H
#define QKLIPPERACCESSDETAILS_H

#include <QObject>

#include "qklipperuser.h"

class QKlipperSystem;
class QKlipperConsole;

class QKlipperAccessDetails
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperAccessDetails() = default;
    ~QKlipperAccessDetails() = default;

    QKlipperAccessDetails(const QKlipperAccessDetails &value)
    {
        m_isLoggedIn = value.m_isLoggedIn;
        m_refreshToken = value.m_refreshToken;
        m_token = value.m_token;
        m_user = value.m_user;
    }

    inline QKlipperAccessDetails &operator=(const QKlipperAccessDetails &value)
    {
        m_isLoggedIn = value.m_isLoggedIn;
        m_refreshToken = value.m_refreshToken;
        m_token = value.m_token;
        m_user = value.m_user;

        return *this;
    }

    inline bool operator==(const QKlipperAccessDetails &value)
    {
        if(m_isLoggedIn != value.m_isLoggedIn)
            return false;
        if(m_refreshToken != value.m_refreshToken)
            return false;
        if(m_token != value.m_token)
            return false;
        if(m_user != value.m_user)
            return false;

        return true;
    }

    inline bool operator!=(const QKlipperAccessDetails &value) { return !(*this == value); }

    bool isLoggedIn() const { return m_isLoggedIn; }

    const QString token() const { return m_token; }

    const QString refreshToken() const { return m_refreshToken; }

    const QKlipperUser user() const { return m_user; }

protected:

    void setIsLoggedIn(bool isLoggedIn) { m_isLoggedIn = isLoggedIn; }

    void setToken(const QString &token) { m_token = token; }

    void setRefreshToken(const QString &refreshToken) { m_refreshToken = refreshToken; }

    void setUser(const QKlipperUser &user) { m_user = user; }

private:
    bool m_isLoggedIn = false;

    QString m_token;
    QString m_refreshToken;

    QKlipperUser m_user;
};

Q_DECLARE_METATYPE(QKlipperAccessDetails)
#endif // QKLIPPERACCESSDETAILS_H
