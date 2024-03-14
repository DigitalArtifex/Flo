#ifndef TOOLHEAD_H
#define TOOLHEAD_H

#include <QObject>
#include <QMap>

#include "extruder.h"
#include "position.h"

class Toolhead
{
    Q_GADGET
public:
    Toolhead();

    void addExtruder(Extruder *extruder);

    Extruder *extruder(int index);
    Fan *fan();
    Position position();
    Position destination();

    void setPosition(Position position);
    void setPosition(qreal x, qreal y, qreal z);

    void setDestination(Position position);
    void setDestination(qreal x, qreal y, qreal z);

    void setMaxPosition(Position position);
    void setMaxPosition(qreal x, qreal y, qreal z);
    Position maxPosition();

    void setMinPosition(Position position);
    void setMinPosition(qreal x, qreal y, qreal z);
    Position minPosition();

    void setZHomed(bool homed);
    bool isZHomed();

    void setYHomed(bool homed);
    bool isYHomed();

    void setXHomed(bool homed);
    bool isXHomed();

    bool isHomed();

    int extruderCount();

    QString homedAxes();

private:
    Position _position;
    Position _destination;
    Position _maxPosition;
    Position _minPosition;
    Fan *_fan;
    QMap<int, Extruder*> _extruders;

    bool _zHomed = false;
    bool _yHomed = false;
    bool _xHomed = false;
};

#endif // TOOLHEAD_H
