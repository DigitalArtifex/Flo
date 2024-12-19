#include "printerannouncementview.h"

#include "system/settings.h"

PrinterAnnouncementView::PrinterAnnouncementView(QKlipperInstance *instance, QWidget *parent)
    : QFrame{parent}
{
    m_instance = instance;
    setupUi();
}

PrinterAnnouncementView::~PrinterAnnouncementView()
{

}

void PrinterAnnouncementView::setupUi()
{
    m_layout = new QGridLayout();
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    //Action bar
    m_actionBar = new QWidget();
    m_actionBarLayout = new QGridLayout(m_actionBar);
    m_actionBarLayout->setContentsMargins(4,4,4,4);

    m_titleLabel = new QLabel(m_actionBar);
    m_titleLabel->setText(QString("Announcements"));
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_actionBarLayout->addWidget(m_titleLabel, 0, 0, 1, 1);

    QSpacerItem *actionSpacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_actionBarLayout->addItem(actionSpacer, 0, 1, 1, 1);

    m_refreshButton = new QToolButton(m_actionBar);
    m_refreshButton->setFixedSize(32,32);
    m_refreshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_refreshButton, 0, 2, 1, 1);

    m_actionBar->setLayout(m_actionBarLayout);
    m_layout->addWidget(m_actionBar, 0, 0, 1, 2);

    m_updateWidget = new PrinterAnnouncementWidget(this);
    m_layout->addWidget(m_updateWidget);

    m_refreshButton->setIcon(Settings::getThemeIcon(QString("refresh")));

    connect(m_refreshButton, SIGNAL(clicked()), this, SLOT(refreshButtonClickEvent()));
    //connect(m_updateWidget, SIGNAL(itemUpdateRequested(PrinterUpdateItem*)), this, SLOT(itemUpdateRequestedEvent(PrinterUpdateItem*)));

    connect(m_instance->server(), SIGNAL(announcementsChanged()), this, SLOT(onServerAnnouncementsChanged()));

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
    m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));

    setLayout(m_layout);
}

void PrinterAnnouncementView::onServerAnnouncementsChanged()
{
    m_updateWidget->clear();
    m_updateWidget->setAnnouncements(m_instance->server()->announcements());
}

void PrinterAnnouncementView::refreshButtonClickEvent()
{
    m_updateWidget->clear();
    m_instance->console()->serverAnnouncementsUpdate();
}

void PrinterAnnouncementView::itemDismissRequestedEvent(PrinterAnnouncementItem *item)
{
    m_instance->console()->serverAnnouncementDismiss(item->announcement().entryId());
}
