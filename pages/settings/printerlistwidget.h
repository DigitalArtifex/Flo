#ifndef PRINTERLISTWIDGET_H
#define PRINTERLISTWIDGET_H

#include <QFrame>
#include <QSpacerItem>
#include <QMouseEvent>
#include <QKlipper/qklipper.h>

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

    void addItem(QKlipperInstance *definition);
    void removeItem(QKlipperInstance *instance);
    PrinterListItem *selectedItem();

signals:
    void itemSelected(PrinterListItem *item);

private slots:
    void on_itemClicked(PrinterListItem *item);

    void onInstanceRemoved(QKlipperInstance *instance);
    void onInstanceAdded(QKlipperInstance *instance);

    virtual void mousePressEvent(QMouseEvent *event);

private:
    Ui::PrinterListWidget *ui;
    QList<PrinterListItem*> m_items;
    QSpacerItem *m_spacer = nullptr;
    PrinterListItem *m_selectedItem = nullptr;
};

#endif // PRINTERLISTWIDGET_H
