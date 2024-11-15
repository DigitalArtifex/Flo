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

class QKlipperSafeZHome : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;

public:
    explicit QKlipperSafeZHome(QObject *parent = nullptr);

    bool operator==(const QKlipperSafeZHome &value);
    bool operator==(QKlipperSafeZHome &&value);
    bool operator!=(const QKlipperSafeZHome &value);
    bool operator!=(QKlipperSafeZHome &&value);

    qreal homeXPosition() const;

    qreal homeYPosition() const;

    qreal speed() const;

    qreal zHop() const;

    qreal zHopSpeed() const;

    bool moveToPrevious() const;

public slots:
    void setHomeXPosition(qreal homeXPosition);

    void setHomeYPosition(qreal homeYPosition);

    void setSpeed(qreal speed);

    void setZHop(qreal zHop);

    void setZHopSpeed(qreal zHopSpeed);

    void setMoveToPrevious(bool moveToPrevious);

private slots:

signals:

    void homeXPositionChanged();

    void homeYPositionChanged();

    void speedChanged();

    void zHopChanged();

    void zHopSpeedChanged();

    void moveToPreviousChanged();

private:
    qreal m_homeXPosition = 0;
    qreal m_homeYPosition = 0;
    qreal m_speed = 0;
    qreal m_zHop = 0;
    qreal m_zHopSpeed = 0;

    bool m_moveToPrevious = false;
    Q_PROPERTY(qreal homeXPosition READ homeXPosition WRITE setHomeXPosition NOTIFY homeXPositionChanged FINAL)
    Q_PROPERTY(qreal homeYPosition READ homeYPosition WRITE setHomeYPosition NOTIFY homeYPositionChanged FINAL)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(qreal zHop READ zHop WRITE setZHop NOTIFY zHopChanged FINAL)
    Q_PROPERTY(qreal zHopSpeed READ zHopSpeed WRITE setZHopSpeed NOTIFY zHopSpeedChanged FINAL)
    Q_PROPERTY(bool moveToPrevious READ moveToPrevious WRITE setMoveToPrevious NOTIFY moveToPreviousChanged FINAL)
};

#endif // QKLIPPERSAFEZHOME_H
