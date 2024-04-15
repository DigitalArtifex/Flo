#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QMovie>

#include "../../types/printer.h"
#include "../../ui/circularprogressbar.h"
#include "../../ui/widgetanimation.h"

namespace Ui {
class SystemWidget;
}

class SystemWidget : public QFrame
{
    Q_OBJECT

public:
    explicit SystemWidget(QWidget *parent = nullptr);
    ~SystemWidget();

    void setUiClasses();
    void setPrinter(Printer *printer);

    virtual void setStyleSheet(QString styleSheet);

private slots:
    void on_printer_systemUpdate(Printer *printer);
    void on_printer_klipperDisconnected(Printer *printer);
    void on_printer_klipperConnected(Printer *printer);

    void on_loadingAnimation_finished();

    //Private Functions
private:
    void convertBytes(qreal &bytes, QString &label);
    void convertDriveBytes(qreal &bytes, QString &label);
    void showLoadingScreen();
    void hideLoadingScreen();

private:
    Ui::SystemWidget *ui;

    Printer *_printer = nullptr;

    CircularProgressBar *_systemCpuLoadProgressBar;
    CircularProgressBar *_systemMemoryLoadProgressBar;
    CircularProgressBar *_systemTemperatureProgressBar;

    QMovie *_loadingGif = nullptr;
    QLabel *_loadingLabel = nullptr;

    WidgetAnimation *_loadingAnimation = nullptr;
};

#endif // SYSTEMWIDGET_H
