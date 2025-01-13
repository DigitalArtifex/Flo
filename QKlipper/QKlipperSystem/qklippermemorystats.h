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

#ifndef QKLIPPERMEMORYSTATS_H
#define QKLIPPERMEMORYSTATS_H

#include <QObject>
class QKlipperSystem;
class QKlipperConsole;

/*!
 * \brief Filled by machine.proc_stats
 */
class QKlipperMemoryStats : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperMemoryStats(QObject *parent = nullptr);

    bool operator==(const QKlipperMemoryStats &value) const;
    bool operator!=(const QKlipperMemoryStats &value) const;

    qreal total() const;
    qreal used() const;
    qreal average() const;

public slots:
    void setTotal(qreal total);
    void setUsed(qreal used);
    void setAverage(qreal average);

signals:
    void totalChanged();
    void usedChanged();
    void averageChanged();

private:
    qreal m_total = 0;
    qreal m_used = 0;
    qreal m_average = 0;

    Q_PROPERTY(qreal total READ total WRITE setTotal NOTIFY totalChanged FINAL)
    Q_PROPERTY(qreal used READ used WRITE setUsed NOTIFY usedChanged FINAL)
    Q_PROPERTY(qreal average READ average WRITE setAverage NOTIFY averageChanged FINAL)
};

#endif // QKLIPPERMEMORYSTATS_H
