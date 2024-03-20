#ifndef PRINTERLISTWIDGET_H
#define PRINTERLISTWIDGET_H

#include <QFrame>
#include <QSpacerItem>
#include <QMouseEvent>

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

    void addItem(PrinterListItem *item);

private slots:
    void on_itemClicked(PrinterListItem *item);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PrinterListWidget *ui;
    QList<PrinterListItem*> _items;
    QSpacerItem *_spacer = nullptr;
    PrinterListItem *_selectedItem = nullptr;
};

#endif // PRINTERLISTWIDGET_H
