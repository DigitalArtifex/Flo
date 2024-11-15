#include "qklippercanbus.h"

QKlipperCanBus::QKlipperCanBus(QObject *parent)
    : QObject{parent}
{}

QList<QKlipperCanBusInterface> QKlipperCanBus::interfaces() const
{
    return m_interfaces;
}

void QKlipperCanBus::setInterfaces(const QList<QKlipperCanBusInterface> &interfaces)
{
    bool changed = false;

    foreach(QKlipperCanBusInterface interface, interfaces)
    {
        if(!m_interfaces.contains(interface))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_interfaces = interfaces;
    emit interfacesChanged();
}

QKlipperCanBusDeviceMap QKlipperCanBus::devices() const
{
    return m_devices;
}

void QKlipperCanBus::setDevices(const QKlipperCanBusDeviceMap &devices)
{
    bool changed = false;
    QStringList keys = devices.keys();

    foreach(QString key, keys)
    {
        if(!m_devices.contains(key))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_devices = devices;
    emit devicesChanged();
}
