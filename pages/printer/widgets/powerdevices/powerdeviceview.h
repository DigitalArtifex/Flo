/*
* Flo :: PowerDeviceView
*
* Provides an overview of configured Power Devices
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

#ifndef POWERDEVICEVIEW_H
#define POWERDEVICEVIEW_H

#include <QObject>
#include <QScrollArea>
#include <QKlipper/qklipper.h>
#include "common/CardWidget/cardwidget.h"
#include "powerdevicecard.h"
#include "ui/layouts/qflowlayout.h"

class PowerDeviceView : public CardWidget
{
        Q_OBJECT
    public:
        explicit PowerDeviceView(QKlipperSystem *system, QWidget *parent);

        QKlipperSystem *system() const;

    public slots:
        void setSystem(QKlipperSystem *system);
        void setStyleSheet(const QString &styleSheet);

    protected slots:
        void clear();
        void setupUi();
        void setupIcons();
        void onDeviceListChanged();

    private:
        QMap<QString, PowerDeviceCard*> m_powerDevices;
        QKlipperSystem *m_system = nullptr;
        QFlowLayout *m_scrollAreaLayout = nullptr;
        QWidget *m_scrollAreaWidget = nullptr;
        QScrollArea *m_scrollArea = nullptr;
        QSpacerItem *m_spacer = nullptr;
};

#endif // POWERDEVICEVIEW_H
