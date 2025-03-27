/*
* Flo :: ExtruderWidget
*
* Provides an overview of an individual extruder
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

#ifndef EXTRUDERWIDGET_H
#define EXTRUDERWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QStyle>
#include <QScreen>
#include <QGraphicsEffect>
#include <QtDAWidgets/qgaugewidget.h>
#include <QKlipper/qklipper.h>

#include "common/QAnimatedWidget/qanimatedwidget.h"

#include "extrudermaterialsdialog.h"
#include "ui/LineGraphWidget/linegraphwidget.h"

#include <QtDAWidgets/qthrobberwidget.h>
#include <dialogs/PidDialog/piddialog.h>
#include <dialogs/PositionDialog/positiondialog.h>

namespace Ui {
class ExtruderWidget;
}

class ExtruderWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ExtruderWidget(QKlipperExtruder *extruder, QWidget *parent = nullptr);
    ~ExtruderWidget();

    void setExtruder(QKlipperExtruder *extruder);

    void setUiClasses();

    void setIcons();

signals:
    void dialogRequested(QDialog *);

protected:
    virtual void changeEvent(QEvent *event) override;

private slots:
    void on_targetTemperatureSpinBox_valueChanged(double arg1);
    void on_pressureAdvanceSpinBox_valueChanged(double arg1);
    void on_smoothTimeSpinBox_valueChanged(double arg1);
    void on_applyButton_clicked();
    void on_resetButton_clicked();
    void on_extrudeButton_clicked();
    void on_retractButton_clicked();

    void onPidDialogFinished(int returnCode);
    void onMaterialDialogFinished(int returnCode);
    void onPreheatDialogFinished(int returnCode);

    void onExtruderCanExtrudeChanged();
    void onExtruderCurrentTempChanged();
    void onExtruderTargetTempChanged();
    void onExtruderGearRatioChanged();
    void onExtruderNozzleDiameterChanged();
    void onExtruderMaxTempChanged();
    void onExtruderMinTempChanged();
    void onExtruderPressureAdvanceChanged();
    void onExtruderSmoothTimeChanged();
    void onExtruderFanSpeedChanged();
    void onExtruderPowerChanged();
    void onExtruderFanChanged();

    void updateUiValues();
    void updateSettingsButtons();

    void showThrobber();
    void hideThrobber();

    void on_pidButton_clicked();

    void on_preheatButton_clicked();

private:
    LineGraphWidget *m_temperatureGraph = nullptr;

    QKlipperExtruder *m_extruder;
    Ui::ExtruderWidget *ui;

    bool m_updating = false;
    bool m_targetTemperatureEdited = false;
    bool m_pressureAdvanceEdited = false;
    bool m_smoothTimeEdited = false;
    bool m_extrusionFactorEdited = false;

    QFrame *m_throbberFrame = nullptr;
    QThrobberWidget *m_throbber = nullptr;

    PidDialog *m_pidDialog = nullptr;
    PidDialog *m_preheatDialog = nullptr;
    ExtruderMaterialsDialog *m_materialDialog = nullptr;
};

#endif // EXTRUDERWIDGET_H
