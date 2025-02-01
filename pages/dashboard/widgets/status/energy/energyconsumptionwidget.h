#ifndef ENERGYCONSUMPTIONWIDGET_H
#define ENERGYCONSUMPTIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include "energyconsumptionchart.h"

#include <QKlipper/qklipper.h>
#include <flo/qklipperinstancepool.h>

class EnergyConsumptionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnergyConsumptionWidget(QWidget *parent = nullptr);
    ~EnergyConsumptionWidget();

signals:

protected:
    void setupUi();

    void printerAddedEvent(QKlipperInstance *printer);

private:
    EnergyConsumptionChart *m_energyWidget = nullptr;

    QGridLayout *m_layout = nullptr;
};

#endif // ENERGYCONSUMPTIONWIDGET_H
