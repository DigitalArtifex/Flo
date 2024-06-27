#include "energyconsumptionwidget.h"

EnergyConsumptionWidget::EnergyConsumptionWidget(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
}

EnergyConsumptionWidget::~EnergyConsumptionWidget()
{
    if(m_energyWidget)
        delete m_energyWidget;

    if(m_layout)
        delete m_layout;
}

void EnergyConsumptionWidget::setupUi()
{
    m_energyWidget = new EnergyConsumptionChart(this);

    foreach(QString key, PrinterPool::keys())
        m_energyWidget->trackPrinter(PrinterPool::getPrinterById(key));

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->addWidget(m_energyWidget);

    setLayout(m_layout);
}

void EnergyConsumptionWidget::printerAddedEvent(Printer *printer)
{
    if(m_energyWidget)
        m_energyWidget->trackPrinter(printer);
}
