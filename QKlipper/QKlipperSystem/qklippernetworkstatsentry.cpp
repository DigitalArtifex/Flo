#include "qklippernetworkstatsentry.h"

QKlipperNetworkStatsEntry::QKlipperNetworkStatsEntry(const QKlipperNetworkStatsEntry &value)
{
    m_rxBytes = value.m_rxBytes;
    m_txBytes = value.m_txBytes;
    m_bandwidth = value.m_bandwidth;
}

bool QKlipperNetworkStatsEntry::operator==(const QKlipperNetworkStatsEntry &value) const
{
    if(m_bandwidth != value.m_bandwidth) return false;
    if(m_rxBytes != value.m_rxBytes) return false;
    if(m_txBytes != value.m_txBytes) return false;

    return true;
}

bool QKlipperNetworkStatsEntry::operator!=(const QKlipperNetworkStatsEntry &value) const
{
    if(m_bandwidth == value.m_bandwidth &&
        m_rxBytes == value.m_rxBytes &&
        m_txBytes == value.m_txBytes)
        return false;

    return true;
}

QKlipperNetworkStatsEntry &QKlipperNetworkStatsEntry::operator=(const QKlipperNetworkStatsEntry &value)
{
    m_rxBytes = value.m_rxBytes;
    m_txBytes = value.m_txBytes;
    m_bandwidth = value.m_bandwidth;

    return (*this);
}

qreal QKlipperNetworkStatsEntry::rxBytes() const
{
    return m_rxBytes;
}

void QKlipperNetworkStatsEntry::setRxBytes(qreal rxBytes)
{
    m_rxBytes = rxBytes;
}

qreal QKlipperNetworkStatsEntry::txBytes() const
{
    return m_txBytes;
}

void QKlipperNetworkStatsEntry::setTxBytes(qreal txBytes)
{
    m_txBytes = txBytes;
}

qreal QKlipperNetworkStatsEntry::bandwidth() const
{
    return m_bandwidth;
}

void QKlipperNetworkStatsEntry::setBandwidth(qreal bandwidth)
{
    m_bandwidth = bandwidth;
}
