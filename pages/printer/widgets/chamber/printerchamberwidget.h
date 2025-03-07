#ifndef PRINTERCHAMBERWIDGET_H
#define PRINTERCHAMBERWIDGET_H

#include <QFrame>
#include <QtDAWidgets/qgaugewidget.h>
#include "pages/printer/widgets/temperature/temperaturewidget.h"

namespace Ui {
class PrinterChamberWidget;
}

class PrinterChamberWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterChamberWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterChamberWidget();

protected slots:
    void setIcons();

protected:
    virtual void changeEvent(QEvent *event) override;

private:
    Ui::PrinterChamberWidget *ui;

    PrinterTemperatureWidget *m_chamberTemperatureWidget = nullptr;
    QGaugeWidget *m_chamberTemperatureBar = nullptr;
};

#endif // PRINTERCHAMBERWIDGET_H
