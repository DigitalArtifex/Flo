/*
* Flo :: PowerDeviceCard
*
* Provides an overview of a single configured Power Device
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

#ifndef POWERDEVICECARD_H
#define POWERDEVICECARD_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QLabel>
#include <ui/Switch/switch.h>
#include <QKlipper/qklipper.h>
#include <common/CardWidget/cardwidget.h>
#include <ui/QIconButton/qiconbutton.h>
#include <flo/settings.h>

class PowerDeviceCard : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit PowerDeviceCard(QKlipperPowerDevice *powerDevice, QWidget *parent);

        QKlipperPowerDevice *powerDevice() const;

    public slots:
        void setPowerDevice(QKlipperPowerDevice *powerDevice);
        void setStyleSheet(const QString &styleSheet);

    protected slots:
        void setupUi();
        void setupIcons();
        void onDeviceStateChanged();
        void onSwitchStateChanged(bool on);

        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);

    private:
        bool m_pressed = false;
        bool m_checked = false;
        bool m_checkable = false;
        bool m_exclusive = false;

        QKlipperPowerDevice *m_powerDevice = nullptr;
        QIconButton *m_powerButton = nullptr;
        QWidget *m_centralWidget = nullptr;
        QHBoxLayout *m_centralLayout = nullptr;
        Switch *m_onSwitch = nullptr;
        QLabel *m_iconLabel = nullptr;
        QLabel *m_textLabel = nullptr;
};

#endif // POWERDEVICECARD_H
