#include "powerdeviceview.h"

PowerDeviceView::PowerDeviceView(QKlipperSystem *system, QWidget *parent) :
    CardWidget{CardWidget::Widget, parent}
{
    setupUi();
    setSystem(system);
}

QKlipperSystem *PowerDeviceView::system() const
{
    return m_system;
}

void PowerDeviceView::setSystem(QKlipperSystem *system)
{
    if(system == m_system)
        return;

    m_system = system;

    onDeviceListChanged();
    connect(m_system, SIGNAL(powerDevicesChanged()), this, SLOT(onDeviceListChanged()));
}

void PowerDeviceView::setStyleSheet(const QString &styleSheet)
{
    CardWidget::setStyleSheet(styleSheet);
    QStringList keys = m_powerDevices.keys();

    for(QString &key : keys)
        m_powerDevices[key]->setStyleSheet(styleSheet);

    setIcons();
}

void PowerDeviceView::clear()
{

}

void PowerDeviceView::setupUi()
{
    setTitle("Power Devices");

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->resize(width(), 220);
    //m_scrollArea->setStyleSheet("background-color: transparent;");
    m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_scrollAreaWidget = new QWidget(m_scrollArea);
    m_scrollAreaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_scrollAreaLayout = new QHBoxLayout(m_scrollAreaWidget);
    m_scrollAreaWidget->setLayout(m_scrollAreaLayout);
    m_scrollAreaWidget->setProperty("class", QStringList{"ScrollAreaContents"});
    //m_scrollAreaWidget->setStyleSheet("background-color: transparent;");

    m_spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Ignored);
    m_scrollAreaLayout->addItem(m_spacer);

    m_scrollArea->setWidget(m_scrollAreaWidget);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setWidgetResizable(true);
    // m_scrollArea->setLayout(new QHBoxLayout(m_scrollArea));
    // m_scrollArea->layout()->addWidget(m_scrollAreaWidget);

    setCentralWidget(m_scrollArea);
    setIcons();
}

void PowerDeviceView::setIcons()
{
    setIcon(Settings::getThemeIcon("plug-icon"));
}

void PowerDeviceView::onDeviceListChanged()
{
    QKlipperPowerDeviceList list = m_system->powerDevices();
    QStringList keys = list.keys();

    for(QString &key : keys)
    {
        if(!m_powerDevices.contains(key))
        {
            PowerDeviceCard *card = new PowerDeviceCard(list[key], this);
            card->setFixedSize(200,125);
            card->setCardFlags(CardWidget::NoTitleBar);

            m_scrollAreaLayout->removeItem(m_spacer);
            m_scrollAreaLayout->addWidget(card);
            m_scrollAreaLayout->addItem(m_spacer);

            m_powerDevices.insert(key, card);
        }
    }
}
