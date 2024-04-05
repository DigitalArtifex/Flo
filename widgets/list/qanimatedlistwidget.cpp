#include "qanimatedlistwidget.h"
#include "../../system/settings.h"

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
    _scrollAreaContents->layout()->removeItem(_spacer);
    _scrollAreaContents->layout()->addWidget(item);
    _scrollAreaContents->layout()->addItem(_spacer);
    _items.append(item);
    connect(item, SIGNAL(animationIn_finished(QAnimatedListItem*)), this, SLOT(on_listItem_animationIn_finished(QAnimatedListItem*)));
    connect(item, SIGNAL(selected(QAnimatedListItem*)), this, SLOT(on_item_selected(QAnimatedListItem*)));
    connect(item, SIGNAL(deselected(QAnimatedListItem*)), this, SLOT(on_item_deselected(QAnimatedListItem*)));

    QString styleSheet = Settings::currentTheme();
    item->setStyleSheet(styleSheet);
    style()->polish(item);

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
    item->setDuration(1000);
    item->animateIn();
}

void QAnimatedListWidget::removeItem(QAnimatedListItem *item)
{
    if(_items.contains(item))
    {
        disconnect(item, SIGNAL(selected(QAnimatedListItem*)), this, SLOT(on_item_selected(QAnimatedListItem*)));
        disconnect(item, SIGNAL(deselected(QAnimatedListItem*)), this, SLOT(on_item_deselected(QAnimatedListItem*)));

        connect(item, SIGNAL(animationOut_finished(QAnimatedListItem*)), this, SLOT(on_listItem_animationOut_finished(QAnimatedListItem*)));

        if(isItemInViewport(item))
        item->animateOut();
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
    }
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

}

void QAnimatedListWidget::on_listItem_animationOut_finished(QAnimatedListItem *item)
{
    _scrollAreaContents->layout()->removeWidget(item);
    _items.removeAll(item);
    delete item;
}

void QAnimatedListWidget::on_listItem_animationIn_finished(QAnimatedListItem *item)
{
    item->setSelectable(true);
}

void QAnimatedListWidget::on_item_selected(QAnimatedListItem *item)
{
    if(!_selectedItems.contains(item))
        _selectedItems.append(item);
}

void QAnimatedListWidget::on_item_deselected(QAnimatedListItem *item)
{
    if(_selectedItems.contains(item))
        _selectedItems.removeAll(item);
}
