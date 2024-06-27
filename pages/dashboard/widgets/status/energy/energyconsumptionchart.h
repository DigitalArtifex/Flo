#ifndef ENERGYCONSUMPTIONCHART_H
#define ENERGYCONSUMPTIONCHART_H

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

#include "../../../../../types/printer.h"

class EnergyConsumptionChart : public QWidget
{
    Q_OBJECT
public:
    explicit EnergyConsumptionChart(QWidget *parent = nullptr);
    ~EnergyConsumptionChart();

    void trackPrinter(Printer *printer);

signals:

protected:
    void setupUi();
    void setupTimer();

protected slots:
    void updateTimerTimeoutEvent();
    virtual void setStyleSheet(QString &styleSheet);

private:
    QTimer *m_updateTimer = nullptr;
    qint64 m_updateTimerInterval = 500; //ms
    QChart *m_chart = nullptr;
    QChartView *m_view = nullptr;
    QDateTimeAxis *m_axisX = nullptr;
    QValueAxis *m_axisY = nullptr;
    QVBoxLayout *m_layout = nullptr;

    QList<Printer*> m_sources;
    QMap<QString, QLineSeries*> m_series;

    QLineSeries *m_totalSeries = nullptr;
};

#endif // ENERGYCONSUMPTIONCHART_H
