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

#ifndef QKLIPPERTHROTTLESTATE_H
#define QKLIPPERTHROTTLESTATE_H

#include <QObject>
class QKlipperSystem;
class QKlipperConsole;
/*!
 * \brief Filled by machine.proc_stats
 */
class QKlipperThrottleState : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperThrottleState(QObject *parent = nullptr);

    QKlipperThrottleState(const QKlipperThrottleState &value);
    QKlipperThrottleState(QKlipperThrottleState &&value);
    QKlipperThrottleState &operator=(const QKlipperThrottleState &value);
    QKlipperThrottleState &operator=(QKlipperThrottleState &&value);
    bool operator==(const QKlipperThrottleState &value);
    bool operator==(QKlipperThrottleState &&value);
    bool operator!=(const QKlipperThrottleState &value);
    bool operator!=(QKlipperThrottleState &&value);

    qint32 bits() const;

    QStringList flags() const;

public slots:
    void setBits(qint32 bits);

    void setFlags(const QStringList &flags);

private slots:

signals:

    void bitsChanged();

    void flagsChanged();

private:
    qint32 m_bits = 0;

    QStringList m_flags;

    Q_PROPERTY(qint32 bits READ bits WRITE setBits NOTIFY bitsChanged FINAL)
    Q_PROPERTY(QStringList flags READ flags WRITE setFlags NOTIFY flagsChanged FINAL)
};

#endif // QKLIPPERTHROTTLESTATE_H
