#ifndef EXTRUDERWIDGET_H
#define EXTRUDERWIDGET_H

#include <QWidget>
#include "../../ui/circularprogressbar.h"
#include "../../types/extruder.h"

namespace Ui {
class ExtruderWidget;
}

class ExtruderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExtruderWidget(QWidget *parent = nullptr);
    ~ExtruderWidget();

    void setTargetTemp(qreal temp);
    void setCurrentTemp(qreal temp);
    void setPower(qreal power);
    void setPressureAdvance(qreal advance);
    void setSmoothTime(qreal time);

    void setExtruder(Extruder *extruder);

    void update();

    void setUiClasses();

private:
    CircularProgressBar *_temperatureProgressBar;
    Extruder *_extruder;
    Ui::ExtruderWidget *ui;
};

#endif // EXTRUDERWIDGET_H
