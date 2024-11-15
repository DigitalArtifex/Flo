#ifndef PRINTERWIDGET_H
#define PRINTERWIDGET_H

#include <QFrame>
#include <QTimer>
#include <QLayoutItem>
#include <QMovie>
#include <QLabel>

#include <QKlipper/qklipper.h>

#include "ui/widgetanimation.h"
#include "ui/qanimatedwidget.h"
#include "ui/QIconButton/qiconbutton.h"

namespace Ui {
class PrinterWidget;
}

class PrinterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterWidget(QWidget *parent = nullptr);
    ~PrinterWidget();

    void setPrinter(QKlipperInstance *printer);
    QKlipperInstance *printer();

    void setUiClasses();

    virtual void setStyleSheet(QString styleSheet);
signals:
    void clicked(PrinterWidget *);
    void selected(PrinterWidget *);

private slots:
    void on_printer_klipperDisconnected(QKlipperInstance *printer);
    void on_printer_klipperConnected(QKlipperInstance *printer);

    void on_quickActionButton_toggled(bool checked);
    void on_statusButton_clicked();
    void on_goBackButton_clicked();

    void on_pausePrintButton_toggled(bool checked);

    void on_restartKlipperButton_clicked();

    void on_loadingAnimation_finished();

    void on_restartFirmwareButton_clicked();

    void onPrinterStatusChanged();
    void onInstanceNameChanged();
    void onPrinterPrintEndingChanged();

private:
    void showLoadingScreen();
    void hideLoadingScreen();

private:
    Ui::PrinterWidget *ui;
    QKlipperInstance *m_instance = nullptr;
    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    WidgetAnimation *m_loadingAnimation = nullptr;

    QIconButton *m_pausePrintButton = nullptr;
    QIconButton *m_cancelPrintButton = nullptr;
    QIconButton *m_restartFirmwareButton = nullptr;
    QIconButton *m_restartKlipperButton = nullptr;
};

#endif // PRINTERWIDGET_H
