#ifndef PRINTERFANWIDGET_H
#define PRINTERFANWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <ui/common/cardwidget/cardwidget.h>
#include <QKlipper/qklipper.h>

#include "printerfanitem.h"

class PrinterFanWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterFanWidget(QKlipperPrinter *printer, QWidget *parent = nullptr);

public slots:
    void onPrinterFansChanged();
    void setPrinter(QKlipperPrinter *printer);

protected:
    void setupUi();
    void setupIcons();
    void clearLayout();
    virtual void changeEvent(QEvent *event) override;

private:
    QKlipperPrinter *m_printer = nullptr;

    QWidget *m_centralWidget = nullptr;
    QVBoxLayout *m_centralLayout = nullptr;
};

#endif // PRINTERFANWIDGET_H
