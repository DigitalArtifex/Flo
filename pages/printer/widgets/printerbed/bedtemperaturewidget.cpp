#include "bedtemperaturewidget.h"

BedTemperatureWidget::BedTemperatureWidget(QKlipperPrintBed *instance, QWidget *parent)
    : CardWidget{CardType::Widget, parent}
{
    m_instance = instance;

    setupUi();
}

void BedTemperatureWidget::setupUi()
{
    setTitle("Thermals");

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralLayout->setContentsMargins(QMargins(0,0,0,0));
    setCardFlags(NoTitleBar);

    m_bedChart = new BedTemperatureChart(m_instance, this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralLayout->addWidget(m_bedChart);

    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
}
