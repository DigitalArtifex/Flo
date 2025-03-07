#ifndef QANIMATEDLISTWIDGET_H
#define QANIMATEDLISTWIDGET_H

#include <QObject>
#include <QScrollArea>
#include <QList>
#include <QSpacerItem>
#include <QScrollBar>
#include <QResizeEvent>
#include <QParallelAnimationGroup>

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

    enum class AnimationStyle
    {
        SlideLeft = 1,
        SlideRight = 2,
        SlideTop = 4,
        SlideBottom = 8,
        Opacity = 16
    };

    enum class AnimationDirection
    {
        Forward = 1,
        Backwards = 2
    };

    QAnimatedListWidget(QWidget *parent);

    virtual void addItem(QAnimatedListItem *item);
    virtual void removeItem(QAnimatedListItem *item);
    virtual void removeAt(int index);
    virtual void clear();

    virtual void setEmptyText(const QString &text);
    virtual void setEmptyIcon(const QPixmap &pixmap);
    virtual void setEmptyIcon(const QIcon &icon);

    virtual void setStyleSheet(QString styleSheet);

    SelectionMode selectionMode() const;
    void setSelectionMode(SelectionMode selectionMode);

    bool autoScroll() const;

    int animationDuration() const;

    QWidget *scrollAreaContents() const;

public slots:
    void setAutoScroll(bool autoScroll);

    void setAnimationDuration(int animationDuration);

signals:
    void itemSelected(QAnimatedListItem *item);
    void itemDoubleClicked(QAnimatedListItem *item);

private slots:
    void onClearAnimationFinished();
    void on_listItem_animationOut_finished(QAnimatedListItem *item);

    void on_item_selected(QAnimatedListItem *item);
    void on_item_deselected(QAnimatedListItem *item);
    void itemDoubleClickedEvent(QAnimatedListItem *item);

    void onVerticalScrollbarRangeChange(int min, int max);

protected:
    bool isItemInViewport(QAnimatedListItem *item);
    void setAnimation(QAnimatedListItem *item, AnimationDirection direction = AnimationDirection::Forward);
    virtual void resizeEvent(QResizeEvent *event);

    int m_animatingItems = 0;
    int m_animationDuration = 300;

    QList<QAnimatedListItem*> m_items;
    QList<QAnimatedListItem*> m_clearingItems;
    QList<QAnimatedListItem*> m_selectedItems;
    QParallelAnimationGroup *m_clearAnimation = nullptr;

    QString m_emptyText;
    QPixmap m_emptyPixmap;

    QAnimatedEmptyListItem *m_emptyListItem = nullptr;

    QWidget *m_scrollAreaContents = nullptr;

    SelectionMode m_selectionMode = SingleSelect;
    AnimationStyle m_animationStyle = AnimationStyle(24);

    bool m_autoScroll = false;
};

inline constexpr QAnimatedListWidget::AnimationStyle operator|(QAnimatedListWidget::AnimationStyle a, QAnimatedListWidget::AnimationStyle b)
{
    return static_cast<QAnimatedListWidget::AnimationStyle>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline constexpr QAnimatedListWidget::AnimationStyle operator&(QAnimatedListWidget::AnimationStyle a, QAnimatedListWidget::AnimationStyle b)
{
    return static_cast<QAnimatedListWidget::AnimationStyle>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

inline constexpr QAnimatedListWidget::AnimationStyle operator^(QAnimatedListWidget::AnimationStyle a, QAnimatedListWidget::AnimationStyle b)
{
    return static_cast<QAnimatedListWidget::AnimationStyle>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}

inline constexpr QAnimatedListWidget::AnimationStyle operator~(QAnimatedListWidget::AnimationStyle a)
{
    return static_cast<QAnimatedListWidget::AnimationStyle>(~static_cast<unsigned int>(a));
}

inline constexpr QAnimatedListWidget::AnimationStyle operator|=(QAnimatedListWidget::AnimationStyle &a, QAnimatedListWidget::AnimationStyle b)
{
    return a = static_cast<QAnimatedListWidget::AnimationStyle>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline constexpr QAnimatedListWidget::AnimationStyle operator&=(QAnimatedListWidget::AnimationStyle &a, QAnimatedListWidget::AnimationStyle b)
{
    return a = static_cast<QAnimatedListWidget::AnimationStyle>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

inline constexpr QAnimatedListWidget::AnimationStyle operator^=(QAnimatedListWidget::AnimationStyle &a, QAnimatedListWidget::AnimationStyle b)
{
    return a = static_cast<QAnimatedListWidget::AnimationStyle>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}
#endif // QANIMATEDLISTWIDGET_H
