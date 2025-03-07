#include "energyconsumptionwidget.h"

EnergyConsumptionWidget::EnergyConsumptionWidget(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
}

EnergyConsumptionWidget::~EnergyConsumptionWidget()
{
    // if(m_energyWidget)
    //     m_energyWidget->deleteLater();

    if(m_layout)
        m_layout->deleteLater();
}

void EnergyConsumptionWidget::setupUi()
{
    // m_energyWidget = new EnergyConsumptionChart(this);

    // foreach(QKlipperInstance *key, QKlipperInstancePool::klipperInstances())
    //     m_energyWidget->trackPrinter(key);

    m_layout = new QGridLayout(this);
    // m_layout->setContentsMargins(0,0,0,0);
    // m_layout->addWidget(m_energyWidget);

    setLayout(m_layout);
}

void EnergyConsumptionWidget::printerAddedEvent(QKlipperInstance *printer)
{
    // if(m_energyWidget)
    //     m_energyWidget->trackPrinter(printer);
}
