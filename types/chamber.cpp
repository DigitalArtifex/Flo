#include "chamber.h"

Chamber::Chamber() {}

qreal Chamber::watts() const
{
    return m_watts;
}

void Chamber::setWatts(qreal watts)
{
    m_watts = watts;
}
