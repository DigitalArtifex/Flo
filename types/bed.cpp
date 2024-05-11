#include "bed.h"

Q3DPrintBed::Q3DPrintBed(Type type, QObject *parent)
    : QObject(parent)
{

}

long Q3DPrintBed::timeRunning()
{
    return _startTime.secsTo(QDateTime::currentDateTime());
}

qreal Q3DPrintBed::currentTemp() const
{
    return _currentTemp;
}

void Q3DPrintBed::setCurrentTemp(qreal currentTemp)
{
    _currentTemp = currentTemp;
}

qreal Q3DPrintBed::targetTemp() const
{
    return _targetTemp;
}

void Q3DPrintBed::setTargetTemp(qreal targetTemp)
{
    _targetTemp = targetTemp;
}

qreal Q3DPrintBed::power() const
{
    return _power;
}

void Q3DPrintBed::setPower(qreal power)
{
    _power = power;
}

qreal Q3DPrintBed::watts() const
{
    return _watts;
}

void Q3DPrintBed::setWatts(qreal watts)
{
    _watts = watts;
}

Q3DPrintBed::Mesh Q3DPrintBed::bedMesh() const
{
    return _bedMesh;
}

void Q3DPrintBed::setBedMesh(const Mesh &bedMesh)
{
    _bedMesh = bedMesh;

    emit meshUpdated(this);
}
