#include "chamber.h"

Chamber::Chamber() {}

qreal Chamber::watts() const
{
    return _watts;
}

void Chamber::setWatts(qreal watts)
{
    _watts = watts;
}
