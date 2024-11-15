#ifndef PRINTERNETWORKCHART_H
#define PRINTERNETWORKCHART_H

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

class PrinterNetworkChart : public QWidget
{
    Q_OBJECT
public:
    explicit PrinterNetworkChart(QKlipperSystem *system, QWidget *parent = nullptr);
    ~PrinterNetworkChart();

signals:

protected:
    void setupUi();
    void setupTimer();

protected slots:
    void systemNetworkStatsChanged();
    virtual void setStyleSheet(QString &styleSheet);

private:
    QKlipperSystem *m_system = nullptr;
    qint64 m_updateTimerInterval = 500; //ms
    QChart *m_chart = nullptr;
    QChartView *m_view = nullptr;
    QDateTimeAxis *m_axisX = nullptr;
    QValueAxis *m_axisY = nullptr;
    QVBoxLayout *m_layout = nullptr;

    QMap<QString, QLineSeries*> m_series;

    QLineSeries *m_totalSeries = nullptr;
};

#endif // PRINTERNETWORKCHART_H
