#ifndef PRINTERSERVICESVIEW_H
#define PRINTERSERVICESVIEW_H

#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QSizePolicy>

#include "servicewidget/printerservicewidget.h"

#include <QKlipper/qklipper.h>

#include "ui/layouts/qflowlayout.h"

class PrinterServicesView : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterServicesView(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterServicesView();

signals:

protected slots:
    void onSystemServiceStatesChanged();

private:
    QKlipperInstance *m_printer = nullptr;

    QWidget *m_centralWidget = nullptr;

    QFlowLayout *m_layout = nullptr;

    QMap<QString, PrinterServiceWidget*> m_serviceCards;
};

#endif // PRINTERSERVICESVIEW_H
