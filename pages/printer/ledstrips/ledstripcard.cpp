#include "ledstripcard.h"
#include "system/settings.h"

LedStripCard::LedStripCard(QKlipperLedStrip *strip, QWidget *parent)
    : CardWidget{CardWidget::SubWidget,parent}
{
    m_ledStrip = strip;

    setupUi();

    connect(m_ledStrip, SIGNAL(brightnessChanged()), this, SLOT(onLedBrightnessChanged()));
    connect(m_ledStrip, SIGNAL(errorChanged()), this, SLOT(onLedErrorChanged()));
    connect(m_ledStrip, SIGNAL(intensityChanged()), this, SLOT(onLedIntensityChanged()));
    connect(m_ledStrip, SIGNAL(presetChanged()), this, SLOT(onLedPresetChanged()));
    connect(m_ledStrip, SIGNAL(speedChanged()), this, SLOT(onLedSpeedChanged()));

    connect(m_onSwitch, SIGNAL(toggled(bool)), this, SLOT(onSwitchChanged(bool)));
    connect(m_brightnessSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onValuesUpdated(int)));
    connect(m_speedSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onValuesUpdated(int)));
    connect(m_presetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onValuesUpdated(int)));
    connect(m_intensitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(onValuesUpdated(int)));
}

void LedStripCard::onSwitchChanged(bool toggled)
{
    Q_UNUSED(toggled);

    if(m_speedSpinBox)
        m_speedSpinBox->setEnabled(m_onSwitch->isChecked());
    if(m_brightnessSpinBox)
        m_brightnessSpinBox->setEnabled(m_onSwitch->isChecked());
    if(m_presetSpinBox)
        m_presetSpinBox->setEnabled(m_onSwitch->isChecked());
    if(m_intensitySpinBox)
        m_intensitySpinBox->setEnabled(m_onSwitch->isChecked());

    if(!m_commandBlock)
    {
        m_ledStrip->setIsOn(true);
        m_ledStrip->saveState();
    }
}

void LedStripCard::onLedIsOnChanged()
{
    m_commandBlock = true;
    m_onSwitch->setChecked(m_ledStrip->isOn());
    m_commandBlock = false;
}

void LedStripCard::onLedErrorChanged()
{

}

void LedStripCard::onLedSpeedChanged()
{
    m_speedSpinBox->setValue(m_ledStrip->speed());
}

void LedStripCard::onLedPresetChanged()
{
    m_presetSpinBox->setValue(m_ledStrip->preset());
}

void LedStripCard::onLedBrightnessChanged()
{
    m_brightnessSpinBox->setValue(m_ledStrip->brightness());
}

void LedStripCard::onLedIntensityChanged()
{
    m_intensitySpinBox->setValue(m_ledStrip->intensity());
}

void LedStripCard::onResetButtonPressed()
{
    onLedBrightnessChanged();
    onLedErrorChanged();
    onLedIntensityChanged();
    onLedIsOnChanged();
    onLedPresetChanged();
    onLedSpeedChanged();

    m_resetButton->setEnabled(false);
    m_applyButton->setEnabled(false);
}

void LedStripCard::onApplyButtonPressed()
{
    m_ledStrip->setBrightness(m_brightnessSpinBox->value());
    m_ledStrip->setIntensity(m_intensitySpinBox->value());
    m_ledStrip->setPreset(m_presetSpinBox->value());
    m_ledStrip->setSpeed(m_speedSpinBox->value());
    m_ledStrip->saveState();

    m_resetButton->setEnabled(false);
    m_applyButton->setEnabled(false);
}

void LedStripCard::onValuesUpdated(int value)
{
    Q_UNUSED(value)

    bool enabled = false;

    if(m_ledStrip->brightness() != m_brightnessSpinBox->value())
        enabled = true;

    if(m_ledStrip->intensity() != m_intensitySpinBox->value())
        enabled = true;

    if(m_ledStrip->speed() != m_speedSpinBox->value())
        enabled = true;

    if(m_ledStrip->preset() != m_presetSpinBox->value())
        enabled = true;

    m_resetButton->setEnabled(enabled);
    m_applyButton->setEnabled(enabled);
}

void LedStripCard::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_centralLayout = new QGridLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_nameLabel = new QLabel(m_centralWidget);
    m_nameLabel->setText(m_ledStrip->name());
    m_centralLayout->addWidget(m_nameLabel, 0, 0);

    m_onSwitch = new Switch(m_centralWidget);
    m_onSwitch->setChecked(m_ledStrip->isOn());
    m_centralLayout->addWidget(m_onSwitch, 0, 1, Qt::AlignRight);

    m_chainCountLabel = new QLabel(m_centralWidget);
    m_chainCountLabel->setText(QString("%1 LEDs").arg(QString::number(m_ledStrip->chainCount())));
    m_centralLayout->addWidget(m_chainCountLabel, 1, 0, 1, 2);

    m_speedLabel = new QLabel(m_centralWidget);
    m_speedLabel->setText("Speed");
    m_centralLayout->addWidget(m_speedLabel, 2, 0);

    m_speedSpinBox = new QSpinBox(m_centralWidget);
    m_speedSpinBox->setValue(m_ledStrip->speed());
    m_centralLayout->addWidget(m_speedSpinBox, 2, 1);

    m_presetLabel = new QLabel(m_centralWidget);
    m_presetLabel->setText("Preset");
    m_centralLayout->addWidget(m_presetLabel, 3, 0);

    m_presetSpinBox = new QSpinBox(m_centralWidget);
    m_presetSpinBox->setValue(m_ledStrip->preset());
    m_centralLayout->addWidget(m_presetSpinBox, 3, 1);

    m_brightnessLabel = new QLabel(m_centralWidget);
    m_brightnessLabel->setText("Brightness");
    m_centralLayout->addWidget(m_brightnessLabel, 4, 0);

    m_brightnessSpinBox = new QSpinBox(m_centralWidget);
    m_brightnessSpinBox->setValue(m_ledStrip->brightness());
    m_centralLayout->addWidget(m_brightnessSpinBox, 4, 1);

    m_intensityLabel = new QLabel(m_centralWidget);
    m_intensityLabel->setText("Intensity");
    m_centralLayout->addWidget(m_intensityLabel, 5, 0);

    m_intensitySpinBox = new QSpinBox(m_centralWidget);
    m_intensitySpinBox->setValue(m_ledStrip->intensity());
    m_centralLayout->addWidget(m_intensitySpinBox, 5, 1);

    m_resetButton = new QIconButton(m_centralWidget);
    m_resetButton->setIcon(Settings::getThemeIcon("restart"));
    m_resetButton->setText("Reset");
    m_centralLayout->addWidget(m_resetButton, 6, 0);

    m_applyButton = new QIconButton(m_centralWidget);
    m_applyButton->setIcon(Settings::getThemeIcon("accept"));
    m_applyButton->setText("Apply");
    m_centralLayout->addWidget(m_applyButton, 6, 1);

    m_resetButton->setEnabled(false);
    m_applyButton->setEnabled(false);

    setCentralWidget(m_centralWidget);

    onSwitchChanged(m_onSwitch->isChecked());
}
