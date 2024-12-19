#include "ledstripview.h"

LedStripView::LedStripView(QKlipperSystem *system, QWidget *parent) :
    CardWidget{CardWidget::Widget, parent}
{
    setupUi();
    setSystem(system);
}

QKlipperSystem *LedStripView::system() const
{
    return m_system;
}

void LedStripView::setSystem(QKlipperSystem *system)
{
    if(system == m_system)
        return;

    m_system = system;

    onDeviceListChanged();
    connect(m_system, SIGNAL(powerDevicesChanged()), this, SLOT(onDeviceListChanged()));
}

void LedStripView::setStyleSheet(const QString &styleSheet)
{
    CardWidget::setStyleSheet(styleSheet);
    QStringList keys = m_powerDevices.keys();

    for(QString &key : keys)
        m_powerDevices[key]->setStyleSheet(styleSheet);

    setupIcons();
}

void LedStripView::clear()
{

}

void LedStripView::setupUi()
{
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->resize(width(), 220);
    m_scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_scrollAreaWidget = new QWidget(m_scrollArea);
    m_scrollAreaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_scrollAreaLayout = new QFlowLayout(m_scrollAreaWidget);
    m_scrollAreaWidget->setLayout(m_scrollAreaLayout);
    m_scrollAreaWidget->setProperty("class", QStringList{"ScrollAreaContents"});

    m_spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Ignored);
    m_scrollAreaLayout->addItem(m_spacer);

    m_scrollArea->setWidget(m_scrollAreaWidget);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setWidgetResizable(true);

    setCentralWidget(m_scrollArea);
    setupIcons();
}

void LedStripView::setupIcons()
{
}

void LedStripView::onDeviceListChanged()
{
    QKlipperLedStripList list = m_system->ledStrips();
    QStringList keys = list.keys();

    for(QString &key : keys)
    {
        if(!m_powerDevices.contains(key))
        {
            LedStripCard *card = new LedStripCard(list[key], this);
            card->setFixedSize(280,300);
            card->setCardFlags(CardWidget::NoTitleBar);

            m_scrollAreaLayout->removeItem(m_spacer);
            m_scrollAreaLayout->addWidget(card);
            m_scrollAreaLayout->addItem(m_spacer);

            m_powerDevices.insert(key, card);
        }
    }
}
