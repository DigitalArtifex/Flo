#include "bed.h"

Bed::Bed(Type type)
{

}

void Bed::setCurrentTemp(qreal temp)
{
    _currentTemp = temp;
}

qreal Bed::currentTemp()
{
    return _currentTemp;
}

void Bed::setTargetTemp(qreal temp)
{
    _targetTemp = temp;
}

qreal Bed::targetTemp()
{
    return _targetTemp;
}

void Bed::setPower(qreal power)
{
    _power = power;
}

qreal Bed::power()
{
    return _power;
}

void Bed::setStartTime(QDateTime time)
{
    _startTime = time;
}

long Bed::timeRunning()
{
    return _startTime.secsTo(QDateTime::currentDateTime());
}
