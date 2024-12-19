#include "temperaturewidget.h"

PrinterTemperatureWidget::PrinterTemperatureWidget(QKlipperInstance *instance, QWidget *parent)
    : CardWidget{CardWidget::Widget, parent}
{
    m_instance = instance;

    setupUi();
}

void PrinterTemperatureWidget::setupUi()
{
    setTitle("Thermals");

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralLayout->setContentsMargins(QMargins(0,0,0,0));
    setCardFlags(NoTitleBar);

    m_networkChart = new PrinterTemperatureChart(m_instance, this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralLayout->addWidget(m_networkChart);

    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
}
