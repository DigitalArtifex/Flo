#include "qanimatedlistwidget.h"

#include "ui/layouts/qflowlayout.h"

#include <QApplication>

QAnimatedListWidget::QAnimatedListWidget(QWidget *parent) :
    QScrollArea(parent)
{
    QFlowLayout *layout = new QFlowLayout(m_scrollAreaContents);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setContentsMargins(0,0,0,0);

    m_scrollAreaContents = new QWidget(this);
    m_scrollAreaContents->setLayout(layout);

    m_emptyListItem = new QAnimatedEmptyListItem(this);
    m_emptyListItem->setFixedSize(size());
    m_emptyListItem->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    m_scrollAreaContents->layout()->addWidget(m_emptyListItem);
    m_scrollAreaContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setWidget(m_scrollAreaContents);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setWidgetResizable(true);

    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "List"));

    connect(verticalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(onVerticalScrollbarRangeChange(int,int)));
}

void QAnimatedListWidget::addItem(QAnimatedListItem *item)
{
    if(m_emptyListItem)
    {
        m_scrollAreaContents->layout()->removeWidget(m_emptyListItem);
        m_emptyListItem->deleteLater();
        m_emptyListItem = nullptr;
    }

    if((m_selectionMode == SingleSelect) | (m_selectionMode == MultiSelect))
    {
        item->setSelected(false, false);
        item->setSelectable(true);
    }
    else if(m_selectionMode == NoSelect)
    {
        item->setSelected(false, false);
        item->setSelectable(false);
    }

    connect(item, SIGNAL(selected(QAnimatedListItem*)), this, SLOT(on_item_selected(QAnimatedListItem*)));
    connect(item, SIGNAL(deselected(QAnimatedListItem*)), this, SLOT(on_item_deselected(QAnimatedListItem*)));
    connect(item, SIGNAL(doubleClicked(QAnimatedListItem*)), this, SLOT(itemDoubleClickedEvent(QAnimatedListItem*)));

    item->setFixedWidth(viewport()->width() - (m_scrollAreaContents->layout()->contentsMargins().left() + m_scrollAreaContents->layout()->contentsMargins().right()));
    m_scrollAreaContents->layout()->addWidget(item);
    item->show();

    setAnimation(item);
    item->animations()->start(QAbstractAnimation::KeepWhenStopped);

    m_items.append(item);
}

void QAnimatedListWidget::removeItem(QAnimatedListItem *item)
{
    if(m_items.contains(item) && isItemInViewport(item))
    {
        m_clearAnimation = new QParallelAnimationGroup(this);

        setAnimation(item, AnimationDirection::Backwards);

        int index = m_items.indexOf(item);
        int offset = item->height();

        for(int i = index + 1; i < m_items.count(); i++)
        {
            if(!isItemInViewport(item))
                break;

            qDebug() << "Animating";

            QPropertyAnimation *animation = new QPropertyAnimation(m_items[i], "geometry");

            QRect geometryStart(
                m_items[i]->x(),
                m_items[i]->y(),
                m_items[i]->width(),
                m_items[i]->height()
                );

            QRect geometryEnd(
                m_items[i]->x(),
                m_items[i]->y() - offset,
                m_items[i]->width(),
                m_items[i]->height()
                );

            animation->setStartValue(geometryStart);
            animation->setEndValue(geometryEnd);
            animation->setDuration(m_animationDuration);

            m_clearAnimation->addAnimation(animation);
        }

        m_clearAnimation->addAnimation(item->animations());

        QEventLoop loop;

        connect(m_clearAnimation, &QParallelAnimationGroup::finished, this, [&loop, this]() { loop.exit(); });
        m_clearAnimation->start();
        loop.exec();

        delete m_clearAnimation;

        m_items.takeAt(index);
        m_scrollAreaContents->layout()->removeWidget(item);
        delete item;
    }
    else if(m_items.contains(item))
    {
        m_items.takeAt(m_items.indexOf(item));
        m_scrollAreaContents->layout()->removeWidget(item);
        delete item;
    }
}

void QAnimatedListWidget::removeAt(int index)
{
    if(index < m_items.count())
        removeItem(m_items[index]);
}

void QAnimatedListWidget::clear()
{
    if(m_items.isEmpty())
        return;

    m_selectedItems.clear();

    if(!m_scrollAreaContents->visibleRegion().isEmpty())
    {
        if(m_clearAnimation)
            delete m_clearAnimation;

        m_clearAnimation = new QParallelAnimationGroup(this);

        for(auto item : m_items)
        {
            if(isItemInViewport(item))
            {
                setAnimation(item, AnimationDirection::Backwards);
                m_clearAnimation->addAnimation(item->animations());
            }
        }

        while(!m_items.isEmpty())
        {
            QAnimatedListItem *item = m_items.takeAt(0);
            m_clearingItems.append(item);
        }

        connect(m_clearAnimation, SIGNAL(finished()), this, SLOT(onClearAnimationFinished()));
        m_clearAnimation->start();
    }
    else
    {
        while(!m_items.isEmpty())
        {
            QAnimatedListItem *item = m_items.takeAt(0);
            m_scrollAreaContents->layout()->removeWidget(item);
            delete item;
        }
    }
}

