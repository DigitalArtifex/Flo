#ifndef PRINTERANNOUNCEMENTWIDGET_H
#define PRINTERANNOUNCEMENTWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include "printerannouncementitem.h"

#include "ui/list/qanimatedlistwidget.h"
#include <QKlipper/qklipper.h>

class PrinterAnnouncementWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    explicit PrinterAnnouncementWidget(QWidget *parent);
    ~PrinterAnnouncementWidget();

    QKlipperAnnouncementList announcements() const;
    void setAnnouncements(const QKlipperAnnouncementList &newAnnouncements);

signals:
    void itemDismissRequested(PrinterAnnouncementItem *item);

protected slots:
    void itemDismissRequestedEvent(PrinterAnnouncementItem* item);

private:
    QKlipperAnnouncementList m_announcements;
};

#endif // PRINTERANNOUNCEMENTWIDGET_H
