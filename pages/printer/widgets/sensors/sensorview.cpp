#include "sensorview.h"
SensorView::SensorView(QKlipperSystem *system, QWidget *parent) :
    CardWidget{CardType::Widget, parent}
{
    setupUi();
    setSystem(system);
}

QKlipperSystem *SensorView::system() const
{
    return m_system;
}

void SensorView::setSystem(QKlipperSystem *system)
{
    if(system == m_system)
        return;

    m_system = system;

    onDeviceListChanged();
    connect(m_system, SIGNAL(sensorsChanged()), this, SLOT(onDeviceListChanged()));
}

void SensorView::setStyleSheet(const QString &styleSheet)
{
    CardWidget::setStyleSheet(styleSheet);
    QStringList keys = m_sensors.keys();

    for(QString &key : keys)
        m_sensors[key]->setStyleSheet(styleSheet);

    setupIcons();
}

void SensorView::reset()
{
    clear();

}

void SensorView::clear()
{
    for(auto iterator = m_sensors.begin(); iterator != m_sensors.end();)
    {
        m_scrollAreaLayout->removeWidget(iterator.value());
        iterator = m_sensors.erase(iterator);
    }
}

void SensorView::setupUi()
{
    clear();

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->resize(width(), 220);
    m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_scrollAreaWidget = new QWidget(m_scrollArea);
    m_scrollAreaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_scrollAreaLayout = new QFlowLayout(m_scrollAreaWidget);
    m_scrollAreaWidget->setLayout(m_scrollAreaLayout);
    m_scrollAreaWidget->setProperty("class", QStringList{"ScrollAreaContents"});

    // m_spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Ignored);
    // m_scrollAreaLayout->addItem(m_spacer);

    m_scrollArea->setWidget(m_scrollAreaWidget);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setWidgetResizable(true);

    setCentralWidget(m_scrollArea);
    setupIcons();
}

void SensorView::setupIcons()
{
}

void SensorView::onDeviceListChanged()
{
    QKlipperSensorMap list = m_system->sensors();
    QStringList keys = list.keys();

    for(QString &key : keys)
    {
        if(!m_sensors.contains(key))
        {
            SensorCard *card = new SensorCard(list[key], this);
            card->setFixedSize(280,300);

            //m_scrollAreaLayout->removeItem(m_spacer);
            m_scrollAreaLayout->addWidget(card);
            //m_scrollAreaLayout->addItem(m_spacer);

            m_sensors.insert(key, card);
        }
    }
}
