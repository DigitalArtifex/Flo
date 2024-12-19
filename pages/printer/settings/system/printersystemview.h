#ifndef PRINTERSYSTEMVIEW_H
#define PRINTERSYSTEMVIEW_H

#include <QWidget>
#include <QKlipper/qklipper.h>
#include "systemwidget/printersystemwidget.h"
#include "drivewidget/printerdrivewidget.h"
#include "networkwidget/printernetworkwidget.h"

class PrinterSystemView : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterSystemView(QKlipperInstance *printer, QWidget *parent = nullptr);
    ~PrinterSystemView();

public slots:
    void setStyleSheet(const QString &styleSheet);

signals:

protected slots:
    void setupUi();

private:
    QKlipperInstance *m_instance = nullptr;

    QWidget *m_centralWidget = nullptr;

    QHBoxLayout *m_layout = nullptr;

    PrinterDriveWidget *m_driveWidget = nullptr;
    PrinterNetworkWidget *m_networkWidget = nullptr;
    PrinterSystemWidget *m_systemWidget = nullptr;
};

#endif // PRINTERSYSTEMVIEW_H
