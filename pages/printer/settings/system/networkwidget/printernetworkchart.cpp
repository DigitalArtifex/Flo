#include "printernetworkchart.h"

#include "system/settings.h"

PrinterNetworkChart::PrinterNetworkChart(System *system, QWidget *parent)
    : QWidget{parent}
{
    m_system = system;

    setupUi();

    connect(m_system, SIGNAL(networkStatsChanged()), this, SLOT(systemNetworkStatsChanged()));
}

PrinterNetworkChart::~PrinterNetworkChart()
{
    if(m_axisX)
        delete m_axisX;

    if(m_axisY)
        delete m_axisY;

    foreach(QString key, m_series.keys())
        delete m_series[key];

    if(m_chart)
        delete m_chart;

    if(m_view)
        delete m_view;

    if(m_layout)
        delete m_layout;
}

void PrinterNetworkChart::trackPrinter(Printer *printer)
{
}

void PrinterNetworkChart::setupUi()
{
    m_chart = new QChart();
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->setTheme(QChart::ChartThemeDark);
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-180);
    QDateTime rangeEnd = timestamp.addSecs(10);

    m_series["total"] = new QLineSeries(m_chart);
    m_series["total"]->setName("Total");

    //m_chart->addSeries(m_series["total"]);

    m_axisX = new QDateTimeAxis;
    m_axisX->setRange(rangeStart, rangeEnd);
    m_axisX->setTickCount(12);
    m_axisX->setFormat("hh:mm:ss");
    m_axisX->setTitleText("Time");
    m_axisX->setTitleVisible(false);
    m_axisX->setLabelsVisible(false);
    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    //m_series["total"]->attachAxis(m_axisX);

    m_axisY = new QValueAxis;
    m_axisY->setRange(0, 1);
    m_axisY->setTickCount(6);
    m_axisY->setTitleText("Bytes");
    m_axisY->setLabelFormat("%.2f MB");
    m_axisY->setTitleVisible(false);
    //m_axisY->setLabelsVisible(false);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);
    //m_series["total"]->attachAxis(m_axisY);

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
    plotAreaGradient.setColorAt(0.0, QColor(Settings::get("theme-graph-plot-background-start").toString()));
    plotAreaGradient.setColorAt(1.0, QColor(Settings::get("theme-graph-plot-background-end").toString()));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    m_chart->setPlotAreaBackgroundVisible(true);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QColor(Settings::get("theme-graph-background-start").toString()));
    backgroundGradient.setColorAt(1.0, QColor(Settings::get("theme-graph-background-end").toString()));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setBackgroundBrush(backgroundGradient);
}

void PrinterNetworkChart::updateTimerTimeoutEvent()
{
    delete m_updateTimer;
    m_updateTimer = nullptr;

    m_system->updateProcStats();
}

void PrinterNetworkChart::systemNetworkStatsChanged()
{
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-30);
    QDateTime rangeEnd = timestamp.addSecs(10);
    qint64 x = timestamp.toMSecsSinceEpoch();

    m_axisX->setRange(rangeStart, rangeEnd);

    QMap<QString, System::NetworkStatsEntry> stats = m_system->networkStats();
    QStringList statsKeys = stats.keys();

    foreach(QString key, statsKeys)
    {
        qreal bandwidth = ((stats[key].bandwidth / 1024) / 1024);

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

    if(!m_updateTimer)
    {
        m_updateTimer = new QTimer(this);
        m_updateTimer->setInterval(m_updateTimerInterval);

        connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateTimerTimeoutEvent()));
        m_updateTimer->setSingleShot(true);
        m_updateTimer->start();
    }
}

void PrinterNetworkChart::setStyleSheet(QString &styleSheet)
{
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QColor(Settings::get("theme-graph-plot-background-start").toString()));
    plotAreaGradient.setColorAt(1.0, QColor(Settings::get("theme-graph-plot-background-end").toString()));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    m_chart->setPlotAreaBackgroundVisible(true);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QColor(Settings::get("theme-graph-background-start").toString()));
    backgroundGradient.setColorAt(1.0, QColor(Settings::get("theme-graph-background-end").toString()));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setBackgroundBrush(backgroundGradient);

    QWidget::setStyleSheet(styleSheet);
}
