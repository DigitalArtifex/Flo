#include "printerannouncementitem.h"

#include "flo/settings.h"

PrinterAnnouncementItem::PrinterAnnouncementItem(QKlipperAnnouncement announcement, QWidget *parent)
    : QAnimatedListItem{parent}
{
    m_announcement = announcement;
    setupUi();
}

void PrinterAnnouncementItem::updateButtonClickEvent()
{
    emit dismissRequested(this);
}

void PrinterAnnouncementItem::setupUi()
{
    m_layout = new QGridLayout();

    m_iconContainer = new QWidget(this);
    m_iconContainer->setLayout(new QVBoxLayout(m_iconContainer));
    m_iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    m_iconContainer->layout()->setContentsMargins(0,0,0,0);
    m_layout->addWidget(m_iconContainer,0,0,2,1);

    m_iconLabel = new QLabel(this);
    m_iconContainer->layout()->addWidget(m_iconLabel);

    setFixedHeight(50);
    m_iconContainer->setFixedWidth(45);
    m_iconLabel->setFixedSize(32,32);

    QPixmap icon = Settings::getThemeIcon(QString("file")).pixmap(32,32);

    if(m_title.toLower() == QString("crowsnest"))
        icon = Settings::getThemeIcon(QString("crowsnest")).pixmap(32,32);

    if(m_title.toLower() == QString("klipper"))
        icon = Settings::getThemeIcon(QString("klipper")).pixmap(32,32);

    if(m_title.contains("mainsail", Qt::CaseInsensitive))
        icon = Settings::getThemeIcon(QString("mainsail")).pixmap(32,32);

    m_iconLabel->setPixmap(icon);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setText(m_announcement.title());

    m_versionLabel = new QLabel(this);
    m_versionLabel->setText(m_announcement.source());

    //_spacer = new QSpacerItem(10,10, QSizePolicy::Ignored, QSizePolicy::Expanding);

    m_branchLabel = new QLabel(this);
    m_branchLabel->setText(m_announcement.priority());
    m_branchLabel->setFixedWidth(64);
    m_branchLabel->setAlignment(Qt::AlignRight);

    m_updateButton = new QToolButton(this);
    m_updateButton->setIcon(Settings::getThemeIcon(QString("cancel")));
    m_updateButton->setIconSize(QSize(32,32));
    m_updateButton->setFixedSize(35,35);

    connect(m_updateButton, SIGNAL(clicked(bool)), this, SLOT(updateActionTriggered(bool)));

    m_layout->addWidget(m_titleLabel,0,1,1,1);
    m_layout->addWidget(m_versionLabel,0,2,1,1);
    m_layout->addWidget(m_branchLabel,0,3,1,1);
    m_layout->addWidget(m_updateButton,0,4,1,1);

    m_branchLabel->setProperty("class", "FileWidgetItemDetails");
    m_versionLabel->setProperty("class", "FileWidgetItemDetails");
    m_titleLabel->setProperty("class", "FileWidgetItemTitle");

    QIcon actionIcon = Settings::getThemeIcon("print");
    m_updateAction = new QAction(actionIcon, "Print", this);
    connect(m_updateAction, SIGNAL(triggered(bool)), this, SLOT(updateActionTriggered(bool)));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(m_updateAction);

    setContextMenu(contextMenu);

    setLayout(m_layout);
}

QKlipperAnnouncement PrinterAnnouncementItem::announcement() const
{
    return m_announcement;
}

void PrinterAnnouncementItem::setAnnouncement(const QKlipperAnnouncement &newAnnouncement)
{
    m_announcement = newAnnouncement;
}

void PrinterAnnouncementItem::updateActionTriggered(bool checked)
{
    Q_UNUSED(checked)

    emit dismissRequested(this);
}
