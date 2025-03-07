#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QMap>
#include <QScrollArea>
#include <ui/layouts/qflowlayout.h>
#include <common/CardWidget/cardwidget.h>
#include <QKlipper/qklipper.h>


#include "sensorcard.h"

class SensorView : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit SensorView(QKlipperSystem *system, QWidget *parent = nullptr);

        QKlipperSystem *system() const;

    public slots:
        void setSystem(QKlipperSystem *system);
        void setStyleSheet(const QString &styleSheet);
        virtual void reset();

    protected slots:
        void clear();
        void setupUi();
        void setupIcons();
        void onDeviceListChanged();

    private:
        QMap<QString, SensorCard*> m_sensors;
        QKlipperSystem *m_system = nullptr;
        QFlowLayout *m_scrollAreaLayout = nullptr;
        QWidget *m_scrollAreaWidget = nullptr;
        QScrollArea *m_scrollArea = nullptr;
        QSpacerItem *m_spacer = nullptr;
};

#endif // SENSORVIEW_H
