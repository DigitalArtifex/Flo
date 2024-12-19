#ifndef EXTRUDERTEMPERATUREWIDGET_H
#define EXTRUDERTEMPERATUREWIDGET_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QSpacerItem>
#include <QLabel>

#include <QKlipper/qklipper.h>
#include "ui/common/cardwidget/cardwidget.h"
#include "extrudertemperaturechart.h"

class ExtruderTemperatureWidget : public CardWidget
{
        Q_OBJECT
    public:
        explicit ExtruderTemperatureWidget(QKlipperExtruder *instance, QWidget *parent = nullptr);

    signals:

    protected:
        void setupUi();

    private:
        QKlipperExtruder *m_instance = nullptr;
        QVBoxLayout *m_centralLayout = nullptr;
        QWidget *m_centralWidget = nullptr;

        ExtruderTemperatureChart *m_extruderChart = nullptr;
};

#endif // EXTRUDERTEMPERATUREWIDGET_H
