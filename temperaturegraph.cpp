#include "temperaturegraph.h"
#include "ui_temperaturegraph.h"
#include "settings.h"

TemperatureGraph::TemperatureGraph(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TemperatureGraph)
{
    sampleIndex= 0;
    ui->setupUi(this);


    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "TemperatureView"));

    temperatureChart = new QChart();
    temperatureChart->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "TemperatureChart"));
    temperatureChart->setAnimationDuration(250);
    temperatureChart->setDropShadowEnabled();
    temperatureChart->setTheme(QChart::ChartThemeBlueCerulean);
    temperatureChart->setAnimationOptions(QChart::SeriesAnimations);
    temperatureChartView = new QChartView(temperatureChart);
    temperatureChartView->setRenderHint(QPainter::Antialiasing);
    //temperatureChartView->setBackgroundBrush(QBrush(Qt::transparent));
    this->layout()->addWidget(temperatureChartView);

    extruderSeries = new QLineSeries();
    extruderSeries->setName("Extruder");
    bedSeries = new QLineSeries();
    bedSeries->setName("Bed Heater");

    QStringList categories;
    axisX = new QValueAxis();
    temperatureChart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0, 30);

    axisY = new QValueAxis();
    temperatureChart->addAxis(axisY, Qt::AlignLeft);
    axisY->setRange(0, 50);

    sampleUpdateInterval = 1000;
    sampleUpdateTimer = new QTimer();
    sampleUpdateTimer->setInterval(sampleUpdateInterval);
    connect(sampleUpdateTimer, SIGNAL(timeout()), this, SLOT(on_sampleUpdateTimeout()));
    sampleUpdateTimer->start();
}

TemperatureGraph::~TemperatureGraph()
{
    delete ui;
}

void TemperatureGraph::addTemperature(QString source, double temp, QString timecode)
{
    bool found = false;

    for(int i = 0; i < temperatureSources.count(); i++)
    {
        if(temperatureSources[i]->name == source)
        {
            temperatureSources[i]->temp = temp;
            found = true;
            break;
        }
    }

    if(!found)
    {
        Source *newSource = new Source();
        newSource->series = new QLineSeries();
        newSource->temp = temp;
        newSource->series->setName(source);
        newSource->name = source;

        if(sampleIndex > 0)
        {
            for (int i = 0; i < sampleIndex - 1; i++) {
                QPointF p((qreal) i, 0);
                newSource->series->append(p);
            }

        }

        temperatureChart->addSeries(newSource->series);
        newSource->series->attachAxis(axisX);
        newSource->series->attachAxis(axisY);
        newSource->series->append(QPoint(sampleIndex, temp));
        temperatureSources.append(newSource);
    }
}

void TemperatureGraph::updateStyleSheet()
{
    temperatureChart->setBackgroundBrush(QBrush(QColor::fromString(Settings::get("color_Graph").toString())));
}

void TemperatureGraph::on_sampleUpdateTimeout()
{
    if(sampleIndex > 30)
    {
        axisX->setRange((sampleIndex - 30), sampleIndex);
    }

    for(int i = 0; i < temperatureSources.count(); i++)
    {
        QPoint sample(sampleIndex, temperatureSources[i]->temp);
        temperatureSources[i]->series->append(sample);

        if(sample.y() >= axisY->max())
            axisY->setRange(0, sample.y() + 10);
    }

    sampleIndex++;
}

void TemperatureGraph::repaint()
{
    this->style()->polish(this);
    QFrame::repaint();
}

