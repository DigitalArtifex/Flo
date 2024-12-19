#include "extrudertemperaturewidget.h"

ExtruderTemperatureWidget::ExtruderTemperatureWidget(QKlipperExtruder *instance, QWidget *parent)
    : CardWidget{CardWidget::Widget, parent}
{
    m_instance = instance;

    setupUi();
}

void ExtruderTemperatureWidget::setupUi()
{
    setTitle("Thermals");

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralLayout->setContentsMargins(QMargins(0,0,0,0));
    setCardFlags(NoTitleBar);

    m_extruderChart = new ExtruderTemperatureChart(m_instance, this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralLayout->addWidget(m_extruderChart);

    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
}
