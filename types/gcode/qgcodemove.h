#ifndef QGCODEMOVE_H
#define QGCODEMOVE_H

#include <QObject>

#include "../position.h"

class QGCodeMove
{
    Q_GADGET
public:
    QGCodeMove() { }

    bool absoluteCoordinates = false;
    bool absoluteExtrude = false;

    qreal extrusionFactor = 0;
    qreal speedFactor = 0;
    qreal speed = 0;

    QGCodePosition gcodePosition;
    QGCodePosition homingOrigin;
    QGCodePosition position;
};

#endif // QGCODEMOVE_H
