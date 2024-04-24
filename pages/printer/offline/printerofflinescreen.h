#ifndef PRINTEROFFLINESCREEN_H
#define PRINTEROFFLINESCREEN_H

#include <QFrame>

namespace Ui {
class PrinterOfflineScreen;
}

class PrinterOfflineScreen : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterOfflineScreen(QWidget *parent = nullptr);
    ~PrinterOfflineScreen();

    virtual void setStyleSheet(QString &styleSheet);

private:
    Ui::PrinterOfflineScreen *ui;
};

#endif // PRINTEROFFLINESCREEN_H
