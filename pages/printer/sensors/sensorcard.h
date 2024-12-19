#ifndef SENSORCARD_H
#define SENSORCARD_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>

#include <ui/common/cardwidget/cardwidget.h>

#include <QKlipper/qklipper.h>

#include <QLineSeries>
#include <QSplineSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QDateTimeAxis>

class SensorCard : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit SensorCard(QKlipperSensor *sensor, QWidget *parent = nullptr);

        virtual void setStyleSheet(const QString &styleSheet);

    signals:

    protected slots:
        void setupUi();
        void setupIcons();

    private:
        QKlipperSensor *m_sensor = nullptr;
        QIconButton *m_powerButton = nullptr;
        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;
};

#endif // SENSORCARD_H
