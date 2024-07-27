#include "extruder.h"
#include "printer.h"

Extruder::Extruder(Printer *printer, Position offset, QObject *parent) : QObject(parent)
{
    m_offset = offset;
    m_fan = new Fan(printer);
    m_printer = printer;
}

void Extruder::setOffset(Position offset)
{
    m_offset = offset;
}

void Extruder::setOffset(qreal x, qreal y, qreal z)
{
    m_offset = Position(x,y,z);
}

Position Extruder::offset()
{
    return m_offset;
}

Fan *Extruder::fan()
{
    return m_fan;
}

qreal Extruder::currentTemp()
{
    return m_currentTemp;
}

void Extruder::setTargetTemp(qreal temp)
{
    m_targetTemp = temp;

    //construct the gcode
    QString gcode("M104 T");
    gcode += QString::number(m_extruderNumber);
    gcode += QString(" S") + QString::number(temp);

    //send the gcode
    m_printer->console()->sendGcode(gcode);
}

qreal Extruder::targetTemp()
{
    return m_targetTemp;
}

qreal Extruder::power()
{
    return m_power;
}

void Extruder::setPressureAdvance(qreal advance, qreal smoothTime)
{
    m_pressureAdvance = advance;
    m_smoothTime = smoothTime;

    //set to relative movement
    QString gcode("SET_PRESSURE_ADVANCE EXTRUDER=");
    gcode += m_name + QString(" ADVANCE=") + QString::number(m_pressureAdvance);
    gcode += QString(" SMOOTH_TIME=") + QString::number(m_smoothTime);

    m_printer->console()->sendGcode(gcode);
}

qreal Extruder::pressureAdvance()
{
    return m_pressureAdvance;
}

qreal Extruder::smoothTime()
{
    return m_smoothTime;
}

bool Extruder::canExtrude()
{
    return m_canExtrude;
}

void Extruder::extrude(qreal amount, qreal speed)
{
    if(m_canExtrude)
    {
        //set to relative movement
        QString gcode("G91");
        m_printer->console()->sendGcode(gcode);

        //set active extruder
        gcode = QString("M6 T") + QString::number(m_extruderNumber);
        m_printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 E") + QString::number(amount);
        gcode += QString(" F") + QString::number(speed);
        m_printer->console()->sendGcode(gcode);
    }
}

void Extruder::retract(qreal amount, qreal speed)
{
    //extrude the inverted amount
    extrude((amount * -1), speed);
}

qreal Extruder::watts() const
{
    //qDebug() << QString("Extruder wattage ") + QString::number(m_maxWatts * m_power) + QString(" of ") + QString::number(m_maxWatts) + QString(" - ") + QString::number(m_power);
    return (m_maxWatts * m_power);
}

TemperatureStore Extruder::temperatureStore() const
{
    return m_temperatureStore;
}

Printer *Extruder::printer() const
{
    return m_printer;
}

void Extruder::setPrinter(Printer *printer)
{
    m_printer = printer;
}

void Extruder::emitUpdate()
{
    emit updated(this);
}

qreal Extruder::maxWatts() const
{
    return m_maxWatts;
}

void Extruder::setMaxWatts(qreal maxWatts)
{
    m_maxWatts = maxWatts;
}

qreal Extruder::minTemp() const
{
    return m_minTemp;
}

qreal Extruder::minExtrudeTemp() const
{
    return m_minExtrudeTemp;
}

QString Extruder::stepPin() const
{
    return m_stepPin;
}

QString Extruder::sensorType() const
{
    return m_sensorType;
}

QString Extruder::sensorPin() const
{
    return m_sensorPin;
}

QString Extruder::heaterPin() const
{
    return m_heaterPin;
}

QString Extruder::enablePin() const
{
    return m_enablePin;
}

QString Extruder::dirPin() const
{
    return m_dirPin;
}

QString Extruder::control() const
{
    return m_control;
}

qreal Extruder::maxPower() const
{
    return m_maxPower;
}

qreal Extruder::maxExtrudeOnlyVelocity() const
{
    return m_maxExtrudeOnlyVelocity;
}

qreal Extruder::maxExtrudeOnlyDistance() const
{
    return m_maxExtrudeOnlyDistance;
}

qreal Extruder::maxExtrudeOnlyAcceleration() const
{
    return m_maxExtrudeOnlyAcceleration;
}

qreal Extruder::maxExtrudeCrossSection() const
{
    return m_maxExtrudeCrossSection;
}

qreal Extruder::pidKP() const
{
    return m_pidKP;
}

qreal Extruder::pidKI() const
{
    return m_pidKI;
}

qreal Extruder::pidKD() const
{
    return m_pidKD;
}

qreal Extruder::instantCornerVelocity() const
{
    return m_instantCornerVelocity;
}

qreal Extruder::rotationDistance() const
{
    return m_rotationDistance;
}

qreal Extruder::pwmCycle() const
{
    return m_pwmCycle;
}

qreal Extruder::pullupResistor() const
{
    return m_pullupResistor;
}

qreal Extruder::inlineResistor() const
{
    return m_inlineResistor;
}

qreal Extruder::nozzleDiameter() const
{
    return m_nozzleDiameter;
}

qreal Extruder::filamentDiameter() const
{
    return m_filamentDiameter;
}

qreal Extruder::pressureAdvanceSmoothTime() const
{
    return m_pressureAdvanceSmoothTime;
}

qint32 Extruder::microsteps() const
{
    return m_microsteps;
}

qint32 Extruder::fullStepsPerRotation() const
{
    return m_fullStepsPerRotation;
}

qint32 Extruder::extruderNumber() const
{
    return m_extruderNumber;
}

QPair<qint32, qint32> Extruder::gearRatio() const
{
    return m_gearRatio;
}

qreal Extruder::maxTemp() const
{
    return m_maxTemp;
}

QString Extruder::name() const
{
    return m_name;
}

qreal Extruder::extrusionFactor() const
{
    return m_extrusionFactor;
}

void Extruder::setExtrusionFactor(qreal extrusionFactor)
{
    m_extrusionFactor = extrusionFactor;

    //convert to percentage
    extrusionFactor *= 100;

    //M221 to set extrusion factor
    QString gcode("M221 S");

    //add the value as S
    gcode += QString::number(extrusionFactor);

    //set the extruder number as T
    gcode += QString(" T") + QString::number(m_extruderNumber);

    //send the gcode
    m_printer->console()->sendGcode(gcode);
}


