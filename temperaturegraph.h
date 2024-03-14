#ifndef TEMPERATUREGRAPH_H
#define TEMPERATUREGRAPH_H

#include <QFrame>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QLayout>
#include <QColor>
#include <QMap>
#include <QMapIterator>
#include <QQueue>
#include <QLineSeries>
#include <QDateTime>
#include <QTimer>
#include <QRandomGenerator>
#include <QStyle>

namespace Ui {
class TemperatureGraph;
}

class TemperatureGraph : public QFrame
{
    Q_OBJECT

public:
    explicit TemperatureGraph(QWidget *parent = nullptr);
    ~TemperatureGraph();

    void addTemperature(QString source, double temp, QString timecode = QDateTime::currentDateTime().toString());
    void updateStyleSheet();

private slots:
    void on_sampleUpdateTimeout();

private:
    Ui::TemperatureGraph *ui;

    //Temperature chart
    QChart *temperatureChart;
    QChartView *temperatureChartView;
    QValueAxis *axisY;
    QValueAxis *axisX;

    QLineSeries *extruderSeries;
    QLineSeries *bedSeries;

    double extruderTemp = 0;
    double bedTemp = 0;

    struct Source
    {
        QString name;
        QColor color;
        double temp;
        QLineSeries *series;
    };

    QList<Source*> temperatureSources;

    QTimer *sampleUpdateTimer;
    int sampleUpdateInterval;
    int sampleIndex;

    virtual void repaint();
};

#endif // TEMPERATUREGRAPH_H
