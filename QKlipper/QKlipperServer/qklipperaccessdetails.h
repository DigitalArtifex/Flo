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

class QKlipperAccessDetails : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperAccessDetails(QObject *parent = nullptr);
    ~QKlipperAccessDetails();

    QKlipperAccessDetails(const QKlipperAccessDetails &value);
    QKlipperAccessDetails(QKlipperAccessDetails &&value);
    QKlipperAccessDetails &operator=(const QKlipperAccessDetails &value);
    QKlipperAccessDetails &operator=(QKlipperAccessDetails &&value);
    bool operator==(const QKlipperAccessDetails &value);
    bool operator==(QKlipperAccessDetails &&value);
    bool operator!=(const QKlipperAccessDetails &value);
    bool operator!=(QKlipperAccessDetails &&value);

    bool isLoggedIn() const;

    QString token() const;

    QString refreshToken() const;

    QKlipperUser user() const;

public slots:

    void setIsLoggedIn(bool isLoggedIn);

    void setToken(const QString &token);

    void setRefreshToken(const QString &refreshToken);

    void setUser(const QKlipperUser &user);

signals:

    void isLoggedInChanged();

    void tokenChanged();

    void refreshTokenChanged();

    void userChanged();

private:
    bool m_isLoggedIn = false;

    QString m_token;
    QString m_refreshToken;

    QKlipperUser m_user;
    Q_PROPERTY(bool isLoggedIn READ isLoggedIn WRITE setIsLoggedIn NOTIFY isLoggedInChanged FINAL)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged FINAL)
    Q_PROPERTY(QString refreshToken READ refreshToken WRITE setRefreshToken NOTIFY refreshTokenChanged FINAL)
    Q_PROPERTY(QKlipperUser user READ user WRITE setUser NOTIFY userChanged FINAL)
};

#endif // QKLIPPERACCESSDETAILS_H
