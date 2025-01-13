#include "qanimatedlistitem.h"

QAnimatedListItem::QAnimatedListItem(QWidget *parent)
    : QFrame{parent}
{
    m_animationFinal = new QWidgetAnimation(this, parent);
    m_animationIn = new QWidgetAnimation(this, parent);
    m_animationOut = new QWidgetAnimation(this, parent);

    connect(m_animationIn, SIGNAL(finished()), this, SLOT(on_animationIn_finished()));
    connect(m_animationOut, SIGNAL(finished()), this, SLOT(on_animationOut_finished()));

    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ListItem" ));
}

void QAnimatedListItem::animateIn()
{
    if(m_animationIn->hasAnimationType(QWidgetAnimation::Position))
    {
        m_animationIn->setStartPosition(m_positionOut);
        m_animationIn->setEndPosition(m_positionIn);
    }

    if(m_animationIn->hasAnimationType(QWidgetAnimation::Opacity))
    {
        m_animationIn->setStartOpacity(m_opacityOut);
        m_animationIn->setEndOpacity(m_opacityIn);
    }

    if(m_animationIn->hasAnimationType(QWidgetAnimation::Geometry))
    {
        m_animationIn->setStartGeometry(m_geometryOut);
        m_animationIn->setEndGeometry(m_geometryIn);
    }

    if(m_animationIn->hasAnimationType(QWidgetAnimation::Blur))
    {
        m_animationIn->setStartBlur(m_blurOut);
        m_animationIn->setEndBlur(m_blurIn);
    }

    if(m_animationIn->hasAnimationType(QWidgetAnimation::Height))
    {
        m_animationIn->setStartHeight(m_heightOut);
        m_animationIn->setEndHeight(m_heightIn);
    }

    if(m_animationIn->hasAnimationType(QWidgetAnimation::Width))
    {
        m_animationIn->setStartWidth(m_widthOut);
        m_animationIn->setEndWidth(m_widthIn);
    }

    m_animationIn->setDuration(m_duration);
    m_animationIn->start();
}

void QAnimatedListItem::animateOut()
{
    if(m_animationOut->hasAnimationType(QWidgetAnimation::Position))
    {
        m_animationOut->setStartPosition(m_positionIn);
        m_animationOut->setEndPosition(m_positionOut);
    }

    if(m_animationOut->hasAnimationType(QWidgetAnimation::Opacity))
    {
        m_animationOut->setStartOpacity(m_opacityIn);
        m_animationOut->setEndOpacity(m_opacityOut);
    }

    if(m_animationOut->hasAnimationType(QWidgetAnimation::Geometry))
    {
        m_animationOut->setStartGeometry(m_geometryIn);
        m_animationOut->setEndGeometry(m_geometryOut);
    }

    if(m_animationOut->hasAnimationType(QWidgetAnimation::Blur))
    {
        m_animationOut->setStartBlur(m_blurIn);
        m_animationOut->setEndBlur(m_blurOut);
    }

    if(m_animationOut->hasAnimationType(QWidgetAnimation::Height))
    {
        m_animationOut->setStartHeight(m_heightIn);
        m_animationOut->setEndHeight(m_heightOut);
    }

    if(m_animationOut->hasAnimationType(QWidgetAnimation::Width))
    {
        m_animationOut->setStartWidth(m_widthIn);
        m_animationOut->setEndWidth(m_widthOut);
    }

    m_animationOut->setDuration(m_duration);
    m_animationOut->start();
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

void QAnimatedListItem::setWidget(QWidget *widget)
{
    m_widget = widget;
    setLayout(new QVBoxLayout(this));
    setLayoutDirection(Qt::LayoutDirectionAuto);
    layout()->setContentsMargins(0,4,0,4);
    layout()->setSpacing(0);
    setLayoutDirection(Qt::LayoutDirectionAuto);
    layout()->addWidget(m_widget);
}

QWidget *QAnimatedListItem::widget()
{
    return m_widget;
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
        style()->polish(this);
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
        style()->polish(this);

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

void QAnimatedListItem::on_animationIn_finished()
{
    emit animationIn_finished(this);
}

void QAnimatedListItem::on_animationOut_finished()
{
    emit animationOut_finished(this);
}

void QAnimatedListItem::setContextMenu(QMenu *menu)
{
    m_contextMenu = menu;
}

qint32 QAnimatedListItem::widthOut() const
{
    return m_widthOut;
}

void QAnimatedListItem::setWidthOut(qint32 widthOut)
{
    m_widthOut = widthOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Width));
}

qint32 QAnimatedListItem::widthIn() const
{
    return m_widthIn;
}

void QAnimatedListItem::setWidthIn(qint32 widthIn)
{
    m_widthIn = widthIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Width));
}

qint32 QAnimatedListItem::heightOut() const
{
    return m_heightOut;
}

void QAnimatedListItem::setHeightOut(qint32 heightOut)
{
    m_heightOut = heightOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Height));
}

qint32 QAnimatedListItem::heightIn() const
{
    return m_heightIn;
}

void QAnimatedListItem::setHeightIn(qint32 heightIn)
{
    m_heightIn = heightIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Height));
}

void QAnimatedListItem::setDuration(qint32 duration)
{
    m_duration = duration;
}

void QAnimatedListItem::setOpacityOut(qreal opacityOut)
{
    m_opacityOut = opacityOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedListItem::setOpacityIn(qreal opacityIn)
{
    m_opacityIn = opacityIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedListItem::setBlurOut(qreal blurOut)
{
    m_blurOut = blurOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedListItem::setBlurIn(qreal blurIn)
{
    m_blurIn = blurIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedListItem::setPositionOut(QPoint positionOut)
{
    m_positionOut = positionOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedListItem::setPositionIn(QPoint positionIn)
{
    m_positionIn = positionIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedListItem::setGeometryOut(const QRect &geometryOut)
{
    m_geometryOut = geometryOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Geometry));
}

void QAnimatedListItem::setGeometryIn(const QRect &geometryIn)
{
    m_geometryIn = geometryIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Geometry));
}
