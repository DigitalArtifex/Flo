#include "toolhead.h"
#include "printer.h"

Toolhead::Toolhead(Printer *printer, QObject *parent) : QObject(parent)
{
    _fan = new Fan(printer);
    _printer = printer;
}

void Toolhead::addExtruder(Extruder *extruder)
{
    _extruders[_extruders.count()] = extruder;
}

Extruder *Toolhead::extruder(int index)
{
    int currentIndex = _extruders.count() - 1;

    if(index > currentIndex)
        addExtruder(new Extruder(_printer));

    return _extruders[index];
}

Fan *Toolhead::fan()
{
    return _fan;
}

Position Toolhead::position()
{
    return _position;
}

Position Toolhead::destination()
{
    return _destination;
}

void Toolhead::setPosition(Position position)
{
    _position = position;
}

void Toolhead::setPosition(qreal x, qreal y, qreal z)
{
    _position = Position(x,y,z);
}

Position Toolhead::maxPosition()
{
    return _maxPosition;
}

Position Toolhead::minPosition()
{
    return _minPosition;
}

void Toolhead::homeX()
{
    _isHoming = true;
    _isXHoming = true;

    _xHomed = false;

    //G28 to home
    QString gcode("G28 X");

    //send the gcode
    _printer->console()->sendGcode(gcode);

    emit homing();
}

void Toolhead::homeY()
{
    _isHoming = true;
    _isYHoming = true;

    _yHomed = false;

    //G28 to home
    QString gcode("G28 Y");

    //send the gcode
    _printer->console()->sendGcode(gcode);

    emit homing();
}

void Toolhead::homeZ()
{
    _isHoming = true;
    _isZHoming = true;

    _zHomed = false;

    //G28 to home
    QString gcode("G28 Z");

    //send the gcode
    _printer->console()->sendGcode(gcode);

    emit homing();
}

bool Toolhead::isZHomed()
{
    return _zHomed;
}

bool Toolhead::isYHomed()
{
    return _yHomed;
}

bool Toolhead::isXHomed()
{
    return _xHomed;
}

bool Toolhead::isHomed()
{
    return (isXHomed() && isYHomed() && isZHomed());
}

void Toolhead::moveX(qreal amount, qreal speed)
{
    if(_xHomed)
    {
        //set to relative movement
        QString gcode("G91");
        _printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 X") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        _printer->console()->sendGcode(gcode);
    }
}

void Toolhead::moveY(qreal amount, qreal speed)
{
    if(_yHomed)
    {
        //set to relative movement
        QString gcode("G91");
        _printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 Y") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        _printer->console()->sendGcode(gcode);
    }
}

void Toolhead::moveZ(qreal amount, qreal speed)
{
    if(_zHomed)
    {
        //set to relative movement
        QString gcode("G91");
        _printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 Z") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        _printer->console()->sendGcode(gcode);
    }
}

void Toolhead::homeAll()
{
    _isHoming = true;

    _isXHoming = true;
    _isYHoming = true;
    _isZHoming = true;

    _xHomed = false;
    _yHomed = false;
    _zHomed = false;

    //G28 to home
    QString gcode("G28");

    //send the gcode
    _printer->console()->sendGcode(gcode);

    emit homing();
}

int Toolhead::extruderCount()
{
    return _extruders.count();
}

Extruder *Toolhead::currentExtruder()
{
    Extruder *extruder = nullptr;

    if(!_currentExtruderName.isEmpty())
    {
        for(int i = 0; i < _extruders.count(); i++)
        {
            if(_extruders[i]->_name == _currentExtruderName)
            {
                extruder = _extruders[i];
                break;
            }
        }
    }

    return extruder;
}

Extruder *Toolhead::extruderByName(QString name)
{
    Extruder *extruder = nullptr;

    for(int i = 0; i < _extruders.count(); i++)
    {
        if(_extruders[i]->_name == name)
        {
            extruder = _extruders[i];
            break;
        }
    }

    return extruder;
}

QString Toolhead::homedAxes()
{
    QString homed;

    if(_xHomed)
        homed += "x";
    if(_yHomed)
        homed += "y";
    if(_zHomed)
        homed += "z";

    return homed;
}

qint32 Toolhead::maxAcceleration() const
{
    return _maxAcceleration;
}

void Toolhead::setMaxAcceleration(qint32 maxAcceleration)
{
    _maxAcceleration = maxAcceleration;
}

qint32 Toolhead::maxVelocity() const
{
    return _maxVelocity;
}

void Toolhead::setMaxVelocity(qint32 maxVelocity)
{
    _maxVelocity = maxVelocity;
}

qint32 Toolhead::maxAccelerationToDeceleration() const
{
    return _maxAccelerationToDeceleration;
}

void Toolhead::setMaxAccelerationToDeceleration(qint32 maxAccelerationToDeceleration)
{
    _maxAccelerationToDeceleration = maxAccelerationToDeceleration;
}

qint32 Toolhead::stalls() const
{
    return _stalls;
}

Printer *Toolhead::printer() const
{
    return _printer;
}

void Toolhead::setPrinter(Printer *printer)
{
    _printer = printer;
}

void Toolhead::setExtruderMaxWatts(qint32 extruder, qreal watts)
{
    _extruders[extruder]->_watts = watts;
}

void Toolhead::emitUpdate()
{
    if(_isHoming)
    {
        bool homingComplete = false;

        if(_isXHoming)
        {
            homingComplete = _xHomed;
            _isXHoming = !_xHomed;
        }

        if(_isYHoming)
        {
            homingComplete = _yHomed;
            _isYHoming = !_yHomed;
        }

        if(_isZHoming)
        {
            homingComplete = _zHomed;
            _isZHoming = !_zHomed;
        }

        if(homingComplete)
        {
            qDebug() << QString("homed");

            _isXHoming = false;
            _isYHoming = false;
            _isZHoming = false;

            _isHoming = false;
            emit homed();
        }
    }

    emit updated();
}
