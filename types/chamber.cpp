#include "chamber.h"

Chamber::Chamber()
{

}

qreal Chamber::watts() const
{
    return m_watts;
}

qreal Chamber::maxWatts() const
{
    return m_maxWatts;
}

void Chamber::setMaxWatts(qreal maxWatts)
{
    m_maxWatts = maxWatts;
}

qreal Chamber::power() const
{
    return m_power;
}

void Chamber::setPower(qreal power)
{
    m_power = power;
}
