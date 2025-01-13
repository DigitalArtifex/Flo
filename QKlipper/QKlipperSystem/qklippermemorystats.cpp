#include "qklippermemorystats.h"

QKlipperMemoryStats::QKlipperMemoryStats(QObject *parent)
    : QObject{parent}
{}

bool QKlipperMemoryStats::operator==(const QKlipperMemoryStats &value) const
{
    if(m_total != value.m_total) return false;
    if(m_used != value.m_used) return false;
    if(m_average != value.m_average) return false;

    return true;
}

bool QKlipperMemoryStats::operator!=(const QKlipperMemoryStats &value) const
{
    if(m_total == value.m_total &&
        m_used == value.m_used &&
        m_average == value.m_average)
        return false;

    return true;
}

qreal QKlipperMemoryStats::total() const
{
    return m_total;
}

void QKlipperMemoryStats::setTotal(qreal total)
{
    if (qFuzzyCompare(m_total, total))
        return;
    m_total = total;
    emit totalChanged();
}

qreal QKlipperMemoryStats::used() const
{
    return m_used;
}

void QKlipperMemoryStats::setUsed(qreal used)
{
    if (qFuzzyCompare(m_used, used))
        return;
    m_used = used;
    emit usedChanged();
}

qreal QKlipperMemoryStats::average() const
{
    return m_average;
}

void QKlipperMemoryStats::setAverage(qreal average)
{
    if (qFuzzyCompare(m_average, average))
        return;
    m_average = average;
    emit averageChanged();
}
