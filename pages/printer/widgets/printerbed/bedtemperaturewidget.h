#ifndef BEDTEMPERATUREWIDGET_H
#define BEDTEMPERATUREWIDGET_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QSpacerItem>
#include <QLabel>

#include <QKlipper/qklipper.h>
#include "ui/common/cardwidget/cardwidget.h"
#include "bedtemperaturechart.h"

class BedTemperatureWidget : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit BedTemperatureWidget(QKlipperPrintBed *instance, QWidget *parent = nullptr);

    signals:

    protected:
        void setupUi();

    private:
        QKlipperPrintBed *m_instance = nullptr;
        QVBoxLayout *m_centralLayout = nullptr;
        QWidget *m_centralWidget = nullptr;

        BedTemperatureChart *m_bedChart = nullptr;
};

#endif // BEDTEMPERATUREWIDGET_H
