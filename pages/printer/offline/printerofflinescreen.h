#ifndef PRINTEROFFLINESCREEN_H
#define PRINTEROFFLINESCREEN_H

#include <QFrame>
#include <QKlipper/qklipper.h>
#include "ui/QIconButton/qiconbutton.h"

namespace Ui {
class PrinterOfflineScreen;
}

class PrinterOfflineScreen : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterOfflineScreen(QKlipperInstance *printer, QWidget *parent = nullptr);
    ~PrinterOfflineScreen();

    virtual void setStyleSheet(QString &styleSheet);

protected slots:
    void printerConnectingEvent();
    void printerConnectingProgressChanged();
    void printerConnectingTextChanged();
    void onConnectPrinterButtonPressed();

private:
    Ui::PrinterOfflineScreen *ui;

    QIconButton *m_connectButton = nullptr;
    QKlipperInstance *m_instance = nullptr;
};

#endif // PRINTEROFFLINESCREEN_H
