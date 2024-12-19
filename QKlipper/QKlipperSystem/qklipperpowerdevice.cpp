#include "qklipperpowerdevice.h"
#include "qklippersystem.h"
#include "../QKlipperInstance/qklipperinstance.h"

QKlipperPowerDevice::QKlipperPowerDevice(QObject *parent)
    : QObject{parent}
{}

QKlipperPowerDevice::QKlipperPowerDevice(QString name, Type type, bool isOn, bool lockedWhilePrinting)
{
    m_name = name;
    m_type = type;
    m_isOn = isOn;
    m_lockedWhilePrinting = lockedWhilePrinting;

    if((int)type < m_typeNames.count() && (int)type > 0)
        m_typeString = m_typeNames[type];
}

QString QKlipperPowerDevice::name() const
{
    return m_name;
}

void QKlipperPowerDevice::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

bool QKlipperPowerDevice::isOn() const
{
    return m_isOn;
}

void QKlipperPowerDevice::setIsOn(bool isOn)
{
    if (m_isOn == isOn)
        return;

    m_isOn = isOn;
    emit isOnChanged();
}

bool QKlipperPowerDevice::lockedWhilePrinting() const
{
    return m_lockedWhilePrinting;
}

void QKlipperPowerDevice::turnOn()
{
    QKlipperSystem *system = qobject_cast<QKlipperSystem*>(parent());

    if(system)
    {
        QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(system->parent());

        if(instance)
        {
            if(instance->console()->isConnected())
            {
                instance->console()->machinePowerDeviceSetState(m_name, "on");
            }
        }
    }
}

void QKlipperPowerDevice::turnOff()
{
    QKlipperSystem *system = qobject_cast<QKlipperSystem*>(parent());

    if(system)
    {
        QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(system->parent());

        if(instance)
        {
            if(instance->console()->isConnected())
            {
                instance->console()->machinePowerDeviceSetState(m_name, "off");
            }
        }
    }
}

void QKlipperPowerDevice::setLockedWhilePrinting(bool lockedWhilePrinting)
{
    if (m_lockedWhilePrinting == lockedWhilePrinting)
        return;
    m_lockedWhilePrinting = lockedWhilePrinting;
    emit lockedWhilePrintingChanged();
}

QString QKlipperPowerDevice::typeString() const
{
    return m_typeString;
}

void QKlipperPowerDevice::setTypeString(const QString &typeString)
{
    if (m_typeString == typeString)
        return;

    if(m_typeNames.contains(typeString))
        setType((Type)m_typeNames.indexOf(typeString));

    m_typeString = typeString;
    emit typeStringChanged();
}

QKlipperPowerDevice::Type QKlipperPowerDevice::type() const
{
    return m_type;
}

void QKlipperPowerDevice::setType(Type type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged();
}
