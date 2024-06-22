#ifndef PRINTERLISTWIDGET_H
#define PRINTERLISTWIDGET_H

#include <QFrame>
#include <QSpacerItem>
#include <QMouseEvent>

#include "../../types/printer.h"
#include "printerlistitem.h"

namespace Ui {
class PrinterListWidget;
}

class PrinterListWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterListWidget(QWidget *parent = nullptr);
    ~PrinterListWidget();

    void addItem(PrinterDefinition definition);
    PrinterListItem *selectedItem();

signals:
    void itemSelected(PrinterListItem *item);

private slots:
    void on_itemClicked(PrinterListItem *item);
    void on_printerPool_printerRemoved(Printer *printer);
    void on_printerPool_printerAdded(Printer *printer);
    void on_printerPool_printerUpdated(Printer *printer);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PrinterListWidget *ui;
    QList<PrinterListItem*> m_items;
    QSpacerItem *m_spacer = nullptr;
    PrinterListItem *m_selectedItem = nullptr;
};

#endif // PRINTERLISTWIDGET_H
