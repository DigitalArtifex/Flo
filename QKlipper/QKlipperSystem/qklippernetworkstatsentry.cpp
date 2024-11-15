#include "qklippernetworkstatsentry.h"

QKlipperNetworkStatsEntry::QKlipperNetworkStatsEntry(QObject *parent)
    : QObject{parent}
{}

QKlipperNetworkStatsEntry::QKlipperNetworkStatsEntry(const QKlipperNetworkStatsEntry &value)
{
    m_bandwidth = value.m_bandwidth;
    m_rxBytes = value.m_rxBytes;
    m_txBytes = value.m_txBytes;
}

QKlipperNetworkStatsEntry::QKlipperNetworkStatsEntry(QKlipperNetworkStatsEntry &&value)
{
    m_bandwidth = value.m_bandwidth;
    m_rxBytes = value.m_rxBytes;
    m_txBytes = value.m_txBytes;
}

QKlipperNetworkStatsEntry &QKlipperNetworkStatsEntry::operator=(const QKlipperNetworkStatsEntry &value)
{
    m_bandwidth = value.m_bandwidth;
    m_rxBytes = value.m_rxBytes;
    m_txBytes = value.m_txBytes;

    return *this;
}

QKlipperNetworkStatsEntry &QKlipperNetworkStatsEntry::operator=(QKlipperNetworkStatsEntry &&value)
{
    m_bandwidth = value.m_bandwidth;
    m_rxBytes = value.m_rxBytes;
    m_txBytes = value.m_txBytes;

    return *this;
}

bool QKlipperNetworkStatsEntry::operator==(const QKlipperNetworkStatsEntry &value)
{
    if(m_bandwidth != value.m_bandwidth) return false;
    if(m_rxBytes != value.m_rxBytes) return false;
    if(m_txBytes != value.m_txBytes) return false;

    return true;
}

bool QKlipperNetworkStatsEntry::operator==(QKlipperNetworkStatsEntry &&value)
{
    if(m_bandwidth != value.m_bandwidth) return false;
    if(m_rxBytes != value.m_rxBytes) return false;
    if(m_txBytes != value.m_txBytes) return false;

    return true;
}

bool QKlipperNetworkStatsEntry::operator!=(const QKlipperNetworkStatsEntry &value)
{
    if(m_bandwidth == value.m_bandwidth &&
        m_rxBytes == value.m_rxBytes &&
        m_txBytes == value.m_txBytes)
        return false;

    return true;
}

bool QKlipperNetworkStatsEntry::operator!=(QKlipperNetworkStatsEntry &&value)
{
    if(m_bandwidth == value.m_bandwidth &&
        m_rxBytes == value.m_rxBytes &&
        m_txBytes == value.m_txBytes)
        return false;

    return true;
}

qreal QKlipperNetworkStatsEntry::rxBytes() const
{
    return m_rxBytes;
}

void QKlipperNetworkStatsEntry::setRxBytes(qreal rxBytes)
{
    if (qFuzzyCompare(m_rxBytes, rxBytes))
        return;
    m_rxBytes = rxBytes;
    emit rxBytesChanged();
}

qreal QKlipperNetworkStatsEntry::txBytes() const
{
    return m_txBytes;
}

void QKlipperNetworkStatsEntry::setTxBytes(qreal txBytes)
{
    if (qFuzzyCompare(m_txBytes, txBytes))
        return;
    m_txBytes = txBytes;
    emit txBytesChanged();
}

qreal QKlipperNetworkStatsEntry::bandwidth() const
{
    return m_bandwidth;
}

void QKlipperNetworkStatsEntry::setBandwidth(qreal bandwidth)
{
    if (qFuzzyCompare(m_bandwidth, bandwidth))
        return;
    m_bandwidth = bandwidth;
    emit bandwidthChanged();
}
