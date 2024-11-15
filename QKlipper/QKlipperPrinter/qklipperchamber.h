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

#ifndef QKLIPPERCHAMBER_H
#define QKLIPPERCHAMBER_H

#include <QObject>

class QKlipperChamber : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperChamber(QObject *parent = nullptr);

    qreal currentTemperature() const;
    qreal targetTemperature() const;

    qreal maxWatts() const;

public slots:
    void setCurrentTemperature(qreal currentTemperature);
    void setTargetTemperature(qreal targetTemperature);

    void setMaxWatts(qreal maxWatts);

signals:
    void currentTemperatureChanged();
    void targetTemperatureChanged();

    void maxWattsChanged();

private:
    qreal m_currentTemperature = 0.0;
    qreal m_targetTemperature = 0.0;
    qreal m_maxWatts = 0.0;
    qreal m_power = 0.0;

    Q_PROPERTY(qreal currentTemperature READ currentTemperature WRITE setCurrentTemperature NOTIFY currentTemperatureChanged FINAL)
    Q_PROPERTY(qreal targetTemperature READ targetTemperature WRITE setTargetTemperature NOTIFY targetTemperatureChanged FINAL)
    Q_PROPERTY(qreal maxWatts READ maxWatts WRITE setMaxWatts NOTIFY maxWattsChanged FINAL)
};

#endif // QKLIPPERCHAMBER_H
