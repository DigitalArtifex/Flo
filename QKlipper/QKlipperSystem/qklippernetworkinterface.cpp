#include "qklippernetworkinterface.h"

QKlipperNetworkInterface::QKlipperNetworkInterface(QObject *parent)
    : QObject{parent}
{

}

QKlipperNetworkInterface::QKlipperNetworkInterface(const QKlipperNetworkInterface &value)
{
    m_ipAddresses = value.m_ipAddresses;
    m_macAddress = value.m_macAddress;
}

QKlipperNetworkInterface::QKlipperNetworkInterface(QKlipperNetworkInterface &&value)
{
    m_ipAddresses = value.m_ipAddresses;
    m_macAddress = value.m_macAddress;
}

QKlipperNetworkInterface &QKlipperNetworkInterface::operator=(const QKlipperNetworkInterface &value)
{
    m_ipAddresses = value.m_ipAddresses;
    m_macAddress = value.m_macAddress;

    return *this;
}

QKlipperNetworkInterface &QKlipperNetworkInterface::operator=(QKlipperNetworkInterface &&value)
{
    m_ipAddresses = value.m_ipAddresses;
    m_macAddress = value.m_macAddress;

    return *this;
}

bool QKlipperNetworkInterface::operator==(const QKlipperNetworkInterface &value)
{
    foreach(QKlipperNetworkAddress ip, value.m_ipAddresses)
    {
        if(!m_ipAddresses.contains(ip))
            return false;
    }

    if(m_macAddress != value.m_macAddress) return false;

    return true;
}

bool QKlipperNetworkInterface::operator==(QKlipperNetworkInterface &&value)
{
    foreach(QKlipperNetworkAddress ip, value.m_ipAddresses)
    {
        if(!m_ipAddresses.contains(ip))
            return false;
    }

    if(m_macAddress != value.m_macAddress) return false;

    return true;
}

bool QKlipperNetworkInterface::operator!=(const QKlipperNetworkInterface &value)
{
    foreach(QKlipperNetworkAddress ip, value.m_ipAddresses)
    {
        if(!m_ipAddresses.contains(ip))
            return true;
    }

    if(m_macAddress == value.m_macAddress) return false;

    return true;
}

bool QKlipperNetworkInterface::operator!=(QKlipperNetworkInterface &&value)
{
    foreach(QKlipperNetworkAddress ip, value.m_ipAddresses)
    {
        if(!m_ipAddresses.contains(ip))
            return true;
    }

    if(m_macAddress == value.m_macAddress) return false;

    return true;
}

QString QKlipperNetworkInterface::macAddress() const
{
    return m_macAddress;
}

void QKlipperNetworkInterface::setMacAddress(const QString &macAddress)
{
    if (m_macAddress == macAddress)
        return;

    m_macAddress = macAddress;
    emit macAddressChanged();
}

QList<QKlipperNetworkAddress> QKlipperNetworkInterface::ipAddresses() const
{
    return m_ipAddresses;
}

void QKlipperNetworkInterface::setIpAddresses(const QList<QKlipperNetworkAddress> &ipAddresses)
{
    bool changed = false;

    foreach(QKlipperNetworkAddress ip, ipAddresses)
    {
        if(!m_ipAddresses.contains(ip))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_ipAddresses = ipAddresses;
    emit ipAddressesChanged();
}
