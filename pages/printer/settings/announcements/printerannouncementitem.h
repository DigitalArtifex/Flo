#ifndef PRINTERANNOUNCEMENTITEM_H
#define PRINTERANNOUNCEMENTITEM_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>

#include "ui/list/qanimatedlistitem.h"
#include <QKlipper/qklipper.h>

class PrinterAnnouncementItem : public QAnimatedListItem
{
    Q_OBJECT
public:
    explicit PrinterAnnouncementItem(QKlipperAnnouncement announcement, QWidget *parent = nullptr);

    QKlipperAnnouncement announcement() const;
    void setAnnouncement(const QKlipperAnnouncement &newAnnouncement);

signals:
    void dismissRequested(PrinterAnnouncementItem *item);

protected slots:
    void updateActionTriggered(bool checked);
    void updateButtonClickEvent();
    void setupUi();

private:
    QKlipperAnnouncement m_announcement;

    QString m_title;

    QToolButton *m_updateButton = nullptr;

    //UI Elements
    QLabel *m_titleLabel = nullptr;
    QLabel *m_versionLabel = nullptr;
    QLabel *m_branchLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QWidget *m_iconContainer = nullptr;

    QGridLayout *m_layout = nullptr;
    QSpacerItem *m_spacer = nullptr;

    //Context menu
    QAction *m_updateAction = nullptr;
};

#endif // PRINTERANNOUNCEMENTITEM_H
