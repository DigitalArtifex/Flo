#ifndef EXTRUDERWIDGET_H
#define EXTRUDERWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QStyle>
#include <QScreen>
#include <QGraphicsEffect>
#include "../../../../ui/qgaugewidget.h"
#include <QKlipper/qklipper.h>

#include "extruderinfodialog.h"
#include "extrudermaterialsdialog.h"

#include "extrudertemperaturewidget.h"
#include <ui/QThrobber/qthrobber.h>
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

    void setupIcons();

protected:
    virtual void changeEvent(QEvent *event) override;

private slots:
    void on_extrsuionFactorSlider_valueChanged(int value);
    void on_extrusionFactorSpinBox_valueChanged(double value);
    void on_targetTempSpinBox_valueChanged(double arg1);
    void on_pressureAdvanceSpinBox_valueChanged(double arg1);
    void on_smoothTimeSpinBox_valueChanged(double arg1);
    void on_applyButton_clicked();
    void on_resetButton_clicked();
    void on_extrudeButton_clicked();
    void on_retractButton_clicked();

    void onExtruderCanExtrudeChanged();
    void onExtruderCurrentTempChanged();
    void onExtruderTargetTempChanged();
    void onExtruderMaxTempChanged();
    void onExtruderMinTempChanged();
    void onExtruderPressureAdvanceChanged();
    void onExtruderSmoothTimeChanged();
    void onExtruderExtrusionFactorChanged();
    void onExtruderFanSpeedChanged();
    void onExtruderPowerChanged();
    void onExtruderFanChanged();

    void updateUiValues();
    void updateSettingsButtons();

    void onExtruderSettingsButtonClicked();
    void onMaterialsButtonClicked();
    void onPidButtonClicked();
    void onPreheatButtonClicked();
    void onOffsetButtonClicked();

    void showThrobber();
    void hideThrobber();

private:
    ExtruderTemperatureWidget *m_temperatureWidget = nullptr;

    QGaugeWidget *m_temperatureProgressBar = nullptr;
    QGaugeWidget *m_powerProgressBar = nullptr;
    QGaugeWidget *m_extruderFanProgressBar = nullptr;

    QKlipperExtruder *m_extruder;
    Ui::ExtruderWidget *ui;

    bool m_updating = false;
    bool m_targetTempEdited = false;
    bool m_pressureAdvanceEdited = false;
    bool m_smoothTimeEdited = false;
    bool m_extrusionFactorEdited = false;

    QIconButton *m_pidTuneButton = nullptr;
    QIconButton *m_setOffsetButton = nullptr;
    QIconButton *m_pressureAdvanceButton = nullptr;
    QIconButton *m_preheatButton = nullptr;
    QIconButton *m_materialButton = nullptr;
    QIconButton *m_settingsButton = nullptr;

    QFrame *m_throbberFrame = nullptr;
    QThrobber *m_throbber = nullptr;
};

#endif // EXTRUDERWIDGET_H
