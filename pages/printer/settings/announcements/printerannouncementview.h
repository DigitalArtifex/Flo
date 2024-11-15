#ifndef PRINTERANNOUNCEMENTVIEW_H
#define PRINTERANNOUNCEMENTVIEW_H

#include <QFrame>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include <QKlipper/qklipper.h>

#include "printerannouncementwidget.h"

class PrinterAnnouncementView : public QFrame
{
    Q_OBJECT
public:
    explicit PrinterAnnouncementView(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterAnnouncementView();

signals:

protected:
    void setupUi();

protected slots:
    void onServerAnnouncementsChanged();
    void refreshButtonClickEvent();
    void itemDismissRequestedEvent(PrinterAnnouncementItem *item);

private:
    QKlipperInstance *m_instance = nullptr;

    PrinterAnnouncementWidget *m_updateWidget = nullptr;

    QLabel *m_titleLabel = nullptr;

    QToolButton *m_refreshButton = nullptr;

    QWidget *m_actionBar = nullptr;

    QGridLayout *m_layout = nullptr;
    QGridLayout *m_actionBarLayout = nullptr;

};

#endif // PRINTERANNOUNCEMENTVIEW_H
