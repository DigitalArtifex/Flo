#include "qanimatedlistwidget.h"
#include "../../system/settings.h"

#include <QThread>

QAnimatedListWidget::QAnimatedListWidget(QWidget *parent) :
    QScrollArea(parent)
{
    m_scrollAreaContents = new QWidget(this);
    m_scrollAreaContents->setLayout(new QVBoxLayout(m_scrollAreaContents));
    m_scrollAreaContents->setLayoutDirection(Qt::LayoutDirectionAuto);
    m_scrollAreaContents->layout()->setContentsMargins(0,4,0,4);
    m_scrollAreaContents->layout()->setSpacing(0);

    m_spacer = new QSpacerItem(20,20,QSizePolicy::Fixed,QSizePolicy::Expanding);

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
}

void QAnimatedListWidget::addItem(QAnimatedListItem *item)
{
    if(m_emptyListItem)
    {
        m_scrollAreaContents->layout()->removeWidget(m_emptyListItem);
        delete m_emptyListItem;
        m_emptyListItem = nullptr;
    }

    if(m_selectionMode == SingleSelect | m_selectionMode == MultiSelect)
    {
        item->setSelected(false, false);
        item->setSelectable(true);
    }
    else if(m_selectionMode == NoSelect)
    {
        item->setSelected(false, false);
        item->setSelectable(false);

        return;
    }

    m_scrollAreaContents->layout()->removeItem(m_spacer);
    m_scrollAreaContents->layout()->addWidget(item);
    m_scrollAreaContents->layout()->addItem(m_spacer);

    connect(item, SIGNAL(animationIn_finished(QAnimatedListItem*)), this, SLOT(on_listItem_animationIn_finished(QAnimatedListItem*)));
    connect(item, SIGNAL(selected(QAnimatedListItem*)), this, SLOT(on_item_selected(QAnimatedListItem*)));
    connect(item, SIGNAL(deselected(QAnimatedListItem*)), this, SLOT(on_item_deselected(QAnimatedListItem*)));

    QString styleSheet = Settings::currentTheme();
    item->setStyleSheet(styleSheet);
    style()->polish(item);

    m_items.append(item);
    item->animateIn();
}

void QAnimatedListWidget::addWidget(QWidget *widget)
{
    QAnimatedListItem *item = new QAnimatedListItem(this);
    item->setWidget(widget);
    m_items.append(item);

    m_scrollAreaContents->layout()->removeItem(m_spacer);
    m_scrollAreaContents->layout()->addWidget(item);
    m_scrollAreaContents->layout()->addItem(m_spacer);

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
    if(m_items.contains(item))
    {
        m_scrollAreaContents->layout()->removeWidget(item);

        if(!isItemInViewport(item))
            item->setDuration(1);

        connect(item, SIGNAL(animationOut_finished(QAnimatedListItem*)), this, SLOT(on_listItem_animationOut_finished(QAnimatedListItem*)));
        item->animateOut();
    }
}

void QAnimatedListWidget::removeWidget(QWidget *widget)
{
    for(int i = 0; i < m_items.count(); i++)
    {
        if(m_items[i]->widget() == widget)
        {
            removeItem(m_items[i]);
            break;
        }
    }
}

void QAnimatedListWidget::clear()
{
    for(int i = 0; i < m_items.count(); i++)
    {
        removeItem(m_items[i]);

        //delete m_items[i];
    }

    m_selectedItems.clear();
    m_items.clear();
}

void QAnimatedListWidget::setStyleSheet(QString styleSheet)
{
    QScrollArea::setStyleSheet(styleSheet);
    m_scrollAreaContents->setStyleSheet(styleSheet);

    for(int i = 0; i < m_items.count(); i++)
    {
        m_items[i]->setStyleSheet(styleSheet);
        style()->polish(m_items[i]);
    }
}

void QAnimatedListWidget::setAnimationSlide(QAnimatedListItem *item)
{
    qint32 ypos = ((0 + (item->height() * m_items.count())) + (m_scrollAreaContents->layout()->contentsMargins().top()));
    ypos += m_scrollAreaContents->layout()->spacing() * m_items.count();

    item->setPositionIn(QPoint(m_scrollAreaContents->layout()->contentsMargins().left(), ypos));
    item->setPositionOut(QPoint(width(),ypos));
    item->setOpacityIn(1);
    item->setOpacityOut(0);
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
    m_items.removeAll(item);
    item->deleteLater();

    if(m_items.isEmpty())
    {
        if(!m_emptyListItem)
            m_emptyListItem = new QAnimatedEmptyListItem(this);

        if(!m_emptyText.isEmpty())
            m_emptyListItem->setText(m_emptyText);

        if(!m_emptyPixmap.isNull())
            m_emptyListItem->setIcon(m_emptyPixmap);

        m_emptyListItem->setFixedSize(size());
        m_emptyListItem->raise();
    }
}

void QAnimatedListWidget::on_listItem_animationIn_finished(QAnimatedListItem *item)
{
    item->setSelectable(true);
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
        m_selectedItems.removeAll(item);

    if(m_selectedItems.count() <= 0)
        emit itemSelected(nullptr);
}

void QAnimatedListWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    if(m_emptyListItem != nullptr)
        m_emptyListItem->setFixedSize(event->size());
}

QAnimatedListWidget::SelectionMode QAnimatedListWidget::selectionMode() const
{
    return m_selectionMode;
}

void QAnimatedListWidget::setSelectionMode(SelectionMode selectionMode)
{
    m_selectionMode = selectionMode;
}
