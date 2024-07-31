#ifndef PRINTERNETWORKWIDGET_H
#define PRINTERNETWORKWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

#include "types/system.h"
#include "ui/common/cardwidget/cardwidget.h"
#include "printernetworkchart.h"

class PrinterNetworkWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterNetworkWidget(System *system, QWidget *parent = nullptr);

signals:

protected:
    void setupUi();

private:
    System *m_system = nullptr;
    QVBoxLayout *m_centralLayout = nullptr;
    QWidget *m_centralWidget = nullptr;

    PrinterNetworkChart *m_networkChart = nullptr;
};

#endif // PRINTERNETWORKWIDGET_H
