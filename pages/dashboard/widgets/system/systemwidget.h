#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QMovie>

#include "../../../../types/printer.h"
#include "../../../../ui/circularprogressbar.h"
#include "../../../../ui/widgetanimation.h"

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

    Printer *m_printer = nullptr;

    CircularProgressBar *m_systemCpuLoadProgressBar;
    CircularProgressBar *m_systemMemoryLoadProgressBar;
    CircularProgressBar *m_systemTemperatureProgressBar;

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    WidgetAnimation *m_loadingAnimation = nullptr;
};

#endif // SYSTEMWIDGET_H
