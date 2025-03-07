#ifndef PRINTERNETWORKWIDGET_H
#define PRINTERNETWORKWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

#include <QKlipper/qklipper.h>
#include "common/CardWidget/cardwidget.h"
#include "ui/LineGraphWidget/linegraphwidget.h"

class PrinterNetworkWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterNetworkWidget(QKlipperSystem *system, QWidget *parent = nullptr);

    virtual void setStyleSheet(const QString &styleSheet);

signals:

protected slots:
    void systemNetworkUpdate();

protected:
    void setupUi();

private:
    LineGraphWidget *m_temperatureGraph = nullptr;

    QKlipperSystem *m_system = nullptr;
    QVBoxLayout *m_centralLayout = nullptr;
    QWidget *m_centralWidget = nullptr;
};

#endif // PRINTERNETWORKWIDGET_H
