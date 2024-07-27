#ifndef PRINTERUPDATEVIEW_H
#define PRINTERUPDATEVIEW_H

#include <QFrame>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include "types/printer.h"

#include "printerupdatewidget.h"

class PrinterUpdateView : public QFrame
{
    Q_OBJECT
public:
    explicit PrinterUpdateView(Printer *printer, QWidget *parent = nullptr);
    ~PrinterUpdateView();

signals:

protected:
    void setupUi();

protected slots:
    void updateStateUpdateEvent();
    void updateAllButtonClickEvent();
    void refreshButtonClickEvent();
    void itemUpdateRequestedEvent(PrinterUpdateItem *item);

    void machineUpdateAllEvent();
    void machineUpdateClientEvent(QString client);

private:
    Printer *m_printer = nullptr;

    PrinterUpdateWidget *m_updateWidget = nullptr;

    QLabel *m_titleLabel = nullptr;

    QToolButton *m_refreshButton = nullptr;
    QToolButton *m_updateAllButton = nullptr;

    QWidget *m_actionBar = nullptr;

    QGridLayout *m_layout = nullptr;
    QGridLayout *m_actionBarLayout = nullptr;

};

#endif // PRINTERUPDATEVIEW_H
