#ifndef PRINTERANNOUNCEMENTWIDGET_H
#define PRINTERANNOUNCEMENTWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include "printerannouncementitem.h"

#include "ui/list/qanimatedlistwidget.h"
#include "types/system.h"

class PrinterAnnouncementWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    explicit PrinterAnnouncementWidget(QWidget *parent);
    ~PrinterAnnouncementWidget();

    System::UpdateState updateState() const;
    void setUpdateState(const System::UpdateState &newUpdateState);

    QList<System::Announcement> announcements() const;
    void setAnnouncements(const QList<System::Announcement> &newAnnouncements);

signals:
    void itemDismissRequested(PrinterAnnouncementItem *item);

protected slots:
    void itemDismissRequestedEvent(PrinterAnnouncementItem* item);

private:
    System::UpdateState m_updateState;
    QList<System::Announcement> m_announcements;
};

#endif // PRINTERANNOUNCEMENTWIDGET_H
