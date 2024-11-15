#ifndef TEMPERATURECHART_H
#define TEMPERATURECHART_H

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

class PrinterTemperatureChart : public QWidget
{
        Q_OBJECT
    public:
        explicit PrinterTemperatureChart(QKlipperInstance *instance, QWidget *parent = nullptr);
        ~PrinterTemperatureChart();

    signals:

    protected:
        void setupUi();
        void setupTimer();

    protected slots:
        void onUpdateTimerTimeout();
        void onInstanceConnectedChanged();
        virtual void setStyleSheet(QString &styleSheet);

    private:
        QKlipperInstance *m_instance = nullptr;
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

#endif // TEMPERATURECHART_H
