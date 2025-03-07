#ifndef TEMPERATUREWIDGET_H
#define TEMPERATUREWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

#include <QKlipper/qklipper.h>
#include "common/CardWidget/cardwidget.h"
#include "ui/LineGraphWidget/linegraphwidget.h"

class PrinterTemperatureWidget : public CardWidget
{
        Q_OBJECT
    public:
        explicit PrinterTemperatureWidget(QKlipperInstance *instance, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onExtruderCurrentTemperatureChanged();
        void onBedCurrentTemperatureChanged();
        void onInstanceConnected(QKlipperInstance *instance);
        void onInstanceDisconnected(QKlipperInstance *instance);

    protected:
        void setupUi();

    private:
        QKlipperInstance *m_instance = nullptr;
        QVBoxLayout *m_centralLayout = nullptr;
        QWidget *m_centralWidget = nullptr;

        LineGraphWidget *m_temperatureGraph = nullptr;
};

#endif // TEMPERATUREWIDGET_H
