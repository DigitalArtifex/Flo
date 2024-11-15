#ifndef EXTRUDERWIDGET_H
#define EXTRUDERWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QStyle>
#include "../../../../ui/circularprogressbar.h"
#include <QKlipper/qklipper.h>

namespace Ui {
class ExtruderWidget;
}

class ExtruderWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ExtruderWidget(QWidget *parent = nullptr);
    ~ExtruderWidget();

    void setExtruder(QKlipperExtruder *extruder);

    void setUiClasses();

    virtual void setStyleSheet(QString &styleSheet);
    virtual void setIcons();

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
    void onExtruderPressureAdvanceChanged();
    void onExtruderSmoothTimeChanged();
    void onExtruderExtrusionFactorChanged();
    void onExtruderFanSpeedChanged();
    void onPartsFanSpeedChanged();
    void onPartsFanChanged();
    void onExtruderFanChanged();

    void updateUiValues();

private:
    CircularProgressBar *m_temperatureProgressBar;
    QKlipperExtruder *m_extruder;
    Ui::ExtruderWidget *ui;

    bool m_updating = false;
    bool m_targetTempEdited = false;
    bool m_pressureAdvanceEdited = false;
    bool m_smoothTimeEdited = false;
    bool m_extrusionFactorEdited = false;
};

#endif // EXTRUDERWIDGET_H
