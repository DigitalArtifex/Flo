#include "fan.h"

Fan::Fan()
{

}

void Fan::setSpeed(qreal speed)
{
    _speed = speed;
}

qreal Fan::speed()
{
    return _speed;
}

void Fan::setRpm(qreal rpm)
{
    _rpm = rpm;
}

qreal Fan::rpm()
{
    return _rpm;
}
