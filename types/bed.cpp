#include "bed.h"

Bed::Bed(Type type)
{

}

long Bed::timeRunning()
{
    return _startTime.secsTo(QDateTime::currentDateTime());
}

qreal Bed::currentTemp() const
{
    return _currentTemp;
}

void Bed::setCurrentTemp(qreal currentTemp)
{
    _currentTemp = currentTemp;
}

qreal Bed::targetTemp() const
{
    return _targetTemp;
}

void Bed::setTargetTemp(qreal targetTemp)
{
    _targetTemp = targetTemp;
}

qreal Bed::power() const
{
    return _power;
}

void Bed::setPower(qreal power)
{
    _power = power;
}

qreal Bed::watts() const
{
    return _watts;
}

void Bed::setWatts(qreal watts)
{
    _watts = watts;
}
