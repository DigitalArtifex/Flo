#include "qklippertoolhead.h"
#include "qklipperprinter.h"

#include "../QKlipperConsole/qklipperconsole.h"

QKlipperToolHead::QKlipperToolHead(QObject *parent)
    : QObject{parent}
{
    m_partsFan = new QKlipperFan(this);

    QKlipperExtruder *extruder = new QKlipperExtruder(this);
    extruder->setName("extruder");
    m_extruderMap["extruder"] = extruder;
}

QKlipperToolHead::~QKlipperToolHead()
{
    if(m_partsFan)
        m_partsFan->deleteLater();

    foreach(QKlipperExtruder *extruder, m_extruderMap)
        extruder->deleteLater();
}

QKlipperFan *QKlipperToolHead::partsFan() const
{
    return m_partsFan;
}

void QKlipperToolHead::setPartsFan(QKlipperFan *partsFan)
{
    if (m_partsFan == partsFan)
        return;

    m_partsFan = partsFan;
    emit partsFanChanged();
}

QMap<QString, QKlipperExtruder *> QKlipperToolHead::extruderMap() const
{
    return m_extruderMap;
}

QKlipperExtruder *QKlipperToolHead::extruder(const QString &name)
{
    if(m_extruderMap.contains(name))
        return m_extruderMap[name];

    return nullptr;
}

QKlipperExtruder *QKlipperToolHead::currentExtruder()
{
    if(m_extruderMap.contains(m_currentExtruderName))
        return m_extruderMap[m_currentExtruderName];

    return nullptr;
}

void QKlipperToolHead::setExtruderMap(const QMap<QString, QKlipperExtruder *> &extruderMap)
{
    if (m_extruderMap == extruderMap)
        return;
    m_extruderMap = extruderMap;
    emit extruderMapChanged();
}

void QKlipperToolHead::setExtruder(QString name, QKlipperExtruder *extruder)
{
    if(m_extruderMap.contains(name))
    {
        if(extruder == m_extruderMap[name])
            return;

        QKlipperExtruder *current = m_extruderMap[name];
        m_extruderMap.remove(name);

        current->deleteLater();
    }

    m_extruderMap[name] = extruder;
    emit extruderMapChanged();
}

qreal QKlipperToolHead::watts()
{
    qreal totalWatts = 0;
    QMapIterator<QString,QKlipperExtruder*> iterator(m_extruderMap);

    while(iterator.hasNext())
    {
        iterator.next();
        totalWatts += iterator.value()->watts();
    }

    return totalWatts;
}

QKlipperPosition QKlipperToolHead::minPosition() const
{
    return m_minPosition;
}

void QKlipperToolHead::setMinPosition(const QKlipperPosition &minPosition)
{
    if (m_minPosition == minPosition)
        return;
    m_minPosition = minPosition;
    emit minPositionChanged();
}

void QKlipperToolHead::setPositionData(const QKlipperPosition &position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged();
}

