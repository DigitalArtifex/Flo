#ifndef PRINTERWIDGET_H
#define PRINTERWIDGET_H

#include <QFrame>
#include <QTimer>
#include <QLayoutItem>
#include <QMovie>
#include <QLabel>

#include "../../../../types/printer.h"
#include "../../../../ui/widgetanimation.h"
#include "../../../../ui/qanimatedwidget.h"

namespace Ui {
class PrinterWidget;
}

class PrinterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterWidget(QWidget *parent = nullptr);
    ~PrinterWidget();

    void setPrinter(Printer *printer);
    Printer *printer();

    void setUiClasses();

    virtual void setStyleSheet(QString styleSheet);
signals:
    void clicked(PrinterWidget *);
    void selected(PrinterWidget *);

private slots:
    void on_printer_update(Printer *printer);
    void on_printer_klipperDisconnected(Printer *printer);
    void on_printer_klipperConnected(Printer *printer);

    void on_quickActionButton_toggled(bool checked);
    void on_statusButton_clicked();
    void on_goBackButton_clicked();

    void on_pausePrintButton_toggled(bool checked);

    void on_restartKlipperButton_clicked();

    void on_loadingAnimation_finished();

    void on_restartFirmwareButton_clicked();

private:
    void showLoadingScreen();
    void hideLoadingScreen();

private:
    Ui::PrinterWidget *ui;
    Printer *m_printer = nullptr;
    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    WidgetAnimation *m_loadingAnimation = nullptr;
};

#endif // PRINTERWIDGET_H
