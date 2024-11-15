#include "qklippermoonrakerstatsentry.h"

QKlipperMoonrakerStatsEntry::QKlipperMoonrakerStatsEntry()
    : QVariant{}
{}

QKlipperMoonrakerStatsEntry::QKlipperMoonrakerStatsEntry(const QKlipperMoonrakerStatsEntry &value)
{
    m_time = value.m_time;
    m_cpuUsage = value.m_cpuUsage;
    m_memory = value.m_memory;
}

QKlipperMoonrakerStatsEntry &QKlipperMoonrakerStatsEntry::operator=(const QKlipperMoonrakerStatsEntry &value)
{
    m_time = value.m_time;
    m_cpuUsage = value.m_cpuUsage;
    m_memory = value.m_memory;

    return *this;
}

bool QKlipperMoonrakerStatsEntry::operator==(const QKlipperMoonrakerStatsEntry &value)
{
    if(m_time != value.m_time) return false;
    if(m_cpuUsage != value.m_cpuUsage) return false;
    if(m_memory != value.m_memory) return false;

    return true;
}

bool QKlipperMoonrakerStatsEntry::operator!=(const QKlipperMoonrakerStatsEntry &value)
{
    if(m_time == value.m_time &&
        m_cpuUsage == value.m_cpuUsage &&
        m_memory == value.m_memory)
        return false;

    return true;
}

qreal QKlipperMoonrakerStatsEntry::time() const
{
    return m_time;
}

void QKlipperMoonrakerStatsEntry::setTime(qreal time)
{
    m_time = time;
}

qreal QKlipperMoonrakerStatsEntry::cpuUsage() const
{
    return m_cpuUsage;
}

void QKlipperMoonrakerStatsEntry::setCpuUsage(qreal cpuUsage)
{
    m_cpuUsage = cpuUsage;
}

qreal QKlipperMoonrakerStatsEntry::memory() const
{
    return m_memory;
}

void QKlipperMoonrakerStatsEntry::setMemory(qreal memory)
{
    m_memory = memory;
}

QString QKlipperMoonrakerStatsEntry::memoryUnits() const
{
    return m_memoryUnits;
}

void QKlipperMoonrakerStatsEntry::setMemoryUnits(const QString &memoryUnits)
{
    m_memoryUnits = memoryUnits;
}

