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
    setupIcons();
}

void PowerDeviceCard::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralLayout = new QHBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_iconLabel = new QLabel(m_centralWidget);
    m_iconLabel->setFixedSize(24,24);
    m_centralLayout->addWidget(m_iconLabel);

    m_textLabel = new QLabel(m_centralWidget);
    m_textLabel->setAlignment(Qt::AlignCenter);
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralLayout->addWidget(m_textLabel);

    m_onSwitch = new Switch(m_centralWidget);
    m_onSwitch->setFixedWidth(50);
    m_centralLayout->addWidget(m_onSwitch);

    setCentralWidget(m_centralWidget);

    setupIcons();

    setProperty("class", property("class").toStringList() + QStringList { "Button" });

    connect(m_onSwitch, SIGNAL(toggled(bool)), this, SLOT(onSwitchStateChanged(bool)));
}

void PowerDeviceCard::setupIcons()
{
    if(m_iconLabel && m_powerDevice)
    {
        switch(m_powerDevice->type())
        {
            case QKlipperPowerDevice::GPIO:
                m_iconLabel->setPixmap(Settings::getThemeIcon("mcu").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::Mqtt:
                m_iconLabel->setPixmap(Settings::getThemeIcon("mqtt").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::RfDevice:
            case QKlipperPowerDevice::HttpDevice:
                m_iconLabel->setPixmap(Settings::getThemeIcon("connection").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::TpLink:
                m_iconLabel->setPixmap(Settings::getThemeIcon("tplink").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::Tasmota:
                m_iconLabel->setPixmap(Settings::getThemeIcon("tasmota").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::HomeAssistant:
                m_iconLabel->setPixmap(Settings::getThemeIcon("homeassistant").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::Homeseer:
                m_iconLabel->setPixmap(Settings::getThemeIcon("homeseer").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::SmartThings:
                m_iconLabel->setPixmap(Settings::getThemeIcon("smartthings").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::Shelly:
                m_iconLabel->setPixmap(Settings::getThemeIcon("shelly").pixmap(m_iconLabel->size()));
                break;
            case QKlipperPowerDevice::PhilipsHue:
            case QKlipperPowerDevice::Loxonevl:
            case QKlipperPowerDevice::UHubCtl:
            case QKlipperPowerDevice::KlipperDevice:
            default:
                m_iconLabel->setPixmap(Settings::getThemeIcon("power").pixmap(m_iconLabel->size()));
                break;
        }
    }
}

void PowerDeviceCard::onDeviceStateChanged()
{
    setTitle(m_powerDevice->name());

    disconnect(m_onSwitch, SIGNAL(toggled(bool)), this, SLOT(onSwitchStateChanged(bool)));
    m_onSwitch->setChecked(m_powerDevice && m_powerDevice->isOn());
    connect(m_onSwitch, SIGNAL(toggled(bool)), this, SLOT(onSwitchStateChanged(bool)));

    m_textLabel->setText(m_powerDevice->name());
    setupIcons();
    setProperty("checked", m_onSwitch->isChecked());
    style()->polish(this);
}

void PowerDeviceCard::onSwitchStateChanged(bool on)
{
    if(on)
        m_powerDevice->turnOn();
    else
        m_powerDevice->turnOff();

    setProperty("checked", on);
}

void PowerDeviceCard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setProperty("clicked", true);
        m_pressed = true;
        style()->polish(this);
    }
}

void PowerDeviceCard::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_pressed)
    {
        m_pressed = false;
        setProperty("clicked", m_pressed);
        setProperty("checked", !m_onSwitch->isChecked());
        style()->polish(this);

        m_onSwitch->setChecked(!m_onSwitch->isChecked());
    }
}
