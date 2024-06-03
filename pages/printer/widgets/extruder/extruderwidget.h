#ifndef EXTRUDERWIDGET_H
#define EXTRUDERWIDGET_H

#include <QWidget>
#include <QFrame>
#include "../../../../ui/circularprogressbar.h"
#include "../../../../types/extruder.h"
#include "../../../../types/printer.h"

namespace Ui {
class ExtruderWidget;
}

class ExtruderWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ExtruderWidget(QWidget *parent = nullptr);
    ~ExtruderWidget();

    void setExtruder(Extruder *extruder);

    void update();

    void setUiClasses();

    virtual void setStyleSheet(QString &styleSheet);

private slots:
    void on_extrsuionFactorSlider_valueChanged(int value);

    void on_extrusionFactorSpinBox_valueChanged(double value);
    void on_console_extrudersUpdate();

    void on_targetTempSpinBox_valueChanged(double arg1);

    void on_pressureAdvanceSpinBox_valueChanged(double arg1);

    void on_smoothTimeSpinBox_valueChanged(double arg1);

    void on_applyButton_clicked();

    void on_resetButton_clicked();

    void on_extrudeButton_clicked();

    void on_retractButton_clicked();

private:
    CircularProgressBar *_temperatureProgressBar;
    Extruder *_extruder;
    Ui::ExtruderWidget *ui;

    bool _updating = false;
    bool _targetTempEdited = false;
    bool _pressureAdvanceEdited = false;
    bool _smoothTimeEdited = false;
    bool _extrusionFactorEdited = false;
};

#endif // EXTRUDERWIDGET_H
