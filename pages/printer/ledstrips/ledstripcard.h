#ifndef LEDSTRIPCARD_H
#define LEDSTRIPCARD_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QKlipper/qklipper.h>
#include "ui/common/cardwidget/cardwidget.h"
#include "ui/Switch/switch.h"
#include "ui/QIconButton/qiconbutton.h"

class LedStripCard : public CardWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit LedStripCard(QKlipperLedStrip *strip, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onSwitchChanged(bool toggled);
        void onLedIsOnChanged();
        void onLedErrorChanged();
        void onLedSpeedChanged();
        void onLedPresetChanged();
        void onLedBrightnessChanged();
        void onLedIntensityChanged();
        void onResetButtonPressed();
        void onApplyButtonPressed();
        void onValuesUpdated(int value);
        void setupUi();

    private:
        QKlipperLedStrip *m_ledStrip = nullptr;
        QIconButton *m_powerButton = nullptr;
        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;
        Switch *m_onSwitch = nullptr;
        QLabel *m_iconLabel = nullptr;
        QLabel *m_nameLabel = nullptr;
        QLabel *m_errorLabel = nullptr;
        QLabel *m_speedLabel = nullptr;
        QLabel *m_presetLabel = nullptr;
        QLabel *m_brightnessLabel = nullptr;
        QLabel *m_intensityLabel = nullptr;
        QLabel *m_chainCountLabel = nullptr;
        QSpinBox *m_speedSpinBox = nullptr;
        QSpinBox *m_brightnessSpinBox = nullptr;
        QSpinBox *m_presetSpinBox = nullptr;
        QSpinBox *m_intensitySpinBox = nullptr;
        QIconButton *m_resetButton = nullptr;
        QIconButton *m_applyButton = nullptr;
        bool m_commandBlock = false;
};

#endif // LEDSTRIPCARD_H
