#include "qanimatedlistwidget.h"
#include "../../system/settings.h"

#include <QThread>

QAnimatedListWidget::QAnimatedListWidget(QWidget *parent) :
    QScrollArea(parent)
{
    _scrollAreaContents = new QWidget(this);
    _scrollAreaContents->setLayout(new QVBoxLayout(_scrollAreaContents));
    _scrollAreaContents->setLayoutDirection(Qt::LayoutDirectionAuto);
    _scrollAreaContents->layout()->setContentsMargins(0,4,0,4);
    _scrollAreaContents->layout()->setSpacing(0);
    setLayoutDirection(Qt::LayoutDirectionAuto);

    _spacer = new QSpacerItem(20,20,QSizePolicy::Fixed,QSizePolicy::Expanding);
    _scrollAreaContents->layout()->addItem(_spacer);
    _scrollAreaContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setWidget(_scrollAreaContents);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setWidgetResizable(true);

    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "List"));
}

void QAnimatedListWidget::addItem(QAnimatedListItem *item)
{
    if(_selectionMode == SingleSelect | _selectionMode == MultiSelect)
    {
        item->setSelected(false, false);
        item->setSelectable(true);
    }
    else if(_selectionMode == NoSelect)
    {
        item->setSelected(false, false);
        item->setSelectable(false);

        return;
    }

    _scrollAreaContents->layout()->removeItem(_spacer);
    _scrollAreaContents->layout()->addWidget(item);
    _scrollAreaContents->layout()->addItem(_spacer);

    connect(item, SIGNAL(animationIn_finished(QAnimatedListItem*)), this, SLOT(on_listItem_animationIn_finished(QAnimatedListItem*)));
    connect(item, SIGNAL(selected(QAnimatedListItem*)), this, SLOT(on_item_selected(QAnimatedListItem*)));
    connect(item, SIGNAL(deselected(QAnimatedListItem*)), this, SLOT(on_item_deselected(QAnimatedListItem*)));

    QString styleSheet = Settings::currentTheme();
    item->setStyleSheet(styleSheet);
    style()->polish(item);

    qint32 ypos = ((0 + (item->height() * _items.count())) + (_scrollAreaContents->layout()->contentsMargins().top()));

    item->setPositionIn(QPoint(0, ypos));
    item->setPositionOut(QPoint(width(),ypos));
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(100 + (50 * _items.count()));

    _items.append(item);
    item->animateIn();
}

void QAnimatedListWidget::addWidget(QWidget *widget)
{
    QAnimatedListItem *item = new QAnimatedListItem(this);
    item->setWidget(widget);
    _items.append(item);

    _scrollAreaContents->layout()->removeItem(_spacer);
    _scrollAreaContents->layout()->addWidget(item);
    _scrollAreaContents->layout()->addItem(_spacer);

    connect(item, SIGNAL(animationIn_finished(QAnimatedListItem*)), this, SLOT(on_listItem_animationIn_finished(QAnimatedListItem*)));
    connect(item, SIGNAL(selected(QAnimatedListItem*)), this, SLOT(on_item_selected(QAnimatedListItem*)));
    connect(item, SIGNAL(deselected(QAnimatedListItem*)), this, SLOT(on_item_deselected(QAnimatedListItem*)));

    item->setPositionIn(item->pos());
    item->setPositionOut(QPoint(width(),item->pos().y()));
    item->setBlurIn(0);
    item->setBlurOut(1);
    item->setDuration(100);
    item->animateIn();
}

void QAnimatedListWidget::removeItem(QAnimatedListItem *item)
{
    if(_items.contains(item))
    {
        _scrollAreaContents->layout()->removeWidget(item);

        if(isItemInViewport(item))
        {
            connect(item, SIGNAL(animationOut_finished(QAnimatedListItem*)), this, SLOT(on_listItem_animationOut_finished(QAnimatedListItem*)));
            item->animateOut();
        }
        else
            on_listItem_animationOut_finished(item);
    }
}

void QAnimatedListWidget::removeWidget(QWidget *widget)
{
    for(int i = 0; i < _items.count(); i++)
    {
        if(_items[i]->widget() == widget)
        {
            removeItem(_items[i]);
            break;
        }
    }
}

void QAnimatedListWidget::clear()
{
    for(int i = 0; i < _items.count(); i++)
    {
        removeItem(_items[i]);

        //delete _items[i];
    }

    _selectedItems.clear();
    _items.clear();
}

void QAnimatedListWidget::setStyleSheet(QString styleSheet)
{
    QScrollArea::setStyleSheet(styleSheet);
    _scrollAreaContents->setStyleSheet(styleSheet);

    for(int i = 0; i < _items.count(); i++)
    {
        _items[i]->setStyleSheet(styleSheet);
        style()->polish(_items[i]);
    }
}

bool QAnimatedListWidget::isItemInViewport(QAnimatedListItem *item)
{
    bool startsInViewport = false;
    bool endsInViewport = false;

    if(item->y() >= verticalScrollBar()->value())
    {
        if(item->y()  <= (height() + verticalScrollBar()->value()))
            startsInViewport = true;
    }

    if((item->y() + item->height()) <= (height() + verticalScrollBar()->value()))
        endsInViewport = true;

    return (startsInViewport | endsInViewport);
}

void QAnimatedListWidget::on_listItem_animationOut_finished(QAnimatedListItem *item)
{
    _items.removeAll(item);
    delete item;
}

void QAnimatedListWidget::on_listItem_animationIn_finished(QAnimatedListItem *item)
{
    item->setSelectable(true);
}

void QAnimatedListWidget::on_item_selected(QAnimatedListItem *item)
{
    if(_selectionMode == SingleSelect)
    {
        for(int i = 0; i < _selectedItems.count(); i++)
        {
            if(item != _selectedItems[i])
                _selectedItems[i]->setSelected(false, false);
        }

        _selectedItems.clear();
        _selectedItems.append(item);
    }
    else if(_selectionMode == MultiSelect)
    {
        if(!_selectedItems.contains(item))
            _selectedItems.append(item);
    }
    else if(_selectionMode == NoSelect)
    {
        item->setSelected(false, false);
        item->setSelectable(false);

        return;
    }

    emit itemSelected(item);
}

void QAnimatedListWidget::on_item_deselected(QAnimatedListItem *item)
{
    if(_selectedItems.contains(item))
        _selectedItems.removeAll(item);

    if(_selectedItems.count() <= 0)
        emit itemSelected(nullptr);
}

QAnimatedListWidget::SelectionMode QAnimatedListWidget::selectionMode() const
{
    return _selectionMode;
}

void QAnimatedListWidget::setSelectionMode(SelectionMode selectionMode)
{
    _selectionMode = selectionMode;
}
