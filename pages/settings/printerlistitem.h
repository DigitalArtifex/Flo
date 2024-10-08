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

    PrinterDefinition printerDefinition();

signals:
    void clicked(PrinterListItem *item);
    void longPressed(PrinterListItem *item);

private slots:
    virtual void clickTimeout();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PrinterListItem *ui;
    PrinterDefinition m_definition;
    bool m_pressed = false;
    bool m_longPress = false;
    bool m_rightClick = false;
    QTimer *m_clickTimer = NULL;
};

#endif // PRINTERLISTITEM_H
