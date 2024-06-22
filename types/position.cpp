#include "position.h"

Position::Position()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

Position::Position(qreal x, qreal y, qreal z, qreal e)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_e = e;
}

void Position::set(qreal x, qreal y, qreal z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void Position::setX(qreal x)
{
    m_x = x;
}

qreal Position::x()
{
    return m_x;
}

void Position::setY(qreal y)
{
    m_y = y;
}

qreal Position::y()
{
    return m_y;
}

void Position::setZ(qreal z)
{
    m_z = z;
}

qreal Position::z()
{
    return m_z;
}

void Position::setE(qreal e)
{
    m_e = e;
}

qreal Position::e()
{
    return m_e;
}