void QKlipperToolHead::setPosition(const QKlipperPosition &position, qreal speed)
{
    if(m_xHomed && m_zHomed && m_yHomed)
    {
        //set to absolute movement
        QString gcode("G90");
        m_console->printerGcodeScript(gcode);

        //set the requested position
        gcode = QString("G1 X%1 Y%2 Z%3").arg
        (
            QString::number(position.x()),
            QString::number(position.y()),
            QString::number(position.z())
        );

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::setPosition(qreal x, qreal y, qreal z, qreal speed)
{
    if(m_xHomed && m_zHomed && m_yHomed)
    {
        //set to absolute movement
        QString gcode("G90");
        m_console->printerGcodeScript(gcode);

        //set the requested position
        gcode = QString("G1 X%1 Y%2 Z%3").arg
        (
            QString::number(x),
            QString::number(y),
            QString::number(z)
        );

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::setPositionX(qreal position, qreal speed)
{
    if(m_xHomed)
    {
        //set to absolute movement
        QString gcode("G90");
        m_console->printerGcodeScript(gcode);

        //set the requested position
        gcode = QString("G1 X%1").arg(QString::number(position));

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::setPositionY(qreal position, qreal speed)
{
    if(m_yHomed)
    {
        //set to absolute movement
        QString gcode("G90");
        m_console->printerGcodeScript(gcode);

        //set the requested position
        gcode = QString("G1 Y%1").arg(QString::number(position));

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::setPositionZ(qreal position, qreal speed)
{
    if(m_zHomed)
    {
        //set to absolute movement
        QString gcode("G90");
        m_console->printerGcodeScript(gcode);

        //set the requested position
        gcode = QString("G1 Z%1").arg(QString::number(position));

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::home()
{
    emit homing();
    setIsHoming(true);

    //send homing command
    QString gcode("G28");
    m_console->printerGcodeScript(gcode);

    setIsHoming(false);
    emit homingFinished();
}

void QKlipperToolHead::move(qreal x, qreal y, qreal z, qreal speed)
{
    if(m_xHomed && m_zHomed && m_yHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_console->printerGcodeScript(gcode);

        //set the requested position
        gcode = QString("G1 X%1 Y%2 Z%3").arg
        (
            QString::number(x),
            QString::number(y),
            QString::number(z)
        );

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::move(const QKlipperPosition &position, qreal speed)
{
    if(m_xHomed && m_zHomed && m_yHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_console->printerGcodeScript(gcode);

        //set the requested position
        gcode = QString("G1 X%1 Y%2 Z%3").arg
        (
            QString::number(position.x()),
            QString::number(position.y()),
            QString::number(position.z())
        );

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::moveX(qreal amount, qreal speed)
{
    if(m_xHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_console->printerGcodeScript(gcode);

        //extrude the requested amount
        gcode = QString("G1 X") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::moveY(qreal amount, qreal speed)
{
    if(m_yHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_console->printerGcodeScript(gcode);

        //extrude the requested amount
        gcode = QString("G1 Y") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

void QKlipperToolHead::moveZ(qreal amount, qreal speed)
{
    if(m_zHomed)
    {
        //set to relative movement
        QString gcode("G91");
        m_console->printerGcodeScript(gcode);

        //extrude the requested amount
        gcode = QString("G1 Z") + QString::number(amount);

        //only send speed if specified
        if(speed > 0)
            gcode += QString(" F") + QString::number(speed);

        m_console->printerGcodeScript(gcode);
    }
}

QKlipperConsole *QKlipperToolHead::console() const
{
    return m_console;
}

QString QKlipperToolHead::homedAxes() const
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

void QKlipperToolHead::setConsole(QKlipperConsole *console)
{
    if (m_console == console)
        return;

    QMapIterator<QString, QKlipperExtruder*> iterator(m_extruderMap);

    while(iterator.hasNext())
    {
        iterator.next();
        iterator.value()->setConsole(console);
    }

    m_console = console;
}

bool QKlipperToolHead::isHomed() const
{
    return m_isHomed;
}

void QKlipperToolHead::setIsHomed(bool isHomed)
{
    if (m_isHomed == isHomed)
        return;

    m_isHomed = isHomed;
    emit isHomedChanged();
}

QKlipperPosition QKlipperToolHead::maxPosition() const
{
    return m_maxPosition;
}

void QKlipperToolHead::setMaxPosition(const QKlipperPosition &maxPosition)
{
    if (m_maxPosition == maxPosition)
        return;

    m_maxPosition = maxPosition;
    emit maxPositionChanged();
}

QKlipperPosition QKlipperToolHead::destination() const
{
    return m_destination;
}

void QKlipperToolHead::setDestination(const QKlipperPosition &destination)
{
    if (m_destination == destination)
        return;

    m_destination = destination;
    emit destinationChanged();
}

QKlipperPosition QKlipperToolHead::position() const
{
    return m_position;
}

qreal QKlipperToolHead::squareCornerVelocity() const
{
    return m_squareCornerVelocity;
}

void QKlipperToolHead::setSquareCornerVelocity(qreal squareCornerVelocity)
{
    if (qFuzzyCompare(m_squareCornerVelocity, squareCornerVelocity))
        return;
    m_squareCornerVelocity = squareCornerVelocity;
    emit squareCornerVelocityChanged();
}

qint32 QKlipperToolHead::checks() const
{
    return m_checks;
}

void QKlipperToolHead::setChecks(qint32 checks)
{
    if (m_checks == checks)
        return;
    m_checks = checks;
    emit checksChanged();
}

qint32 QKlipperToolHead::stalls() const
{
    return m_stalls;
}

void QKlipperToolHead::setStalls(qint32 stalls)
{
    if (m_stalls == stalls)
        return;

    m_stalls = stalls;
    emit stallsChanged();
}

qint32 QKlipperToolHead::maxAccelerationToDeceleration() const
{
    return m_maxAccelerationToDeceleration;
}

void QKlipperToolHead::setMaxAccelerationToDeceleration(qint32 maxAccelerationToDeceleration)
{
    if (m_maxAccelerationToDeceleration == maxAccelerationToDeceleration)
        return;

    m_maxAccelerationToDeceleration = maxAccelerationToDeceleration;
    emit maxAccelerationToDecelerationChanged();
}

qint32 QKlipperToolHead::maxVelocity() const
{
    return m_maxVelocity;
}

void QKlipperToolHead::setMaxVelocity(qint32 maxVelocity)
{
    if (m_maxVelocity == maxVelocity)
        return;

    m_maxVelocity = maxVelocity;
    emit maxVelocityChanged();
}

qint32 QKlipperToolHead::maxAcceleration() const
{
    return m_maxAcceleration;
}

void QKlipperToolHead::setMaxAcceleration(qint32 maxAcceleration)
{
    if (m_maxAcceleration == maxAcceleration)
        return;

    m_maxAcceleration = maxAcceleration;
    emit maxAccelerationChanged();
}

bool QKlipperToolHead::isHoming() const
{
    return m_isHoming;
}

void QKlipperToolHead::setIsHoming(bool isHoming)
{
    if (m_isHoming == isHoming)
        return;

    m_isHoming = isHoming;
    emit isHomingChanged();
}

bool QKlipperToolHead::xHomed() const
{
    return m_xHomed;
}

void QKlipperToolHead::setXHomed(bool xHomed)
{
    if (m_xHomed == xHomed)
        return;

    m_xHomed = xHomed;

    emit xHomedChanged();

    if(m_xHomed && m_yHomed && m_zHomed)
        setIsHomed(true);
    else
        setIsHomed(false);
}

bool QKlipperToolHead::yHomed() const
{
    return m_yHomed;
}

void QKlipperToolHead::setYHomed(bool yHomed)
{
    if (m_yHomed == yHomed)
        return;

    m_yHomed = yHomed;

    emit yHomedChanged();

    if(m_xHomed && m_yHomed && m_zHomed)
        setIsHomed(true);
    else
        setIsHomed(false);
}

bool QKlipperToolHead::zHomed() const
{
    return m_zHomed;
}

void QKlipperToolHead::setZHomed(bool zHomed)
{
    if (m_zHomed == zHomed)
        return;

    m_zHomed = zHomed;

    emit zHomedChanged();

    if(m_xHomed && m_yHomed && m_zHomed)
        setIsHomed(true);
    else
        setIsHomed(false);
}

QString QKlipperToolHead::currentExtruderName() const
{
    return m_currentExtruderName;
}

void QKlipperToolHead::setCurrentExtruderName(const QString &currentExtruderName)
{
    if (m_currentExtruderName == currentExtruderName)
        return;

    m_currentExtruderName = currentExtruderName;
    emit currentExtruderNameChanged();
}
