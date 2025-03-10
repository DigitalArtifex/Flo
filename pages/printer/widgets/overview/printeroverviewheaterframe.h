#ifndef PRINTEROVERVIEWHEATERFRAME_H
#define PRINTEROVERVIEWHEATERFRAME_H

#include <QFrame>
#include <QKlipper/QKlipperPrinter/qklipperheater.h>

namespace Ui {
class PrinterOverviewHeaterFrame;
}

class PrinterOverviewHeaterFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterOverviewHeaterFrame(QKlipperHeater *heater, QWidget *parent = nullptr);
    ~PrinterOverviewHeaterFrame();

protected slots:
    void onHeaterPowerChanged();

private:
    Ui::PrinterOverviewHeaterFrame *ui;

    QKlipperHeater *m_heater = nullptr;
};

#endif // PRINTEROVERVIEWHEATERFRAME_H
