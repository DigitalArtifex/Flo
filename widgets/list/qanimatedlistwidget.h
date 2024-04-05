#ifndef QANIMATEDLISTWIDGET_H
#define QANIMATEDLISTWIDGET_H

#include <QObject>
#include <QScrollArea>
#include <QList>
#include <QSpacerItem>

#include "qanimatedlistitem.h"

class QAnimatedListWidget : public QScrollArea
{
    Q_OBJECT
public:
    enum SelectionMode
    {
        MultiSelect,
        SingleSelect,
        NoSelect
    };

    QAnimatedListWidget(QWidget *parent);

    virtual void addItem(QAnimatedListItem *item);
    virtual void addWidget(QWidget *widget);
    virtual void removeItem(QAnimatedListItem *item);
    virtual void removeWidget(QWidget *widget);
    virtual void clear();
    virtual bool isItemInViewport(QAnimatedListItem *item);

    virtual void setStyleSheet(QString styleSheet);

private slots:
    void on_listItem_animationOut_finished(QAnimatedListItem *item);
    void on_listItem_animationIn_finished(QAnimatedListItem *item);

    void on_item_selected(QAnimatedListItem *item);
    void on_item_deselected(QAnimatedListItem *item);

private:
    QList<QAnimatedListItem*> _items;
    QList<QAnimatedListItem*> _selectedItems;
    QWidget *_scrollAreaContents = nullptr;
    QSpacerItem *_spacer = nullptr;
};

#endif // QANIMATEDLISTWIDGET_H
