#ifndef PRINTERPAGE_H
#define PRINTERPAGE_H

#include <QFrame>
#include <QMap>

#include "extruderwidget.h"
#include "../../types/printer.h"

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

    void setStyleSheet(QString style);
    void setIcons();

    Printer *printer() const;
    void setPrinter(Printer *printer);

private slots:
    void on_xPosDecreaseButton_clicked();
    void on_terminalButton_toggled(bool checked);
    void on_overviewButton_toggled(bool checked);
    void on_filesButton_toggled(bool checked);
    void on_bedMeshButton_toggled(bool checked);
    void on_settingsButton_toggled(bool checked);
    void on_printerUpdate(Printer *printer);

private:
    CircularProgressBar *_bedTemperatureBar;
    CircularProgressBar *_chamberTemperatureBar;
    CircularProgressBar *_extruderTemperatureBar;
    QMap<int, ExtruderWidget*> _extruderMap;

    Printer *_printer = nullptr;

    Ui::PrinterPage *ui;
    void setupUiClasses();
};

#endif // PRINTERPAGE_H
