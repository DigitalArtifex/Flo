#ifndef PRINTERSERVICESVIEW_H
#define PRINTERSERVICESVIEW_H

#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QSizePolicy>

#include "servicewidget/printerservicewidget.h"

#include "types/printer.h"

#include "ui/layouts/qflowlayout.h"

class PrinterServicesView : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterServicesView(Printer *printer, QWidget *parent = nullptr);
    ~PrinterServicesView();

signals:

protected slots:
    void systemUpdateEvent();

private:
    Printer *m_printer = nullptr;

    QWidget *m_centralWidget = nullptr;

    QFlowLayout *m_layout = nullptr;

    QMap<QString, PrinterServiceWidget*> m_serviceCards;
};

#endif // PRINTERSERVICESVIEW_H
