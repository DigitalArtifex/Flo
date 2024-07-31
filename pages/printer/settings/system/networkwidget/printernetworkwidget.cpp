#include "printernetworkwidget.h"

PrinterNetworkWidget::PrinterNetworkWidget(System *system, QWidget *parent)
    : CardWidget{CardWidget::SubWidget, parent}
{
    m_system = system;

    setupUi();
}

void PrinterNetworkWidget::setupUi()
{
    setTitle("Network");
    setFixedSize(380, 320);

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);

    m_networkChart = new PrinterNetworkChart(m_system, this);
    m_centralLayout->addWidget(m_networkChart);

    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
}
