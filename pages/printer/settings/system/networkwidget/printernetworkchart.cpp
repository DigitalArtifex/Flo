#include "printernetworkchart.h"

#include "system/settings.h"

PrinterNetworkChart::PrinterNetworkChart(QKlipperSystem *system, QWidget *parent)
    : QWidget{parent}
{
    m_system = system;

    setupUi();

    connect(m_system, SIGNAL(networkStatsChanged()), this, SLOT(systemNetworkStatsChanged()));
}

PrinterNetworkChart::~PrinterNetworkChart()
{
    if(m_layout)
        m_layout->deleteLater();
}

void PrinterNetworkChart::setupUi()
{
    m_chart = new QChart();
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->setTheme(QChart::ChartThemeDark);
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-60);
    QDateTime rangeEnd = timestamp.addSecs(10);

    m_axisX = new QDateTimeAxis;
    m_axisX->setRange(rangeStart, rangeEnd);
    m_axisX->setTickCount(12);
    m_axisX->setFormat("hh:mm:ss");
    m_axisX->setTitleText("Time");
    m_axisX->setTitleVisible(false);
    m_axisX->setLabelsVisible(false);
    m_chart->addAxis(m_axisX, Qt::AlignBottom);

    m_axisY = new QValueAxis;
    m_axisY->setRange(0, 1);
    m_axisY->setTickCount(6);
    m_axisY->setTitleText("Bytes");
    m_axisY->setLabelFormat("%.2f MB");
    m_axisY->setTitleVisible(false);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_chart->legend()->show();
    m_chart->legend()->setAlignment(Qt::AlignRight);

    m_view = new QChartView(m_chart);
    m_view->setRenderHint(QPainter::Antialiasing, true);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->addWidget(m_view);

    setLayout(m_layout);

    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QColor(Settings::get("theme/widget-background-color").toString()));
    plotAreaGradient.setColorAt(1.0, QColor(Settings::get("theme/widget-background-color").toString()));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    m_chart->setPlotAreaBackgroundVisible(true);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QColor(Settings::get("theme/subwidget-background-color").toString()));
    backgroundGradient.setColorAt(1.0, QColor(Settings::get("theme/subwidget-background-color").toString()));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setBackgroundBrush(backgroundGradient);
    m_view->setBackgroundBrush(backgroundGradient);
}

void PrinterNetworkChart::systemNetworkStatsChanged()
{
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-60);
    QDateTime rangeEnd = timestamp.addSecs(10);
    qint64 x = timestamp.toMSecsSinceEpoch();

    m_axisX->setRange(rangeStart, rangeEnd);

    QMap<QString, QKlipperNetworkStatsEntry> stats = m_system->networkStats();
    QStringList statsKeys = stats.keys();

    foreach(QString key, statsKeys)
    {
        qreal bandwidth = ((stats[key].bandwidth() / 1024) / 1024);

        if(m_axisY->max() <= bandwidth)
            m_axisY->setMax((bandwidth + (bandwidth * .1)));

        if(m_series.contains(key))
            m_series[key]->append(timestamp.toMSecsSinceEpoch(), bandwidth);
        else
        {
            m_series[key] = new QLineSeries(m_chart);

            m_series[key]->setName(key);
            m_chart->addSeries(m_series[key]);
            m_series[key]->attachAxis(m_axisY);
            m_series[key]->attachAxis(m_axisX);

            m_series[key]->append(timestamp.toMSecsSinceEpoch(), bandwidth);
        }
    }

    if(Settings::contains(QString("energy_tracker_update_interval")))
        m_updateTimerInterval = Settings::get(QString("energy_tracker_update_interval")).toLongLong();
    else
        Settings::set(QString("energy_tracker_update_interval"), m_updateTimerInterval);
}

void PrinterNetworkChart::setStyleSheet(QString &styleSheet)
{
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QColor(Settings::get("theme/widget-background-color").toString()));
    plotAreaGradient.setColorAt(1.0, QColor(Settings::get("theme/widget-background-color").toString()));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    m_chart->setPlotAreaBackgroundVisible(true);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QColor(Settings::get("theme/subwidget-background-color").toString()));
    backgroundGradient.setColorAt(1.0, QColor(Settings::get("theme/subwidget-background-color").toString()));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setBackgroundBrush(backgroundGradient);
    m_view->setBackgroundBrush(backgroundGradient);

    QWidget::setStyleSheet(styleSheet);
}
