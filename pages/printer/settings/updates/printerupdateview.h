#ifndef PRINTERUPDATEVIEW_H
#define PRINTERUPDATEVIEW_H

#include <QFrame>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include <QKlipper/qklipper.h>

#include "printerupdatewidget.h"

class PrinterUpdateView : public QFrame
{
    Q_OBJECT
public:
    explicit PrinterUpdateView(QKlipperSystem *system, QWidget *parent = nullptr);
    ~PrinterUpdateView();

signals:

protected:
    void setupUi();

protected slots:
    void updateStateUpdateEvent();
    void updateAllButtonClickEvent();
    void refreshButtonClickEvent();
    void itemUpdateRequestedEvent(PrinterUpdateItem *item);

private:
    QKlipperSystem *m_system = nullptr;

    PrinterUpdateWidget *m_updateWidget = nullptr;

    QLabel *m_titleLabel = nullptr;

    QToolButton *m_refreshButton = nullptr;
    QToolButton *m_updateAllButton = nullptr;

    QWidget *m_actionBar = nullptr;

    QGridLayout *m_layout = nullptr;
    QGridLayout *m_actionBarLayout = nullptr;

};

#endif // PRINTERUPDATEVIEW_H
