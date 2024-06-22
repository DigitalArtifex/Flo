#include "endstopstatus.h"

EndstopStatus::EndstopStatus(QObject *parent)
{

}

bool EndstopStatus::x() const
{
    return m_x;
}

void EndstopStatus::setX(bool x)
{
    m_x = x;
}

bool EndstopStatus::y() const
{
    return m_y;
}

void EndstopStatus::setY(bool y)
{
    m_y = y;
}

bool EndstopStatus::z() const
{
    return m_z;
}

void EndstopStatus::setZ(bool z)
{
    m_z = z;
}
