#ifndef PRINTERANNOUNCEMENTVIEW_H
#define PRINTERANNOUNCEMENTVIEW_H

#include <QFrame>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include "types/printer.h"

#include "printerannouncementwidget.h"

class PrinterAnnouncementView : public QFrame
{
    Q_OBJECT
public:
    explicit PrinterAnnouncementView(Printer *printer, QWidget *parent = nullptr);
    ~PrinterAnnouncementView();

signals:

protected:
    void setupUi();

protected slots:
    void printSystemUpdateEvent();
    void updateAllButtonClickEvent();
    void refreshButtonClickEvent();
    void itemDismissRequestedEvent(PrinterAnnouncementItem *item);

private:
    Printer *m_printer = nullptr;

    PrinterAnnouncementWidget *m_updateWidget = nullptr;

    QLabel *m_titleLabel = nullptr;

    QToolButton *m_refreshButton = nullptr;
    QToolButton *m_updateAllButton = nullptr;

    QWidget *m_actionBar = nullptr;

    QGridLayout *m_layout = nullptr;
    QGridLayout *m_actionBarLayout = nullptr;

};

#endif // PRINTERANNOUNCEMENTVIEW_H
