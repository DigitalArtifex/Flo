#include "toolhead.h"
#include "printer.h"

Toolhead::Toolhead(Printer *printer, QObject *parent) : QObject(parent)
{
    m_fan = new Fan(printer);
    m_printer = printer;
}

void Toolhead::addExtruder(Extruder *extruder)
{
    m_extruders[m_extruders.count()] = extruder;
}

Extruder *Toolhead::extruder(int index)
{
    int currentIndex = m_extruders.count() - 1;

    if(index > currentIndex)
        addExtruder(new Extruder(m_printer));

    return m_extruders[index];
}

Fan *Toolhead::fan()
{
    return m_fan;
}

Position Toolhead::position()
{
    return m_position;
}

Position Toolhead::destination()
{
    return m_destination;
}

void Toolhead::setPosition(Position position)
{
    m_position = position;
}

void Toolhead::setPosition(qreal x, qreal y, qreal z)
{
    m_position = Position(x,y,z);
}

Position Toolhead::maxPosition()
{
    return m_maxPosition;
}

Position Toolhead::minPosition()
{
    return m_minPosition;
}

void Toolhead::homeX()
{
    m_isHoming = true;
    m_isXHoming = true;

    m_xHomed = false;

    //G28 to home
    QString gcode("G28 X");

    //send the gcode
    m_printer->console()->sendGcode(gcode);

    emit homing();
}

void Toolhead::homeY()
{
    m_isHoming = true;
    m_isYHoming = true;

    m_yHomed = false;

    //G28 to home
    QString gcode("G28 Y");

    //send the gcode
    m_printer->console()->sendGcode(gcode);

    emit homing();
}

void Toolhead::homeZ()
{
    m_isHoming = true;
    m_isZHoming = true;

    m_zHomed = false;

    //G28 to home
    QString gcode("G28 Z");

    //send the gcode
    m_printer->console()->sendGcode(gcode);

    emit homing();
}

bool Toolhead::isZHomed()
{
    return m_zHomed;
}

bool Toolhead::isYHomed()
{
    return m_yHomed;
}

bool Toolhead::isXHomed()
{
    return m_xHomed;
}

bool Toolhead::isHomed()
{
    return (isXHomed() && isYHomed() && isZHomed());
}

void Toolhead::moveX(qreal amount, qreal speed)
{
    if(m_xHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 X") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_printer->console()->sendGcode(gcode);
    }
}

void Toolhead::moveY(qreal amount, qreal speed)
{
    if(m_yHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 Y") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_printer->console()->sendGcode(gcode);
    }
}

void Toolhead::moveZ(qreal amount, qreal speed)
{
    if(m_zHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_printer->console()->sendGcode(gcode);

        //extrude the requested amount
        gcode = QString("G1 Z") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_printer->console()->sendGcode(gcode);
    }
}

void Toolhead::homeAll()
{
    m_isHoming = true;

    m_isXHoming = true;
    m_isYHoming = true;
    m_isZHoming = true;

    m_xHomed = false;
    m_yHomed = false;
    m_zHomed = false;

    //G28 to home
    QString gcode("G28");

    //send the gcode
    m_printer->console()->sendGcode(gcode);

    emit homing();
}

int Toolhead::extruderCount()
{
    return m_extruders.count();
}

Extruder *Toolhead::currentExtruder()
{
    Extruder *extruder = nullptr;

    if(!m_currentExtruderName.isEmpty())
    {
        for(int i = 0; i < m_extruders.count(); i++)
        {
            if(m_extruders[i]->m_name == m_currentExtruderName)
            {
                extruder = m_extruders[i];
                break;
            }
        }
    }

    if(!extruder)
    {
        if(!m_extruders.isEmpty())
            extruder = m_extruders[0];
    }

    return extruder;
}

Extruder *Toolhead::extruderByName(QString name)
{
    Extruder *extruder = nullptr;

    for(int i = 0; i < m_extruders.count(); i++)
    {
        if(m_extruders[i]->m_name == name)
        {
            extruder = m_extruders[i];
            break;
        }
    }

    return extruder;
}

QString Toolhead::homedAxes()
{
    QString homed;

    if(m_xHomed)
        homed += "x";
    if(m_yHomed)
        homed += "y";
    if(m_zHomed)
        homed += "z";

    return homed;
}

qint32 Toolhead::maxAcceleration() const
{
    return m_maxAcceleration;
}

void Toolhead::setMaxAcceleration(qint32 maxAcceleration)
{
    m_maxAcceleration = maxAcceleration;
}

qint32 Toolhead::maxVelocity() const
{
    return m_maxVelocity;
}

void Toolhead::setMaxVelocity(qint32 maxVelocity)
{
    m_maxVelocity = maxVelocity;
}

qint32 Toolhead::maxAccelerationToDeceleration() const
{
    return m_maxAccelerationToDeceleration;
}

void Toolhead::setMaxAccelerationToDeceleration(qint32 maxAccelerationToDeceleration)
{
    m_maxAccelerationToDeceleration = maxAccelerationToDeceleration;
}

qint32 Toolhead::stalls() const
{
    return m_stalls;
}

Printer *Toolhead::printer() const
{
    return m_printer;
}

void Toolhead::setPrinter(Printer *printer)
{
    m_printer = printer;
}

void Toolhead::setExtruderMaxWatts(qint32 extruder, qreal watts)
{
    m_extruders[extruder]->m_maxWatts = watts;
}

qreal Toolhead::watts() const
{
    qreal watts = 0;

    for(int i = 0; i < m_extruders.count(); i++)
        watts += m_extruders[i]->watts();

    return watts;
}

qreal Toolhead::maxWatts() const
{
    qreal watts = 0;

    for(int i = 0; i < m_extruders.count(); i++)
        watts += m_extruders[i]->maxWatts();

    return watts;
}

void Toolhead::update()
{
    if(m_isHoming)
    {
        bool homingComplete = false;

        if(m_isXHoming)
        {
            homingComplete = m_xHomed;
            m_isXHoming = !m_xHomed;
        }

        if(m_isYHoming)
        {
            homingComplete = m_yHomed;
            m_isYHoming = !m_yHomed;
        }

        if(m_isZHoming)
        {
            homingComplete = m_zHomed;
            m_isZHoming = !m_zHomed;
        }

        if(homingComplete)
        {
            qDebug() << QString("homed");

            m_isXHoming = false;
            m_isYHoming = false;
            m_isZHoming = false;

            m_isHoming = false;
            emit homed();
        }
    }

    emit updated();
}
