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
class QKlipperNetworkStatsEntry : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperNetworkStatsEntry(QObject *parent = nullptr);

    QKlipperNetworkStatsEntry(const QKlipperNetworkStatsEntry &value);
    QKlipperNetworkStatsEntry(QKlipperNetworkStatsEntry &&value);
    QKlipperNetworkStatsEntry &operator=(const QKlipperNetworkStatsEntry &value);
    QKlipperNetworkStatsEntry &operator=(QKlipperNetworkStatsEntry &&value);
    bool operator==(const QKlipperNetworkStatsEntry &value);
    bool operator==(QKlipperNetworkStatsEntry &&value);
    bool operator!=(const QKlipperNetworkStatsEntry &value);
    bool operator!=(QKlipperNetworkStatsEntry &&value);

    qreal rxBytes() const;
    qreal txBytes() const;
    qreal bandwidth() const;

public slots:
    void setRxBytes(qreal rxBytes);
    void setTxBytes(qreal txBytes);
    void setBandwidth(qreal bandwidth);

private slots:

signals:
    void rxBytesChanged();
    void txBytesChanged();
    void bandwidthChanged();

private:
    qreal m_rxBytes = 0;
    qreal m_txBytes = 0;
    qreal m_bandwidth = 0;

    Q_PROPERTY(qreal rxBytes READ rxBytes WRITE setRxBytes NOTIFY rxBytesChanged FINAL)
    Q_PROPERTY(qreal txBytes READ txBytes WRITE setTxBytes NOTIFY txBytesChanged FINAL)
    Q_PROPERTY(qreal bandwidth READ bandwidth WRITE setBandwidth NOTIFY bandwidthChanged FINAL)
};

#endif // QKLIPPERNETWORKSTATSENTRY_H
