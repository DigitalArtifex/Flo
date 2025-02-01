#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QFrame>

#include <QKlipper/qklipper.h>
#include <flo/qklipperinstancepool.h>

#include "widgets/printer/printerwidget.h"
#include "widgets/system/systemwidget.h"
#include "widgets/status/statuswidget.h"
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

    virtual void resizeEvent(QResizeEvent *event);

protected slots:
    //Printer Pool
    void onInstanceAdded(QKlipperInstance *instance);
    void onInstanceRemoved(QKlipperInstance *instance);

private:
    Ui::DashboardPage *ui;
    QList<PrinterWidget*> m_printerWidgets;
    PrinterWidget *m_selectedWidget = nullptr;
    SystemWidget *m_systemWidget = nullptr;
    StatusWidget *m_statusWidget = nullptr;
    QFlowLayout *m_layout = nullptr;
    QTimer *m_initTimer = nullptr;
    QHBoxLayout *m_topLayout = nullptr;
};

#endif // DASHBOARDPAGE_H
