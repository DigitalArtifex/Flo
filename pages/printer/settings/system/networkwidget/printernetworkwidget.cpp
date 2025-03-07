#include "printernetworkwidget.h"
#include "flo/settings.h"

PrinterNetworkWidget::PrinterNetworkWidget(QKlipperSystem *system, QWidget *parent)
    : CardWidget{CardType::SubWidget, parent}
{
    m_system = system;

    setupUi();

    connect(m_system, SIGNAL(networkStatsChanged()), this, SLOT(systemNetworkUpdate()));
}

void PrinterNetworkWidget::setStyleSheet(const QString &styleSheet)
{
    setIcon(Settings::getThemeIcon("network"));
    CardWidget::setStyleSheet(styleSheet);
}

void PrinterNetworkWidget::systemNetworkUpdate()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
    qreal timeDiff = m_temperatureGraph->dateMinimum().toSecsSinceEpoch() - timeNow;

    if(timeDiff <= 0)
        m_temperatureGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-30).addSecs(currentTime.offsetFromUtc()));

    QStringList keys = m_system->networkStats().keys();

    for(const QString key : keys)
    {
        m_temperatureGraph->data()->append(
            key,
            QPointF(currentTime.toMSecsSinceEpoch(), (m_system->networkStats()[key].bandwidth() / 1000.00) / 1000)
        );
    }
}

void PrinterNetworkWidget::setupUi()
{
    setTitle("Network");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_centralWidget = new QWidget(this);

    m_centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralLayout->setContentsMargins(0,0,0,0);

    QDateTime currentTime = QDateTime::currentDateTime();

    m_temperatureGraph = new LineGraphWidget(this);
    m_temperatureGraph->data()->setGridMainColor("#666666");
    m_temperatureGraph->data()->setGridSubColor("#444444");
    m_temperatureGraph->data()->setAxisYMainColor("#ccccff");
    m_temperatureGraph->data()->setAxisYSubColor("#eeeeff");
    m_temperatureGraph->data()->setAxisXMainColor("#ccccff");
    m_temperatureGraph->data()->setAxisXSubColor("#eeeeff");
    m_temperatureGraph->setValueLabelFormat("%d MB");
    m_temperatureGraph->data()->setDateMinimum(QDateTime::currentDateTime().addSecs(0).addSecs(currentTime.offsetFromUtc()));
    m_temperatureGraph->data()->setDateMaximum(QDateTime::currentDateTime().addSecs(10).addSecs(currentTime.offsetFromUtc()));
    m_centralLayout->addWidget(m_temperatureGraph);

    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
    setIcon(Settings::getThemeIcon("network"));
}
