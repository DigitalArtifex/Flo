#include "temperaturewidget.h"

PrinterTemperatureWidget::PrinterTemperatureWidget(QKlipperInstance *instance, QWidget *parent)
    : CardWidget{CardType::Widget, parent}
{
    m_instance = instance;

    setupUi();

    connect(m_instance, SIGNAL(connected(QKlipperInstance*)), this, SLOT(onInstanceConnected(QKlipperInstance*)));
    connect(m_instance, SIGNAL(disconnected(QKlipperInstance*)), this, SLOT(onInstanceDisconnected(QKlipperInstance*)));
}

void PrinterTemperatureWidget::onExtruderCurrentTemperatureChanged()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
    qreal timeDiff = m_temperatureGraph->dateMinimum().toSecsSinceEpoch() - timeNow;

     if(timeDiff <= 0)
         m_temperatureGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-30).addSecs(currentTime.offsetFromUtc()));

    for(QKlipperExtruder *extruder : m_instance->printer()->toolhead()->extruderMap())
    {
        m_temperatureGraph->data()->append(
            extruder->name(),
            QPointF(currentTime.toMSecsSinceEpoch(), extruder->currentTemp())
        );
    }
}

void PrinterTemperatureWidget::onBedCurrentTemperatureChanged()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
    qreal timeDiff = m_temperatureGraph->dateMinimum().toSecsSinceEpoch() - timeNow;

    if(timeDiff <= 0)
        m_temperatureGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-30).addSecs(currentTime.offsetFromUtc()));

    m_temperatureGraph->data()->append(
        "Bed",
        QPointF(currentTime.toMSecsSinceEpoch(), m_instance->printer()->bed()->currentTemp())
    );
}

void PrinterTemperatureWidget::onInstanceConnected(QKlipperInstance *instance)
{
    connect(m_instance->printer()->bed(), SIGNAL(currentTempChanged()), this, SLOT(onBedCurrentTemperatureChanged()));
    connect(m_instance->printer()->toolhead()->currentExtruder(), SIGNAL(currentTempChanged()), this, SLOT(onExtruderCurrentTemperatureChanged()));
}

void PrinterTemperatureWidget::onInstanceDisconnected(QKlipperInstance *instance)
{
    disconnect(m_instance->printer()->bed(), SIGNAL(currentTempChanged()), this, SLOT(onBedCurrentTemperatureChanged()));
    disconnect(m_instance->printer()->toolhead()->currentExtruder(), SIGNAL(currentTempChanged()), this, SLOT(onExtruderCurrentTemperatureChanged()));
}

void PrinterTemperatureWidget::setupUi()
{
    setTitle("Thermals");

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralLayout->setContentsMargins(QMargins(0,0,0,0));
    setCardFlags(NoTitleBar);

    QDateTime currentTime = QDateTime::currentDateTime();

    m_temperatureGraph = new LineGraphWidget(this);
    m_temperatureGraph->data()->setGridMainColor("#666666");
    m_temperatureGraph->data()->setGridSubColor("#444444");
    m_temperatureGraph->data()->setAxisYMainColor("#ccccff");
    m_temperatureGraph->data()->setAxisYSubColor("#eeeeff");
    m_temperatureGraph->data()->setAxisXMainColor("#ccccff");
    m_temperatureGraph->data()->setAxisXSubColor("#eeeeff");
    m_temperatureGraph->data()->setDateMinimum(QDateTime::currentDateTime().addSecs(0).addSecs(currentTime.offsetFromUtc()));
    m_temperatureGraph->data()->setDateMaximum(QDateTime::currentDateTime().addSecs(10).addSecs(currentTime.offsetFromUtc()));
    m_centralLayout->addWidget(m_temperatureGraph);

    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
}
