/*
* Flo :: ExtruderInfoDialog
*
* Provides a dialog for extruder configuration information
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

#ifndef EXTRUDERINFODIALOG_H
#define EXTRUDERINFODIALOG_H

#include <QKlipper/qklipper.h>
#include <QObject>
#include <QQmlEngine>
#include <QResizeEvent>
#include <QTableWidget>
#include <QWidget>
#include "ui/QIconButton/qiconbutton.h"

#include <common/dialog/dialog.h>
#include <ui/LineGraphWidget/linegraphwidget.h>

class ExtruderInfoDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit ExtruderInfoDialog(QKlipperExtruder *extruder, QWidget *parent = nullptr);
        ~ExtruderInfoDialog();

    signals:

    protected slots:
        void onGearRatioChanged();
        void onFullStepsPerRoatationChanged();
        void onCurrentTempChanged();
        void onTargetTempChanged();
        void onSmoothTimeChanged();
        void onPressureAdvanceChanged();
        void onExtrusionFactorChanged();
        void onFilamentDiameterChanged();
        void onNozzleDiameterChanged();
        void onPowerChanged();
        void onInlineResistorChanged();
        void onPullupResistorChanged();
        void onPwmCycleChanged();
        void onRotationDistanceChanged();
        void onInstantCornerVelocityChanged();
        void onPidKDChanged();
        void onPidKIChanged();
        void onPidKPChanged();
        void onMaxExtrudeCrossSectionChanged();
        void onMaxExtrudeOnlyAccelerationChanged();
        void onMaxExtrudeOnlyDistanceChanged();
        void onMaxExtrudeOnlyVelocityChanged();
        void onMaxTempChanged();
        void onMaxPowerChanged();
        void onMicrostepsChanged();
        void onMinExtrudeTempChanged();
        void onMinTempChanged();
        void onCanExtrudeChanged();
        void onNameChanged();
        void onControlPinChanged();
        void onDirPinChanged();
        void onEnablePinChanged();
        void onHeaterPinChanged();
        void onSensorPinChanged();
        void onSensorTypeChanged();
        void onStepPinChanged();
        void onOffsetChanged();
        void onPressureAdvanceSmoothTimeChanged();
        void addTableItem(const QString &name);
        void reset();
        void setupUi();

    protected:
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QKlipperExtruder *m_extruder = nullptr;

        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;
        QTableWidget *m_infoTable;
        QMap<QString, QTableWidgetItem*> m_itemMap;

        QWidget *m_footerWidget = nullptr;
        QIconButton *m_acceptButton = nullptr;
};

#endif // EXTRUDERINFODIALOG_H
