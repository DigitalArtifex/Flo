#ifndef EXTRUDERWIDGET_H
#define EXTRUDERWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QStyle>
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
    virtual void setIcons();

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
    CircularProgressBar *m_temperatureProgressBar;
    Extruder *m_extruder;
    Ui::ExtruderWidget *ui;

    bool m_updating = false;
    bool m_targetTempEdited = false;
    bool m_pressureAdvanceEdited = false;
    bool m_smoothTimeEdited = false;
    bool m_extrusionFactorEdited = false;
};

#endif // EXTRUDERWIDGET_H
