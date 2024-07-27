#ifndef PRINTEROFFLINESCREEN_H
#define PRINTEROFFLINESCREEN_H

#include <QFrame>
#include "types/printer.h"
#include "ui/QIconButton/qiconbutton.h"

namespace Ui {
class PrinterOfflineScreen;
}

class PrinterOfflineScreen : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterOfflineScreen(Printer *printer, QWidget *parent = nullptr);
    ~PrinterOfflineScreen();

    virtual void setStyleSheet(QString &styleSheet);

protected slots:
    void printerConnectingEvent();
    void printerConnectingProgressEvent(QString title, qreal progress);

private:
    Ui::PrinterOfflineScreen *ui;

    QIconButton *m_connectButton = nullptr;
};

#endif // PRINTEROFFLINESCREEN_H
