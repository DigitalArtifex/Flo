#include "powerdevicecard.h"

PowerDeviceCard::PowerDeviceCard(QKlipperPowerDevice *powerDevice, QWidget *parent) :
    CardWidget(CardWidget::SubWidget, parent)
{
    setupUi();
    setPowerDevice(powerDevice);
}

QKlipperPowerDevice *PowerDeviceCard::powerDevice() const
{
    return m_powerDevice;
}

void PowerDeviceCard::setPowerDevice(QKlipperPowerDevice *powerDevice)
{
    if(m_powerDevice == powerDevice)
        return;

    m_powerDevice = powerDevice;

    connect(m_powerDevice, SIGNAL(isOnChanged()), this, SLOT(onDeviceStateChanged()));
    onDeviceStateChanged();
}

void PowerDeviceCard::setStyleSheet(const QString &styleSheet)
{
    CardWidget::setStyleSheet(styleSheet);
    setIcons();
}

void PowerDeviceCard::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralLayout = new QHBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_powerButton = new QIconButton(m_centralWidget);
    m_powerButton->setCheckable(true);
    m_powerButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_powerButton->setFlag(QIconButton::IconVCentered, false);
    m_powerButton->setFlag(QIconButton::IconHCentered);
    m_powerButton->setTextMargins(QMargins(0,0,0,0));
    m_centralLayout->addWidget(m_powerButton);

    setCentralWidget(m_centralWidget);

    setIcons();
}

void PowerDeviceCard::setIcons()
{
    if(m_powerButton && m_powerDevice)
    {
        switch(m_powerDevice->type())
        {
            case QKlipperPowerDevice::GPIO:
                m_powerButton->setIcon(Settings::getThemeIcon("mcu-icon"));
                break;
            case QKlipperPowerDevice::Mqtt:
                m_powerButton->setIcon(Settings::getThemeIcon("mqtt-icon"));
                break;
            case QKlipperPowerDevice::RfDevice:
            case QKlipperPowerDevice::HttpDevice:
                m_powerButton->setIcon(Settings::getThemeIcon("connection-icon"));
                break;
            case QKlipperPowerDevice::TpLink:
                m_powerButton->setIcon(Settings::getThemeIcon("tplink-icon"));
                break;
            case QKlipperPowerDevice::Tasmota:
                m_powerButton->setIcon(Settings::getThemeIcon("tasmota-icon"));
                break;
            case QKlipperPowerDevice::Shelly:
            case QKlipperPowerDevice::Homeseer:
            case QKlipperPowerDevice::HomeAssistant:
            case QKlipperPowerDevice::Loxonevl:
            case QKlipperPowerDevice::SmartThings:
            case QKlipperPowerDevice::PhillipsHue:
            case QKlipperPowerDevice::UHubCtl:
            case QKlipperPowerDevice::KlipperDevice:
            default:
                m_powerButton->setIcon(Settings::getThemeIcon("power-icon"));
                break;
        }
    }
}

void PowerDeviceCard::onDeviceStateChanged()
{
    setTitle(m_powerDevice->name());
    m_powerButton->setChecked(m_powerDevice && m_powerDevice->isOn());
    m_powerButton->setText(m_powerDevice->name());
    setIcons();
}
