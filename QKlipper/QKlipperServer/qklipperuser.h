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

class QKlipperUser : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperUser(QObject *parent = nullptr);

    QKlipperUser(const QKlipperUser &value);
    QKlipperUser(QKlipperUser &&value);
    QKlipperUser &operator=(const QKlipperUser &value);
    QKlipperUser &operator=(QKlipperUser &&value);
    bool operator==(const QKlipperUser &value);
    bool operator==(QKlipperUser &&value);
    bool operator!=(const QKlipperUser &value);
    bool operator!=(QKlipperUser &&value);

    QString username() const;

    QString source() const;

    qreal createdOn() const;

public slots:
    void setUsername(const QString &username);

    void setSource(const QString &source);

    void setCreatedOn(qreal createdOn);

signals:

    void usernameChanged();

    void sourceChanged();

    void createdOnChanged();

private:
    QString m_username;
    QString m_source;

    qreal m_createdOn;

    Q_PROPERTY(QString username READ username NOTIFY usernameChanged FINAL)
    Q_PROPERTY(QString source READ source NOTIFY sourceChanged FINAL)
    Q_PROPERTY(qreal createdOn READ createdOn NOTIFY createdOnChanged FINAL)
};

typedef QList<QKlipperUser> QKlipperUserList;

#endif // QKLIPPERUSER_H
