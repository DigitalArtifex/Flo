#include "qklipperfan.h"

#include "../QKlipperConsole/qklipperconsole.h"

QKlipperFan::QKlipperFan(QObject *parent)
    : QObject{parent}
{

}

QString QKlipperFan::name() const
{
    return m_name;
}

void QKlipperFan::resetName()
{
    setNameData({}); // TODO: Adapt to use your actual default value
}

void QKlipperFan::setSpeedData(qreal speed)
{
    if (qFuzzyCompare(m_speed, speed))
        return;

    m_speed = speed;
    emit speedChanged();
}

qreal QKlipperFan::speed() const
{
    return m_speed;
}

void QKlipperFan::setSpeed(qreal speed)
{
    //set the fan speed
    QString gcode = QString("SET_FAN_SPEED FAN=%1 SPEED=%2").arg(m_name, QString::number(speed));
    m_console->printerGcodeScript(gcode);
}

void QKlipperFan::resetSpeed()
{
    setSpeed({}); // TODO: Adapt to use your actual default value
}

void QKlipperFan::setRpmData(qreal rpm)
{
    if (qFuzzyCompare(m_rpm, rpm))
        return;

    m_rpm = rpm;
    emit rpmChanged();
}

qreal QKlipperFan::rpm() const
{
    return m_rpm;
}

void QKlipperFan::resetRpm()
{
    setRpmData({}); // TODO: Adapt to use your actual default value
}

bool QKlipperFan::isControllable() const
{
    return m_isControllable;
}

void QKlipperFan::setIsControllable(bool isControllable)
{
    if (m_isControllable == isControllable)
        return;

    m_isControllable = isControllable;
    emit isControllableChanged();
}

void QKlipperFan::resetIsControllable()
{
    setIsControllable({}); // TODO: Adapt to use your actual default value
}

QKlipperConsole *QKlipperFan::console() const
{
    return m_console;
}

void QKlipperFan::setConsole(QKlipperConsole *console)
{
    m_console = console;
}

void QKlipperFan::setNameData(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}
