#include "toolhead.h"

Toolhead::Toolhead()
{
    _fan = new Fan();
}

void Toolhead::addExtruder(Extruder *extruder)
{
    _extruders[_extruders.count()] = extruder;
}

Extruder *Toolhead::extruder(int index)
{
    int currentIndex = _extruders.count() - 1;

    if(index > currentIndex)
        addExtruder(new Extruder());

    return _extruders[index];
}

Fan *Toolhead::fan()
{
    return _fan;
}

Position Toolhead::position()
{
    return _position;
}

Position Toolhead::destination()
{
    return _destination;
}

void Toolhead::setPosition(Position position)
{
    _position = position;
}

void Toolhead::setPosition(qreal x, qreal y, qreal z)
{
    _position = Position(x,y,z);
}

void Toolhead::setDestination(Position position)
{
    _destination = position;
}

void Toolhead::setDestination(qreal x, qreal y, qreal z)
{
    _destination = Position(x,y,z);
}

void Toolhead::setMaxPosition(Position position)
{
    _maxPosition = position;
}

void Toolhead::setMaxPosition(qreal x, qreal y, qreal z)
{
    _maxPosition = Position(x,y,z);
}

Position Toolhead::maxPosition()
{
    return _maxPosition;
}

void Toolhead::setMinPosition(Position position)
{
    _minPosition = position;
}

void Toolhead::setMinPosition(qreal x, qreal y, qreal z)
{
    _minPosition = Position(x,y,z);
}

Position Toolhead::minPosition()
{
    return _minPosition;
}

void Toolhead::setZHomed(bool homed)
{
    _zHomed = homed;
}

bool Toolhead::isZHomed()
{
    return _zHomed;
}

void Toolhead::setYHomed(bool homed)
{
    _yHomed = homed;
}

bool Toolhead::isYHomed()
{
    return _yHomed;
}

void Toolhead::setXHomed(bool homed)
{
    _xHomed = homed;
}

bool Toolhead::isXHomed()
{
    return _xHomed;
}

bool Toolhead::isHomed()
{
    return (isXHomed() && isYHomed() && isZHomed());
}

int Toolhead::extruderCount()
{
    return _extruders.count();
}

QString Toolhead::homedAxes()
{
    QString homed;

    if(isXHomed())
        homed += "x";
    if(isYHomed())
        homed += "y";
    if(isZHomed())
        homed += "z";

    return homed;
}
