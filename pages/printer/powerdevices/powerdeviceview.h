#ifndef POWERDEVICEVIEW_H
#define POWERDEVICEVIEW_H

#include <QObject>
#include <QScrollArea>
#include <QKlipper/qklipper.h>
#include "ui/common/cardwidget/cardwidget.h"
#include "powerdevicecard.h"

class PowerDeviceView : public CardWidget
{
        Q_OBJECT
    public:
        explicit PowerDeviceView(QKlipperSystem *system, QWidget *parent);

        QKlipperSystem *system() const;

    public slots:
        void setSystem(QKlipperSystem *system);
        void setStyleSheet(const QString &styleSheet);

    protected slots:
        void clear();
        void setupUi();
        void setIcons();
        void onDeviceListChanged();

    private:
        QMap<QString, PowerDeviceCard*> m_powerDevices;
        QKlipperSystem *m_system = nullptr;
        QHBoxLayout *m_scrollAreaLayout = nullptr;
        QWidget *m_scrollAreaWidget = nullptr;
        QScrollArea *m_scrollArea = nullptr;
        QSpacerItem *m_spacer = nullptr;
};

#endif // POWERDEVICEVIEW_H
