/*
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERMOONRAKERSTATSENTRY_H
#define QKLIPPERMOONRAKERSTATSENTRY_H

#include <QVariant>
class QKlipperSystem;
class QKlipperConsole;
/*!
 * \brief Filled by machine.proc_stats
 */
class QKlipperMoonrakerStatsEntry
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperMoonrakerStatsEntry() = default;
    ~QKlipperMoonrakerStatsEntry() = default;

    QKlipperMoonrakerStatsEntry(const QKlipperMoonrakerStatsEntry &value)
    {
        m_time = value.m_time;
        m_cpuUsage = value.m_cpuUsage;
        m_memory = value.m_memory;
    }
    QKlipperMoonrakerStatsEntry &operator=(const QKlipperMoonrakerStatsEntry &value)
    {
        m_time = value.m_time;
        m_cpuUsage = value.m_cpuUsage;
        m_memory = value.m_memory;

        return *this;
    }
    bool operator==(const QKlipperMoonrakerStatsEntry &value) const
    {
        if(m_time != value.m_time) return false;
        if(m_cpuUsage != value.m_cpuUsage) return false;
        if(m_memory != value.m_memory) return false;

        return true;
    }
    bool operator!=(const QKlipperMoonrakerStatsEntry &value) const
    {
        if(m_time == value.m_time &&
            m_cpuUsage == value.m_cpuUsage &&
            m_memory == value.m_memory)
            return false;

        return true;
    }

    qreal time() const { return m_time; }
    qreal cpuUsage() const { return m_cpuUsage; }
    qreal memory() const { return m_memory; }
    QString memoryUnits() const { return m_memoryUnits; }

protected:
    void setTime(qreal time) { m_time = time; }
    void setCpuUsage(qreal cpuUsage) { m_cpuUsage = cpuUsage; }
    void setMemory(qreal memory) { m_memory = memory; }
    void setMemoryUnits(const QString &memoryUnits) { m_memoryUnits = memoryUnits; }

private:
    qreal m_time = 0;
    qreal m_cpuUsage = 0;
    qreal m_memory = 0;

    QString m_memoryUnits;
};

#endif // QKLIPPERMOONRAKERSTATSENTRY_H
