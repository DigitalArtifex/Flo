#include "endstopstatus.h"

EndstopStatus::EndstopStatus(QObject *parent)
{}

bool EndstopStatus::x() const
{
    return _x;
}

void EndstopStatus::setX(bool x)
{
    _x = x;
}

bool EndstopStatus::y() const
{
    return _y;
}

void EndstopStatus::setY(bool y)
{
    _y = y;
}

bool EndstopStatus::z() const
{
    return _z;
}

void EndstopStatus::setZ(bool z)
{
    _z = z;
}
