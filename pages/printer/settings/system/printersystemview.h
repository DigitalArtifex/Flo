#ifndef PRINTERSYSTEMVIEW_H
#define PRINTERSYSTEMVIEW_H

#include <QWidget>

#include "systemwidget/printersystemwidget.h"
#include "drivewidget/printerdrivewidget.h"
#include "networkwidget/printernetworkwidget.h"

class PrinterSystemView : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterSystemView(Printer *printer, QWidget *parent = nullptr);
    ~PrinterSystemView();

signals:

protected slots:
    void setupUi();

private:
    Printer *m_printer = nullptr;

    QWidget *m_centralWidget = nullptr;

    QHBoxLayout *m_layout = nullptr;

    PrinterDriveWidget *m_driveWidget = nullptr;
    PrinterNetworkWidget *m_networkWidget = nullptr;
    PrinterSystemWidget *m_systemWidget = nullptr;
};

#endif // PRINTERSYSTEMVIEW_H
