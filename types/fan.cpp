#include "fan.h"

Fan::Fan(Printer *printer)
{
    _printer = printer;
}

Fan::~Fan()
{

}

qreal Fan::speed() const
{
    return _speed;
}

void Fan::setSpeed(qreal speed)
{
    _speed = speed;
}

qreal Fan::rpm() const
{
    return _rpm;
}

void Fan::setRpm(qreal rpm)
{
    _rpm = rpm;
}

Printer *Fan::printer() const
{
    return _printer;
}

void Fan::setPrinter(Printer *printer)
{
    _printer = printer;
}
