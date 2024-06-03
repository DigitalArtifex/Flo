#include "extruder.h"
#include "printer.h"

Extruder::Extruder(Printer *printer, Position offset, QObject *parent) : QObject(parent)
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

qreal Extruder::currentTemp()
{
    return _currentTemp;
}

void Extruder::setTargetTemp(qreal temp)
{
    _targetTemp = temp;

    //construct the gcode
    QString gcode("M104 T");
    gcode += QString::number(_extruderNumber);
    gcode += QString(" S") + QString::number(temp);

    //send the gcode
    _printer->console()->sendGcode(gcode);
}

qreal Extruder::targetTemp()
{
    return _targetTemp;
}

qreal Extruder::power()
{
    return _power;
}

void Extruder::setPressureAdvance(qreal advance, qreal smoothTime)
{
    _pressureAdvance = advance;
    _smoothTime = smoothTime;

    //set to relative movement
    QString gcode("SET_PRESSURE_ADVANCE EXTRUDER=");
    gcode += _name + QString(" ADVANCE=") + QString::number(_pressureAdvance);
    gcode += QString(" SMOOTH_TIME=") + QString::number(_smoothTime);

    _printer->console()->sendGcode(gcode);
}

qreal Extruder::pressureAdvance()
{
    return _pressureAdvance;
}

qreal Extruder::smoothTime()
{
    return _smoothTime;
}

bool Extruder::canExtrude()
{
    return _canExtrude;
}

void Extruder::extrude(qreal amount, qreal speed)
{
    if(_canExtrude)
    {
        //set to relative movement
        QString gcode("G91");
        _printer->console()->sendGcode(gcode);

        //set active extruder
        gcode = QString("M6 T") + QString::number(_extruderNumber);
        _printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 E") + QString::number(amount);
        gcode += QString(" F") + QString::number(speed);
        _printer->console()->sendGcode(gcode);
    }
}

void Extruder::retract(qreal amount, qreal speed)
{
    //extrude the inverted amount
    extrude((amount * -1), speed);
}

qreal Extruder::watts() const
{
    return _watts;
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

void Extruder::emitUpdate()
{
    emit updated(this);
}

qreal Extruder::minTemp() const
{
    return _minTemp;
}

qreal Extruder::minExtrudeTemp() const
{
    return _minExtrudeTemp;
}

QString Extruder::stepPin() const
{
    return _stepPin;
}

QString Extruder::sensorType() const
{
    return _sensorType;
}

QString Extruder::sensorPin() const
{
    return _sensorPin;
}

QString Extruder::heaterPin() const
{
    return _heaterPin;
}

QString Extruder::enablePin() const
{
    return _enablePin;
}

QString Extruder::dirPin() const
{
    return _dirPin;
}

QString Extruder::control() const
{
    return _control;
}

qreal Extruder::maxPower() const
{
    return _maxPower;
}

qreal Extruder::maxExtrudeOnlyVelocity() const
{
    return _maxExtrudeOnlyVelocity;
}

qreal Extruder::maxExtrudeOnlyDistance() const
{
    return _maxExtrudeOnlyDistance;
}

qreal Extruder::maxExtrudeOnlyAcceleration() const
{
    return _maxExtrudeOnlyAcceleration;
}

qreal Extruder::maxExtrudeCrossSection() const
{
    return _maxExtrudeCrossSection;
}

qreal Extruder::pidKP() const
{
    return _pidKP;
}

qreal Extruder::pidKI() const
{
    return _pidKI;
}

qreal Extruder::pidKD() const
{
    return _pidKD;
}

qreal Extruder::instantCornerVelocity() const
{
    return _instantCornerVelocity;
}

qreal Extruder::rotationDistance() const
{
    return _rotationDistance;
}

qreal Extruder::pwmCycle() const
{
    return _pwmCycle;
}

qreal Extruder::pullupResistor() const
{
    return _pullupResistor;
}

qreal Extruder::inlineResistor() const
{
    return _inlineResistor;
}

qreal Extruder::nozzleDiameter() const
{
    return _nozzleDiameter;
}

qreal Extruder::filamentDiameter() const
{
    return _filamentDiameter;
}

qreal Extruder::pressureAdvanceSmoothTime() const
{
    return _pressureAdvanceSmoothTime;
}

qint32 Extruder::microsteps() const
{
    return _microsteps;
}

qint32 Extruder::fullStepsPerRotation() const
{
    return _fullStepsPerRotation;
}

qint32 Extruder::extruderNumber() const
{
    return _extruderNumber;
}

QPair<qint32, qint32> Extruder::gearRatio() const
{
    return _gearRatio;
}

qreal Extruder::maxTemp() const
{
    return _maxTemp;
}

QString Extruder::name() const
{
    return _name;
}

qreal Extruder::extrusionFactor() const
{
    return _extrusionFactor;
}

void Extruder::setExtrusionFactor(qreal extrusionFactor)
{
    _extrusionFactor = extrusionFactor;

    //convert to percentage
    extrusionFactor *= 100;

    //M221 to set extrusion factor
    QString gcode("M221 S");

    //add the value as S
    gcode += QString::number(extrusionFactor);

    //set the extruder number as T
    gcode += QString(" T") + QString::number(_extruderNumber);

    //send the gcode
    _printer->console()->sendGcode(gcode);
}


