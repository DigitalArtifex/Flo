#ifndef TEMPERATUREWIDGET_H
#define TEMPERATUREWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

#include <QKlipper/qklipper.h>
#include "ui/common/cardwidget/cardwidget.h"
#include "temperaturechart.h"

class PrinterTemperatureWidget : public CardWidget
{
        Q_OBJECT
    public:
        explicit PrinterTemperatureWidget(QKlipperInstance *instance, QWidget *parent = nullptr);

    signals:

    protected:
        void setupUi();

    private:
        QKlipperInstance *m_instance = nullptr;
        QVBoxLayout *m_centralLayout = nullptr;
        QWidget *m_centralWidget = nullptr;

        PrinterTemperatureChart *m_networkChart = nullptr;
};

#endif // TEMPERATUREWIDGET_H
