#ifndef PRINTERSERVICESVIEW_H
#define PRINTERSERVICESVIEW_H

#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QSizePolicy>

#include "servicewidget/printerservicewidget.h"
#include "systemwidget/printersystemwidget.h"
#include "drivewidget/printerdrivewidget.h"
#include "networkwidget/printernetworkwidget.h"

#include "types/printer.h"

class PrinterServicesView : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterServicesView(Printer *printer, QWidget *parent = nullptr);
    ~PrinterServicesView();

signals:

protected slots:
    void setupUi();
    void systemUpdateEvent();

private:
    Printer *m_printer = nullptr;

    QWidget *m_centralWidget = nullptr;

    QHBoxLayout *m_layout = nullptr;

    PrinterDriveWidget *m_driveWidget = nullptr;
    PrinterNetworkWidget *m_networkWidget = nullptr;
    PrinterSystemWidget *m_systemWidget = nullptr;

    QMap<QString, PrinterServiceWidget*> m_serviceCards;
};

#endif // PRINTERSERVICESVIEW_H
