#ifndef LEDSTRIPVIEW_H
#define LEDSTRIPVIEW_H

#include <QObject>
#include <QWidget>
#include <QKlipper/qklipper.h>
#include <QScrollArea>
#include "ui/layouts/qflowlayout.h"
#include "ledstripcard.h"
#include "common/CardWidget/cardwidget.h"

class LedStripView : public CardWidget
{
        Q_OBJECT
    public:
        explicit LedStripView(QKlipperSystem *system, QWidget *parent = nullptr);

        QKlipperSystem *system() const;

    public slots:
        void setSystem(QKlipperSystem *system);
        void setStyleSheet(const QString &styleSheet);

    protected slots:
        void clear();
        void setupUi();
        void setupIcons();
        void onDeviceListChanged();

    private:
        QMap<QString, LedStripCard*> m_powerDevices;
        QKlipperSystem *m_system = nullptr;
        QFlowLayout *m_scrollAreaLayout = nullptr;
        QWidget *m_scrollAreaWidget = nullptr;
        QScrollArea *m_scrollArea = nullptr;
        QSpacerItem *m_spacer = nullptr;
};

#endif // LEDSTRIPVIEW_H
