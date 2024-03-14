#ifndef PRINTERPAGE_H
#define PRINTERPAGE_H

#include <QFrame>
#include <QMap>

#include "extruderwidget.h"
#include "../types/printer.h"

namespace Ui {
class PrinterPage;
}

class PrinterPage : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterPage(QWidget *parent = nullptr);
    ~PrinterPage();
    void addExtruder(Extruder *extruder, QString name = QString("Extruder"));

    void update(Printer *printer);
    void setStyleSheet(QString style);
    void setIcons();

private slots:
    void on_xPosDecreaseButton_clicked();

private:
    CircularProgressBar *_bedTemperatureBar;
    CircularProgressBar *_chamberTemperatureBar;
    CircularProgressBar *_extruderTemperatureBar;
    QMap<int, ExtruderWidget*> _extruderMap;

    Ui::PrinterPage *ui;
    void setupUiClasses();
};

#endif // PRINTERPAGE_H
