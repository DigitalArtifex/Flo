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

QKlipperAnnouncementList PrinterAnnouncementWidget::announcements() const
{
    return m_announcements;
}

void PrinterAnnouncementWidget::setAnnouncements(const QKlipperAnnouncementList &newAnnouncements)
{
    m_announcements = newAnnouncements;

    foreach(QKlipperAnnouncement announcement, m_announcements)
    {
        PrinterAnnouncementItem *item = new PrinterAnnouncementItem(announcement, this);
        connect(item, SIGNAL(dismissRequested(PrinterAnnouncementItem*)), this, SLOT(itemDismissRequestedEvent(PrinterAnnouncementItem*)));

        addItem(item);
    }
}
