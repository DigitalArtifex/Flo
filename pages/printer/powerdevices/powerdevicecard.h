#ifndef POWERDEVICECARD_H
#define POWERDEVICECARD_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QLabel>
#include <ui/Switch/switch.h>
#include <QKlipper/qklipper.h>
#include <common/CardWidget/cardwidget.h>
#include <ui/QIconButton/qiconbutton.h>
#include <flo/settings.h>

class PowerDeviceCard : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit PowerDeviceCard(QKlipperPowerDevice *powerDevice, QWidget *parent);

        QKlipperPowerDevice *powerDevice() const;

    public slots:
        void setPowerDevice(QKlipperPowerDevice *powerDevice);
        void setStyleSheet(const QString &styleSheet);

    protected slots:
        void setupUi();
        void setupIcons();
        void onDeviceStateChanged();
        void onSwitchStateChanged(bool on);

        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);

    private:
        bool m_pressed = false;
        bool m_checked = false;
        bool m_checkable = false;
        bool m_exclusive = false;

        QKlipperPowerDevice *m_powerDevice = nullptr;
        QIconButton *m_powerButton = nullptr;
        QWidget *m_centralWidget = nullptr;
        QHBoxLayout *m_centralLayout = nullptr;
        Switch *m_onSwitch = nullptr;
        QLabel *m_iconLabel = nullptr;
        QLabel *m_textLabel = nullptr;
};

#endif // POWERDEVICECARD_H
