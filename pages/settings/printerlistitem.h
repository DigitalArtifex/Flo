#ifndef PRINTERLISTITEM_H
#define PRINTERLISTITEM_H

#include <QFrame>
#include <QListWidgetItem>
#include <QTimer>
#include <QMouseEvent>

#include "../../types/printerdefinition.h"

namespace Ui {
class PrinterListItem;
}

class PrinterListItem : public QFrame, public QListWidgetItem
{
    Q_OBJECT

public:
    explicit PrinterListItem(QWidget *parent = nullptr);
    ~PrinterListItem();

    void setPrinterDefinition(PrinterDefinition definition);
    void setUiClasses();
    void setSelected(bool selected);
    bool selected();

signals:
    void clicked(PrinterListItem *item);
    void longPressed(PrinterListItem *item);

private slots:
    virtual void clickTimeout();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PrinterListItem *ui;
    PrinterDefinition _definition;
    bool _pressed = false;
    bool _longPress = false;
    bool _rightClick = false;
    QTimer *_clickTimer = NULL;
};

#endif // PRINTERLISTITEM_H
