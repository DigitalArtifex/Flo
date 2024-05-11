#include "extruder.h"

Extruder::Extruder(Printer *printer, Position offset)
{
    _offset = offset;
    _fan = new Fan(printer);
    _printer = printer;
}

void Extruder::setOffset(Position offset)
{
    _offset = offset;
}

void Extruder::setOffset(qreal x, qreal y, qreal z)
{
    _offset = Position(x,y,z);
}

Position Extruder::offset()
{
    return _offset;
}

Fan *Extruder::fan()
{
    return _fan;
}

void Extruder::setCurrentTemp(qreal temp)
{
    _currentTemp = temp;
}

qreal Extruder::currentTemp()
{
    return _currentTemp;
}

void Extruder::setTargetTemp(qreal temp)
{
    _targetTemp = temp;
}

qreal Extruder::targetTemp()
{
    return _targetTemp;
}

void Extruder::setPower(qreal power)
{
    _power = power;
}

qreal Extruder::power()
{
    return _power;
}

void Extruder::setPressureAdvance(qreal advance)
{
    _pressureAdvance = advance;
}

qreal Extruder::pressureAdvance()
{
    return _pressureAdvance;
}

void Extruder::setSmoothTime(qreal time)
{
    _smoothTime = time;
}

qreal Extruder::smoothTime()
{
    return _smoothTime;
}

void Extruder::setCanExtrude(bool canExtrude)
{
    _canExtrude = canExtrude;
}

bool Extruder::canExtrude()
{
    return _canExtrude;
}

qreal Extruder::watts() const
{
    return _watts;
}

void Extruder::setWatts(qreal watts)
{
    _watts = watts;
}

TemperatureStore Extruder::temperatureStore() const
{
    return _temperatureStore;
}

Printer *Extruder::printer() const
{
    return _printer;
}

void Extruder::setPrinter(Printer *printer)
{
    _printer = printer;
}
