#include "position.h"

Position::Position()
{
    _x = 0;
    _y = 0;
    _z = 0;
}

Position::Position(qreal x, qreal y, qreal z)
{
    _x = x;
    _y = y;
    _z = z;
}

void Position::set(qreal x, qreal y, qreal z)
{
    _x = x;
    _y = y;
    _z = z;
}

void Position::setX(qreal x)
{
    _x = x;
}

qreal Position::x()
{
    return _x;
}

void Position::setY(qreal y)
{
    _y = y;
}

qreal Position::y()
{
    return _y;
}

void Position::setZ(qreal z)
{
    _z = z;
}

qreal Position::z()
{
    return _z;
}
