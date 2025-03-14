#include "energyconsumptionchart.h"
#include "flo/settings.h"

EnergyConsumptionChart::EnergyConsumptionChart(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
    setupTimer();
}

EnergyConsumptionChart::~EnergyConsumptionChart()
{
    if(m_axisX)
        m_axisX->deleteLater();

    if(m_axisY)
        m_axisY->deleteLater();

    foreach(QString key, m_series.keys())
        m_series[key]->deleteLater();

    if(m_chart)
        m_chart->deleteLater();

    if(m_view)
        m_view->deleteLater();

    if(m_layout)
        m_layout->deleteLater();
}

void EnergyConsumptionChart::trackPrinter(QKlipperInstance *printer)
{
    m_sources.append(printer);

    m_series[printer->id()] = new QLineSeries(m_chart);

    m_series[printer->id()]->setName(printer->name());
    m_chart->addSeries(m_series[printer->id()]);
    m_series[printer->id()]->attachAxis(m_axisY);
    m_series[printer->id()]->attachAxis(m_axisX);
}

void EnergyConsumptionChart::setupUi()
{
    m_chart = new QChart();
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->setTheme(QChart::ChartThemeDark);
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-180);
    QDateTime rangeEnd = timestamp.addSecs(10);

    m_series["total"] = new QLineSeries(m_chart);
    m_series["total"]->setName("Total");

    m_chart->addSeries(m_series["total"]);

    m_axisX = new QDateTimeAxis;
    m_axisX->setRange(rangeStart, rangeEnd);
    m_axisX->setTickCount(12);
    m_axisX->setFormat("hh:mm:ss");
    m_axisX->setTitleText("Time");
    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_series["total"]->attachAxis(m_axisX);

    m_axisY = new QValueAxis;
    m_axisY->setRange(0, 100);
    m_axisY->setTickCount(6);
    m_axisY->setTitleText("Energy");
    m_axisY->setLabelFormat("%dW");
    m_chart->addAxis(m_axisY, Qt::AlignLeft);
    m_series["total"]->attachAxis(m_axisY);

    m_chart->legend()->show();

    m_view = new QChartView(m_chart);
    m_view->setRenderHint(QPainter::Antialiasing, true);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->addWidget(m_view);

    setLayout(m_layout);

    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QColor(Settings::get("theme/graph-plot-background-start").toString()));
    plotAreaGradient.setColorAt(1.0, QColor(Settings::get("theme/graph-plot-background-end").toString()));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    m_chart->setPlotAreaBackgroundVisible(true);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QColor(Settings::get("theme/graph-background-start").toString()));
    backgroundGradient.setColorAt(1.0, QColor(Settings::get("theme/graph-background-end").toString()));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setBackgroundBrush(backgroundGradient);
}

void EnergyConsumptionChart::setupTimer()
{
    //call the timeout event for the initial reading
    //updateTimerTimeoutEvent();

    //check settings for update interval
    if(Settings::contains(QString("energy_tracker_update_interval")))
        m_updateTimerInterval = Settings::get(QString("energy_tracker_update_interval")).toLongLong();
    else
        Settings::set(QString("energy_tracker_update_interval"), m_updateTimerInterval);

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(m_updateTimerInterval);

    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateTimerTimeoutEvent()));
    m_updateTimer->start();
}

void EnergyConsumptionChart::updateTimerTimeoutEvent()
{
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-180);
    QDateTime rangeEnd = timestamp.addSecs(10);
    m_axisX->setRange(rangeStart, rangeEnd);

    qint64 x = timestamp.toMSecsSinceEpoch();
    qreal wattsTotal = 20;

    //qDebug() << "Power Update";

    foreach(QKlipperInstance *printer, m_sources)
    {
        QString key = printer->id();
        qreal power = printer->printer()->watts();
        wattsTotal += power;

        m_series[printer->id()]->append(x, qCeil(power));
    }

    m_series["total"]->append(x, wattsTotal);
}

void EnergyConsumptionChart::setStyleSheet(QString &styleSheet)
{
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QColor(Settings::get("theme/graph-plot-background-start").toString()));
    plotAreaGradient.setColorAt(1.0, QColor(Settings::get("theme/graph-plot-background-end").toString()));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    m_chart->setPlotAreaBackgroundVisible(true);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QColor(Settings::get("theme/graph-background-start").toString()));
    backgroundGradient.setColorAt(1.0, QColor(Settings::get("theme/graph-background-end").toString()));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setBackgroundBrush(backgroundGradient);

    QWidget::setStyleSheet(styleSheet);
}
