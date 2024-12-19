#include "printernetworkwidget.h"
#include "system/settings.h"

PrinterNetworkWidget::PrinterNetworkWidget(QKlipperSystem *system, QWidget *parent)
    : CardWidget{CardWidget::SubWidget, parent}
{
    m_system = system;

    setupUi();
}

void PrinterNetworkWidget::setStyleSheet(const QString &styleSheet)
{
    setIcon(Settings::getThemeIcon("network"));
    CardWidget::setStyleSheet(styleSheet);
}

void PrinterNetworkWidget::setupUi()
{
    setTitle("Network");

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralLayout->setContentsMargins(0,0,0,0);

    m_networkChart = new PrinterNetworkChart(m_system, this);
    m_centralLayout->addWidget(m_networkChart);

    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
    setIcon(Settings::getThemeIcon("network"));
}
