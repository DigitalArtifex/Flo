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

#ifndef QKLIPPERGCODEMOVE_H
#define QKLIPPERGCODEMOVE_H

#include <QObject>

#include "qklipperposition.h"

class QKlipperGCodeMove
{
    Q_GADGET

public:
    bool absoluteCoordinates = false;
    bool absoluteExtrude = false;

    qreal extrusionFactor = 0;
    qreal speedFactor = 0;
    qreal speed = 0;

    QKlipperPosition gcodePosition;
    QKlipperPosition homingOrigin;
    QKlipperPosition position;

    bool operator==(const QKlipperGCodeMove &move)
    {
        if(absoluteCoordinates != move.absoluteCoordinates) return false;
        if(absoluteExtrude != move.absoluteExtrude) return false;

        if(extrusionFactor != move.extrusionFactor) return false;
        if(speedFactor != move.speedFactor) return false;
        if(speed != move.speed) return false;

        if(gcodePosition != move.gcodePosition) return false;
        if(homingOrigin != move.homingOrigin) return false;
        if(position != move.position) return false;

        return true;
    }

    bool operator!=(const QKlipperGCodeMove &move)
    {
        if(absoluteCoordinates == move.absoluteCoordinates &&
            absoluteExtrude == move.absoluteExtrude &&
            extrusionFactor == move.extrusionFactor &&
            speedFactor == move.speedFactor &&
            speed == move.speed &&
            gcodePosition == move.gcodePosition &&
            homingOrigin == move.homingOrigin &&
            position == move.position)
            return false;

        return true;
    }
};

Q_DECLARE_METATYPE(QKlipperGCodeMove)

#endif // QKLIPPERGCODEMOVE_H