void QAnimatedListWidget::setStyleSheet(QString styleSheet)
{
    QScrollArea::setStyleSheet(styleSheet);
    // m_scrollAreaContents->setStyleSheet(styleSheet);

    // for(int i = 0; i < m_items.count(); i++)
    // {
    //     m_items[i]->setStyleSheet(styleSheet);
    //     style()->polish(m_items[i]);
    // }
}

bool QAnimatedListWidget::isItemInViewport(QAnimatedListItem *item)
{
    return !(item->visibleRegion().isEmpty());
}

void QAnimatedListWidget::setEmptyText(const QString &text)
{
    m_emptyText = text;

    if(m_emptyListItem)
        m_emptyListItem->setText(text);
}

void QAnimatedListWidget::setEmptyIcon(const QPixmap &pixmap)
{
    m_emptyPixmap = pixmap;
}

void QAnimatedListWidget::setEmptyIcon(const QIcon &icon)
{
    m_emptyPixmap = icon.pixmap(64,64);

    if(m_emptyListItem)
        m_emptyListItem->setIcon(m_emptyPixmap);
}

void QAnimatedListWidget::on_listItem_animationOut_finished(QAnimatedListItem *item)
{
    m_scrollAreaContents->layout()->removeWidget(item);
    delete item;

    if(m_items.isEmpty())
    {
        if(!m_emptyListItem)
        {
            m_emptyListItem = new QAnimatedEmptyListItem(this);
            m_emptyListItem->setFixedSize(size());
            m_emptyListItem->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

            if(!m_emptyText.isEmpty())
                m_emptyListItem->setText(m_emptyText);

            if(!m_emptyPixmap.isNull())
                m_emptyListItem->setIcon(m_emptyPixmap);

            m_scrollAreaContents->layout()->addWidget(m_emptyListItem);
        }
    }
}

void QAnimatedListWidget::on_item_selected(QAnimatedListItem *item)
{
    if(m_selectionMode == SingleSelect)
    {
        for(int i = 0; i < m_selectedItems.count(); i++)
        {
            if(item != m_selectedItems[i])
                m_selectedItems[i]->setSelected(false, false);
        }

        m_selectedItems.clear();
        m_selectedItems.append(item);
    }
    else if(m_selectionMode == MultiSelect)
    {
        if(!m_selectedItems.contains(item))
            m_selectedItems.append(item);
    }
    else if(m_selectionMode == NoSelect)
    {
        item->setSelected(false, false);
        item->setSelectable(false);

        return;
    }

    emit itemSelected(item);
}

void QAnimatedListWidget::on_item_deselected(QAnimatedListItem *item)
{
    if(m_selectedItems.contains(item))
        m_selectedItems.removeOne(item);

    if(m_selectedItems.count() <= 0)
        emit itemSelected(nullptr);
}

void QAnimatedListWidget::itemDoubleClickedEvent(QAnimatedListItem *item)
{
    emit itemDoubleClicked(item);
}

void QAnimatedListWidget::onVerticalScrollbarRangeChange(int min, int max)
{
    Q_UNUSED(min)

    if(!m_autoScroll)
        return;

    if(verticalScrollBar()->value() != min && verticalScrollBar()->value() != max)
        return;

    int x = m_scrollAreaContents->contentsMargins().top();
    x += m_scrollAreaContents->contentsMargins().bottom();

    auto children = m_scrollAreaContents->findChildren<QAnimatedListItem*>();

    for(auto child : children)
        x += child->height();

    x += (m_scrollAreaContents->layout()->spacing() * children.count());

    if(x > height())
    {
        verticalScrollBar()->setValue(max);
    }
}

