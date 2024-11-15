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
class QKlipperMoonrakerStatsEntry : public QVariant
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperMoonrakerStatsEntry();

    QKlipperMoonrakerStatsEntry(const QKlipperMoonrakerStatsEntry &value);
    QKlipperMoonrakerStatsEntry &operator=(const QKlipperMoonrakerStatsEntry &value);
    bool operator==(const QKlipperMoonrakerStatsEntry &value);
    bool operator!=(const QKlipperMoonrakerStatsEntry &value);

    qreal time() const;
    qreal cpuUsage() const;
    qreal memory() const;
    QString memoryUnits() const;

    void setTime(qreal time);
    void setCpuUsage(qreal cpuUsage);
    void setMemory(qreal memory);
    void setMemoryUnits(const QString &memoryUnits);

private:
    qreal m_time = 0;
    qreal m_cpuUsage = 0;
    qreal m_memory = 0;

    QString m_memoryUnits;
};

#endif // QKLIPPERMOONRAKERSTATSENTRY_H
