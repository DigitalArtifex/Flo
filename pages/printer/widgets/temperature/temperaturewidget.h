/*
* Flo :: PrinterTemperatureWidget
*
* Provides a widget for monitoring vital temperatures in the system
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

#ifndef TEMPERATUREWIDGET_H
#define TEMPERATUREWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

#include <QKlipper/qklipper.h>
#include "common/CardWidget/cardwidget.h"
#include "ui/LineGraphWidget/linegraphwidget.h"

class PrinterTemperatureWidget : public CardWidget
{
        Q_OBJECT
    public:
        explicit PrinterTemperatureWidget(QKlipperInstance *instance, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onExtruderCurrentTemperatureChanged();
        void onBedCurrentTemperatureChanged();
        void onInstanceConnected(QKlipperInstance *instance);
        void onInstanceDisconnected(QKlipperInstance *instance);

    protected:
        void setupUi();

    private:
        QKlipperInstance *m_instance = nullptr;
        QVBoxLayout *m_centralLayout = nullptr;
        QWidget *m_centralWidget = nullptr;

        LineGraphWidget *m_temperatureGraph = nullptr;
};

#endif // TEMPERATUREWIDGET_H