void QAnimatedListWidget::setAnimation(QAnimatedListItem *item, AnimationDirection direction)
{
    item->initAnimations();

    qint32 ypos = item->y(); // ((0 + (item->height() * m_items.count())) + );

    if(direction == AnimationDirection::Forward)
    {
        ypos = (m_scrollAreaContents->layout()->contentsMargins().top());
        ypos += m_scrollAreaContents->layout()->spacing() * m_items.count();

        for(auto child : m_items)
        ypos += child->height();
    }

    QPropertyAnimation *animation = nullptr;

    QRect geometryStart;
    QRect geometryEnd;

    int xPadding = m_scrollAreaContents->layout()->contentsMargins().left() + m_scrollAreaContents->layout()->contentsMargins().right();

    if((m_animationStyle & AnimationStyle::SlideRight) == AnimationStyle::SlideRight)
    {
        animation = new QPropertyAnimation(item, "geometry");

        geometryStart = QRect(
            width(),
            ypos,
            width() - xPadding,
            item->height()
            );

        geometryEnd = QRect(
            m_scrollAreaContents->layout()->contentsMargins().left(),
            ypos,
            width() - xPadding,
            item->height()
            );
    }

    else if((m_animationStyle & AnimationStyle::SlideLeft) == AnimationStyle::SlideLeft)
    {
        animation = new QPropertyAnimation(item, "geometry");

        geometryStart = QRect(
            width() * -1,
            ypos,
            width() - xPadding,
            item->height()
            );

        geometryEnd = QRect(
            m_scrollAreaContents->layout()->contentsMargins().left(),
            ypos,
            width() - xPadding,
            item->height()
            );
    }

    else if((m_animationStyle & AnimationStyle::SlideTop) == AnimationStyle::SlideTop)
    {
        animation = new QPropertyAnimation(item, "geometry");

        geometryStart = QRect(
            m_scrollAreaContents->layout()->contentsMargins().left(),
            item->height() * -1,
            width() - xPadding,
            item->height()
            );

        geometryEnd = QRect(
            m_scrollAreaContents->layout()->contentsMargins().left(),
            ypos,
            width() - xPadding,
            item->height()
            );
    }

    else if((m_animationStyle & AnimationStyle::SlideBottom) == AnimationStyle::SlideBottom)
    {
        animation = new QPropertyAnimation(item, "geometry");

        geometryStart = QRect(
            m_scrollAreaContents->layout()->contentsMargins().left(),
            (viewport()->height() + verticalScrollBar()->value()),
            width() - xPadding,
            item->height()
            );

        geometryEnd = QRect(
            m_scrollAreaContents->layout()->contentsMargins().left(),
            ypos,
            width() - xPadding,
            item->height()
            );

        qDebug() << geometryEnd;
    }

    if((m_animationStyle & AnimationStyle::Opacity) == AnimationStyle::Opacity)
    {
        item->setGraphicsEffect(new QGraphicsOpacityEffect);

        QPropertyAnimation *opacityAnimation = new QPropertyAnimation(item->graphicsEffect(), "opacity");
        opacityAnimation->setDuration(m_animationDuration);

        if(direction == AnimationDirection::Forward)
        {
            opacityAnimation->setStartValue(0);
            opacityAnimation->setEndValue(1);
        }
        else
        {
            opacityAnimation->setStartValue(1);
            opacityAnimation->setEndValue(0);
        }

        item->animations()->addAnimation(opacityAnimation);
    }

    if(animation)
    {
        if(direction == AnimationDirection::Forward)
        {
            animation->setStartValue(geometryStart);
            animation->setEndValue(geometryEnd);
        }
        else
        {
            animation->setStartValue(geometryEnd);
            animation->setEndValue(geometryStart);
        }

        animation->setDuration(m_animationDuration);
        item->animations()->addAnimation(animation);
    }
}

void QAnimatedListWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    int xPadding = m_scrollAreaContents->layout()->contentsMargins().left() + m_scrollAreaContents->layout()->contentsMargins().right();
    int yPadding = m_scrollAreaContents->layout()->contentsMargins().top() + m_scrollAreaContents->layout()->contentsMargins().bottom();

    QSize size = event->size();
    size.setHeight(size.height() - yPadding);
    size.setWidth(size.width() - xPadding);

    if(m_emptyListItem)
        m_emptyListItem->setFixedSize(size);

    auto children = m_scrollAreaContents->findChildren<QAnimatedListItem*>();

    for(auto child : children)
        child->setFixedWidth(viewport()->width() - xPadding);
}

QWidget *QAnimatedListWidget::scrollAreaContents() const
{
    return m_scrollAreaContents;
}

int QAnimatedListWidget::animationDuration() const
{
    return m_animationDuration;
}

void QAnimatedListWidget::setAnimationDuration(int animationDuration)
{
    m_animationDuration = animationDuration;
}

void QAnimatedListWidget::onClearAnimationFinished()
{
    while(!m_clearingItems.isEmpty())
    {
        QAnimatedListItem *item = m_clearingItems.takeAt(0);
        m_scrollAreaContents->layout()->removeWidget(item);
        delete item;
    }
}

bool QAnimatedListWidget::autoScroll() const
{
    return m_autoScroll;
}

void QAnimatedListWidget::setAutoScroll(bool autoScroll)
{
    m_autoScroll = autoScroll;
}

QAnimatedListWidget::SelectionMode QAnimatedListWidget::selectionMode() const
{
    return m_selectionMode;
}

void QAnimatedListWidget::setSelectionMode(SelectionMode selectionMode)
{
    m_selectionMode = selectionMode;
}
