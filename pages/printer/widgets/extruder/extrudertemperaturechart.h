#ifndef EXTRUDERTEMPERATURECHART_H
#define EXTRUDERTEMPERATURECHART_H

#include <QWidget>
#include <QLineSeries>
#include <QSplineSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QVBoxLayout>
#include <QTimer>
#include <QList>
#include <QDateTime>

#include <QKlipper/qklipper.h>

class ExtruderTemperatureChart : public QWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit ExtruderTemperatureChart(QKlipperExtruder *instance, QWidget *parent = nullptr);
        ~ExtruderTemperatureChart();
        void setStyleSheet(QString &styleSheet);

    signals:

    protected:
        void setupUi();
        void setupTimer();

    protected slots:
        void onUpdateTimerTimeout();

    private:
        QKlipperExtruder *m_instance = nullptr;
        qint64 m_updateTimerInterval = 500; //ms
        QChart *m_chart = nullptr;
        QChartView *m_view = nullptr;
        QDateTimeAxis *m_axisX = nullptr;
        QValueAxis *m_axisY = nullptr;
        QVBoxLayout *m_layout = nullptr;

        QMap<QString, QLineSeries*> m_series;

        QLineSeries *m_totalSeries = nullptr;
        QMap<QString, qreal> m_dataPoints;

        QTimer *m_updateTimer = nullptr;
};

#endif // EXTRUDERTEMPERATURECHART_H
