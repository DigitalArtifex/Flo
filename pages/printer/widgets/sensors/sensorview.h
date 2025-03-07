/*
* Flo :: SensorView
*
* Provides an overview of configured Sensors
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

#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QMap>
#include <QScrollArea>
#include <ui/layouts/qflowlayout.h>
#include <common/CardWidget/cardwidget.h>
#include <QKlipper/qklipper.h>


#include "sensorcard.h"

class SensorView : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit SensorView(QKlipperSystem *system, QWidget *parent = nullptr);

        QKlipperSystem *system() const;

    public slots:
        void setSystem(QKlipperSystem *system);
        void setStyleSheet(const QString &styleSheet);
        virtual void reset();

    protected slots:
        void clear();
        void setupUi();
        void setupIcons();
        void onDeviceListChanged();

    private:
        QMap<QString, SensorCard*> m_sensors;
        QKlipperSystem *m_system = nullptr;
        QFlowLayout *m_scrollAreaLayout = nullptr;
        QWidget *m_scrollAreaWidget = nullptr;
        QScrollArea *m_scrollArea = nullptr;
        QSpacerItem *m_spacer = nullptr;
};

#endif // SENSORVIEW_H
