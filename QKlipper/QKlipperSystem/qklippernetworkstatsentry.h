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

#ifndef QKLIPPERNETWORKSTATSENTRY_H
#define QKLIPPERNETWORKSTATSENTRY_H

#include <QObject>
class QKlipperSystem;
class QKlipperConsole;
/*!
 * \brief Filled by machine.proc_stats
 */
class QKlipperNetworkStatsEntry
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperNetworkStatsEntry() = default;
    ~QKlipperNetworkStatsEntry() = default;
    QKlipperNetworkStatsEntry(const QKlipperNetworkStatsEntry &value);

    bool operator==(const QKlipperNetworkStatsEntry &value) const;
    bool operator!=(const QKlipperNetworkStatsEntry &value) const;
    QKlipperNetworkStatsEntry &operator=(const QKlipperNetworkStatsEntry &value);

    qreal rxBytes() const;
    qreal txBytes() const;
    qreal bandwidth() const;

    void setRxBytes(qreal rxBytes);
    void setTxBytes(qreal txBytes);
    void setBandwidth(qreal bandwidth);

private:

private:
    qreal m_rxBytes = 0;
    qreal m_txBytes = 0;
    qreal m_bandwidth = 0;
};

Q_DECLARE_METATYPE(QKlipperNetworkStatsEntry)

#endif // QKLIPPERNETWORKSTATSENTRY_H
