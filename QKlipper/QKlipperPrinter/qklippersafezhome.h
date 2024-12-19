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

#ifndef QKLIPPERSAFEZHOME_H
#define QKLIPPERSAFEZHOME_H

#include <QObject>

class QKlipperSystem;
class QKlipperConsole;

class QKlipperSafeZHome
{
    friend QKlipperSystem;
    friend QKlipperConsole;

public:
    QKlipperSafeZHome() = default;
    ~QKlipperSafeZHome() = default;

    QKlipperSafeZHome(const QKlipperSafeZHome &value)
    {
        m_homeXPosition = value.m_homeXPosition;
        m_homeYPosition = value.m_homeYPosition;
        m_speed = value.m_speed;
        m_zHopSpeed = value.m_zHopSpeed;
        m_zHop = value.m_zHop;
        m_moveToPrevious = value.m_moveToPrevious;
    }

    QKlipperSafeZHome &operator=(const QKlipperSafeZHome &value)
    {
        m_homeXPosition = value.m_homeXPosition;
        m_homeYPosition = value.m_homeYPosition;
        m_speed = value.m_speed;
        m_zHopSpeed = value.m_zHopSpeed;
        m_zHop = value.m_zHop;
        m_moveToPrevious = value.m_moveToPrevious;

        return *this;
    }

    bool operator==(const QKlipperSafeZHome &value) const
    {
        if(m_homeXPosition != value.m_homeXPosition) return false;
        if(m_homeYPosition != value.m_homeYPosition) return false;
        if(m_speed != value.m_speed) return false;
        if(m_zHop != value.m_zHop) return false;
        if(m_zHopSpeed != value.m_zHopSpeed) return false;

        if(m_moveToPrevious != value.m_moveToPrevious) return false;

        return true;
    }

    bool operator!=(const QKlipperSafeZHome &value) const { return !(*this == value); }

    qreal homeXPosition() const { return m_homeXPosition; }

    qreal homeYPosition() const { return m_homeYPosition; }

    qreal speed() const { return m_speed; }

    qreal zHop() const { return m_zHop; }

    qreal zHopSpeed() const { return m_zHopSpeed; }

    bool moveToPrevious() const { return m_moveToPrevious; }

protected:
    void setHomeXPosition(qreal homeXPosition) { m_homeXPosition = homeXPosition; }

    void setHomeYPosition(qreal homeYPosition) { m_homeYPosition = homeYPosition; }

    void setSpeed(qreal speed) { m_speed = speed; }

    void setZHop(qreal zHop) { m_zHop = zHop; }

    void setZHopSpeed(qreal zHopSpeed) { m_zHopSpeed = zHopSpeed; }

    void setMoveToPrevious(bool moveToPrevious) { m_moveToPrevious = moveToPrevious; }


private:
    qreal m_homeXPosition = 0;
    qreal m_homeYPosition = 0;
    qreal m_speed = 0;
    qreal m_zHop = 0;
    qreal m_zHopSpeed = 0;

    bool m_moveToPrevious = false;
};

Q_DECLARE_METATYPE(QKlipperSafeZHome)

#endif // QKLIPPERSAFEZHOME_H
