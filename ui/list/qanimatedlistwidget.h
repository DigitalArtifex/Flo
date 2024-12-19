#ifndef QANIMATEDLISTWIDGET_H
#define QANIMATEDLISTWIDGET_H

#include <QObject>
#include <QScrollArea>
#include <QList>
#include <QSpacerItem>
#include <QScrollBar>
#include <QResizeEvent>

#include "qanimatedlistitem.h"
#include "qanimatedemptylistitem.h"

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

    virtual void setEmptyText(const QString &text);
    virtual void setEmptyIcon(const QPixmap &pixmap);
    virtual void setEmptyIcon(const QIcon &icon);

    virtual void setStyleSheet(QString styleSheet);

    void setAnimationSlide(QAnimatedListItem *item);

    SelectionMode selectionMode() const;
    void setSelectionMode(SelectionMode selectionMode);

signals:
    void itemSelected(QAnimatedListItem *item);
    void itemDoubleClicked(QAnimatedListItem *item);

private slots:
    void on_listItem_animationOut_finished(QAnimatedListItem *item);
    void on_listItem_animationIn_finished(QAnimatedListItem *item);

    void on_item_selected(QAnimatedListItem *item);
    void on_item_deselected(QAnimatedListItem *item);
    void itemDoubleClickedEvent(QAnimatedListItem *item);

    void onVerticalScrollbarRangeChange(int min, int max);

protected:
    virtual void resizeEvent(QResizeEvent *event);

    int m_animatingItems = 0;

    QList<QAnimatedListItem*> m_items;
    QList<QAnimatedListItem*> m_selectedItems;

    QString m_emptyText;
    QPixmap m_emptyPixmap;

    QAnimatedEmptyListItem *m_emptyListItem = nullptr;

    QWidget *m_scrollAreaContents = nullptr;
    QSpacerItem *m_spacer = nullptr;

    SelectionMode m_selectionMode = SingleSelect;
};

#endif // QANIMATEDLISTWIDGET_H
