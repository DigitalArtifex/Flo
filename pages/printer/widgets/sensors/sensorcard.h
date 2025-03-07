/*
* Flo :: SensorCard
*
* Provides an overview of a single configured Sensor
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SENSORCARD_H
#define SENSORCARD_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <common/CardWidget/cardwidget.h>
#include <QKlipper/qklipper.h>

class SensorCard : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit SensorCard(QKlipperSensor *sensor, QWidget *parent = nullptr);

        virtual void setStyleSheet(const QString &styleSheet);

    signals:

    protected slots:
        void setupUi();
        void setupIcons();

    private:
        QKlipperSensor *m_sensor = nullptr;
        QIconButton *m_powerButton = nullptr;
        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;
};

#endif // SENSORCARD_H
