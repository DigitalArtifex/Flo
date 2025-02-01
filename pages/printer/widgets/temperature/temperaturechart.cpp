#include "temperaturechart.h"
#include "flo/settings.h"

PrinterTemperatureChart::PrinterTemperatureChart(QKlipperInstance *instance, QWidget *parent)
    : QWidget{parent}
{
    m_instance = instance;

    setupUi();

    connect(m_instance, SIGNAL(isConnectedChanged()), this, SLOT(onInstanceConnectedChanged()));
}

PrinterTemperatureChart::~PrinterTemperatureChart()
{
    // if(m_axisX)
    //     m_axisX->deleteLater();

    // if(m_axisY)
    //     m_axisY->deleteLater();

    // foreach(QString key, m_series.keys())
    //     m_series[key];

    // if(m_chart)
    //     m_chart->deleteLater();

    // if(m_view)
    //     m_view->deleteLater();

    // if(m_layout)
    //     m_layout->deleteLater();
}

void PrinterTemperatureChart::setupUi()
{
    m_chart = new QChart();
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->setMargins(QMargins(0,0,0,0));
    m_chart->setContentsMargins(QMargins(0,0,0,0));
    m_chart->legend()->setAlignment(Qt::AlignRight);
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-120);
    QDateTime rangeEnd = timestamp.addSecs(10);

    m_series["total"] = new QLineSeries(m_chart);
    m_series["total"]->setName("Total");

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
    m_axisY->setTickCount(4);
    m_axisY->setMinorTickCount(4);
    m_axisY->setTitleText("Temperature");
    m_axisY->setLabelFormat("%.2f C");
    m_axisY->setTitleVisible(false);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_chart->legend()->show();

    m_view = new QChartView(m_chart);
    m_view->setRenderHint(QPainter::Antialiasing, true);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(10,0,0,0);
    m_layout->addWidget(m_view);

    setLayout(m_layout);

    QFont font;
    font.setPointSize(9);

    m_axisX->setLabelsFont(font);
    m_axisY->setLabelsFont(font);

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
    m_view->setBackgroundBrush(backgroundGradient);
}

void PrinterTemperatureChart::onUpdateTimerTimeout()
{
    QDateTime timestamp = QDateTime::currentDateTime();

    QDateTime rangeStart = timestamp.addSecs(-120);
    QDateTime rangeEnd = timestamp.addSecs(10);
    qint64 msSinceEpoch = timestamp.toMSecsSinceEpoch();

    m_axisX->setRange(rangeStart, rangeEnd);

    //Update bed temps
    QString key = "Bed";
    qreal temperature = m_instance->printer()->bed()->currentTemp();

    if(m_axisY->max() <= temperature)
        m_axisY->setMax((temperature + (temperature * .1)));

    if(m_series.contains(key))
        m_series[key]->append(msSinceEpoch, temperature);
    else
    {
        m_series[key] = new QLineSeries(m_chart);

        m_series[key]->setName(key);
        m_chart->addSeries(m_series[key]);
        m_series[key]->attachAxis(m_axisY);
        m_series[key]->attachAxis(m_axisX);

        m_series[key]->append(msSinceEpoch, temperature);
    }

    for(int i = 0; i < m_series[key]->count(); i++)
    {
        if(m_series[key]->at(i).y() > rangeStart.toMSecsSinceEpoch())
        {
            m_series[key]->remove(i);
            --i;
        }
    }

    //Update chamber temps
    if(m_instance->printer()->hasChamber())
    {
        key = "Chamber";
        temperature = m_instance->printer()->chamber()->currentTemperature();

        if(m_axisY->max() <= temperature)
            m_axisY->setMax((temperature + (temperature * .1)));

        if(m_series.contains(key))
            m_series[key]->append(msSinceEpoch, temperature);
        else
        {
            m_series[key] = new QLineSeries(m_chart);

            m_series[key]->setName(key);
            m_chart->addSeries(m_series[key]);
            m_series[key]->attachAxis(m_axisY);
            m_series[key]->attachAxis(m_axisX);

            m_series[key]->append(msSinceEpoch, temperature);
        }
    }

    for(int i = 0; i < m_series[key]->count(); i++)
    {
        if(m_series[key]->at(i).y() > rangeStart.toMSecsSinceEpoch())
        {
            m_series[key]->remove(i);
            --i;
        }
    }

    //Update extruder temps
    for(QKlipperExtruder *extruder : m_instance->printer()->toolhead()->extruderMap())
    {
        key = extruder->name();
        temperature = extruder->currentTemp();

        if(m_axisY->max() <= temperature)
            m_axisY->setMax((temperature + (temperature * .1)));

        if(m_series.contains(key))
            m_series[key]->append(msSinceEpoch, temperature);
        else
        {
            m_series[key] = new QLineSeries(m_chart);

            m_series[key]->setName(key);
            m_chart->addSeries(m_series[key]);
            m_series[key]->attachAxis(m_axisY);
            m_series[key]->attachAxis(m_axisX);

            m_series[key]->append(msSinceEpoch, temperature);
        }
    }

    for(int i = 0; i < m_series[key]->count(); i++)
    {
        if(m_series[key]->at(i).y() > rangeStart.toMSecsSinceEpoch())
        {
            m_series[key]->remove(i);
            --i;
        }
    }
}

void PrinterTemperatureChart::onInstanceConnectedChanged()
{
    if(m_instance->isConnected())
    {
        if(!m_updateTimer)
        {
            m_updateTimer = new QTimer(this);

            connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateTimerTimeout()));

            m_updateTimer->setInterval(1000);
            m_updateTimer->start();
        }
    }
    else if(m_updateTimer)
    {
        m_updateTimer->stop();
        m_updateTimer->deleteLater();

        m_updateTimer = nullptr;
    }
}

void PrinterTemperatureChart::setStyleSheet(QString &styleSheet)
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

