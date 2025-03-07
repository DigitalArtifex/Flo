/*
* Flo :: LedStripCard
*
* Provides an overview of a single configured LED Strip
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

#ifndef LEDSTRIPCARD_H
#define LEDSTRIPCARD_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QKlipper/qklipper.h>
#include "common/CardWidget/cardwidget.h"
#include "ui/Switch/switch.h"
#include "ui/QIconButton/qiconbutton.h"

class LedStripCard : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit LedStripCard(QKlipperLedStrip *strip, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onSwitchChanged(bool toggled);
        void onLedIsOnChanged();
        void onLedErrorChanged();
        void onLedSpeedChanged();
        void onLedPresetChanged();
        void onLedBrightnessChanged();
        void onLedIntensityChanged();
        void onResetButtonPressed();
        void onApplyButtonPressed();
        void onValuesUpdated(int value);
        void setupUi();

    private:
        QKlipperLedStrip *m_ledStrip = nullptr;
        QIconButton *m_powerButton = nullptr;
        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;
        Switch *m_onSwitch = nullptr;
        QLabel *m_iconLabel = nullptr;
        QLabel *m_nameLabel = nullptr;
        QLabel *m_errorLabel = nullptr;
        QLabel *m_speedLabel = nullptr;
        QLabel *m_presetLabel = nullptr;
        QLabel *m_brightnessLabel = nullptr;
        QLabel *m_intensityLabel = nullptr;
        QLabel *m_chainCountLabel = nullptr;
        QSpinBox *m_speedSpinBox = nullptr;
        QSpinBox *m_brightnessSpinBox = nullptr;
        QSpinBox *m_presetSpinBox = nullptr;
        QSpinBox *m_intensitySpinBox = nullptr;
        QIconButton *m_resetButton = nullptr;
        QIconButton *m_applyButton = nullptr;
        bool m_commandBlock = false;
};

#endif // LEDSTRIPCARD_H
