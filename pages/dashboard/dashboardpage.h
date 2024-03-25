#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QFrame>

#include "../../types/printer.h"
#include "../../widgets/printer/printerwidget.h"
#include "../../widgets/system/systemwidget.h"
#include "../../widgets/job/printjobwidget.h"
#include "../../ui/layouts/qflowlayout.h"

namespace Ui {
class DashboardPage;
}

class DashboardPage : public QFrame
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget *parent = nullptr);
    ~DashboardPage();
    void loadPrinters();
    void setUiClasses();

    void updateStyleSheet(QString stylesheet);

    virtual void setStyleSheet(QString styleSheet);

private slots:
    void on_console_response(Printer *printer, KlipperResponse);
    void on_printer_update(Printer *printer);
    void on_printer_systemUpdate(Printer *printer);

    //Printer Pool
    void on_printerPool_printerRemoved(Printer *printer);
    void on_printerPool_printerAdded(Printer *printer);
    void on_printerPool_printerUpdated(Printer *printer);

private:
    Ui::DashboardPage *ui;
    QList<PrinterWidget*> _printerWidgets;
    PrinterWidget *_selectedWidget = nullptr;
    SystemWidget *_systemWidget = nullptr;
    PrintJobWidget *_printJobWidget = nullptr;
    QFlowLayout *_layout = nullptr;
};

#endif // DASHBOARDPAGE_H
