#include "printerannouncementwidget.h"

PrinterAnnouncementWidget::PrinterAnnouncementWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{

}

PrinterAnnouncementWidget::~PrinterAnnouncementWidget()
{
    clear();
}

void PrinterAnnouncementWidget::itemDismissRequestedEvent(PrinterAnnouncementItem *item)
{
    emit itemDismissRequested(item);
}

QList<System::Announcement> PrinterAnnouncementWidget::announcements() const
{
    return m_announcements;
}

void PrinterAnnouncementWidget::setAnnouncements(const QList<System::Announcement> &newAnnouncements)
{
    m_announcements = newAnnouncements;

    foreach(System::Announcement announcement, m_announcements)
    {
        PrinterAnnouncementItem *item = new PrinterAnnouncementItem(announcement, this);
        connect(item, SIGNAL(dismissRequested(PrinterAnnouncementItem*)), this, SLOT(itemDismissRequestedEvent(PrinterAnnouncementItem*)));

        setAnimationSlide(item);
        item->setDuration(150);

        addItem(item);
    }
}
