#include "fan.h"

Fan::Fan(Printer *printer)
{
    m_printer = printer;
}

Fan::~Fan()
{

}

qreal Fan::speed() const
{
    return m_speed;
}

void Fan::setSpeed(qreal speed)
{
    m_speed = speed;
}

qreal Fan::rpm() const
{
    return m_rpm;
}

void Fan::setRpm(qreal rpm)
{
    m_rpm = rpm;
}

Printer *Fan::printer() const
{
    return m_printer;
}

void Fan::setPrinter(Printer *printer)
{
    m_printer = printer;
}
