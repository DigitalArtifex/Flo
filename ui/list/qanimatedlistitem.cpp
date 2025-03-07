#include "qanimatedlistitem.h"

QAnimatedListItem::QAnimatedListItem(QWidget *parent)
    : QFrame{parent}
{
    m_animations = new QParallelAnimationGroup(this);

    connect(m_animations, SIGNAL(finished()), this, SLOT(onAnimationFinished()));

    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ListItem" ));
}

void QAnimatedListItem::setSelectable(bool selectable)
{
    m_selectable = selectable;
}

void QAnimatedListItem::setSelected(bool select, bool trigger)
{
    if(!m_selectable)
        return;

    m_selected = select;
    setProperty("selected", select);
    style()->polish(this);

    if(trigger)
    {
        if(select)
            emit(selected(this));
        else
        {
            emit(deselected(this));
        }
    }
}

void QAnimatedListItem::on_clickTimer_timeout()
{
    if(m_pressed)
        m_longPressed = true;
}

void QAnimatedListItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    setSelected(true);
    emit doubleClicked(this);

    QWidget::mouseDoubleClickEvent(event);
}

void QAnimatedListItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_clickTimer = new QTimer(this);
        connect(m_clickTimer, SIGNAL(timeout()), this, SLOT(on_clickTimer_timeout()));

        m_clickTimer->setInterval(500);
        m_clickTimer->setSingleShot(true);
        m_clickTimer->start();

        setProperty("pressed", true);
        m_pressed = true;
        //style()->polish(this);
    }
    else if(event->button() == Qt::RightButton)
    {
        setSelected(true);

        if(m_contextMenu)
        {
            m_contextMenu->popup(event->globalPosition().toPoint());
        }
    }

    QWidget::mousePressEvent(event);
}

void QAnimatedListItem::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        this->setProperty("pressed", false);
        //style()->polish(this);

        if(m_clickTimer)
        {
            m_clickTimer->deleteLater();
            m_clickTimer = nullptr;
        }

        if(m_pressed && !m_longPressed)
        {
            m_pressed = false;
            m_longPressed = false;

            setSelected(!m_selected);
        }
        else if(m_longPressed)
        {
            m_pressed = false;
            m_longPressed = false;

            setSelected(!m_selected);

            if(m_contextMenu)
            {
                m_contextMenu->popup(event->globalPosition().toPoint());
            }
        }

    }
}

void QAnimatedListItem::onAnimationFinished()
{
    setGraphicsEffect(nullptr);
    emit animationFinished(this);
}

void QAnimatedListItem::setContextMenu(QMenu *menu)
{
    m_contextMenu = menu;
}

QWidget *QAnimatedListItem::centralWidget() const
{
    return m_centralWidget;
}

void QAnimatedListItem::setCentralWidget(QWidget *centralWidget)
{
    m_centralWidget = centralWidget;
    m_centralWidget->setParent(this);
    m_centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setLayout(new QVBoxLayout(this));
    layout()->setContentsMargins(0,0,0,0);
    layout()->setSpacing(0);
    layout()->addWidget(m_centralWidget);
}

void QAnimatedListItem::initAnimations()
{
    if(m_animations)
        delete m_animations;

    m_animations = new QParallelAnimationGroup(this);
    connect(m_animations, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
}

QParallelAnimationGroup *QAnimatedListItem::animations() const
{
    return m_animations;
}
