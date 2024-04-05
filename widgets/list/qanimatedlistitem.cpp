#include "qanimatedlistitem.h"

QAnimatedListItem::QAnimatedListItem(QWidget *parent)
    : QFrame{parent}
{
    _animationFinal = new QWidgetAnimation(this, parent);
    _animationIn = new QWidgetAnimation(this, parent);
    _animationOut = new QWidgetAnimation(this, parent);

    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ListItem" ));
}

void QAnimatedListItem::animateIn()
{
    if(_animationIn->hasAnimationType(QWidgetAnimation::Position))
    {
        _animationIn->setStartPosition(_positionOut);
        _animationIn->setEndPosition(_positionIn);
    }

    if(_animationIn->hasAnimationType(QWidgetAnimation::Opacity))
    {
        _animationIn->setStartOpacity(_opacityOut);
        _animationIn->setEndOpacity(_opacityIn);
    }

    if(_animationIn->hasAnimationType(QWidgetAnimation::Geometry))
    {
        _animationIn->setStartGeometry(_geometryOut);
        _animationIn->setEndGeometry(_geometryIn);
    }

    if(_animationIn->hasAnimationType(QWidgetAnimation::Blur))
    {
        _animationIn->setStartBlur(_blurOut);
        _animationIn->setEndBlur(_blurIn);
    }

    if(_animationIn->hasAnimationType(QWidgetAnimation::Height))
    {
        _animationIn->setStartHeight(_heightOut);
        _animationIn->setEndHeight(_heightIn);
    }

    if(_animationIn->hasAnimationType(QWidgetAnimation::Width))
    {
        _animationIn->setStartWidth(_widthOut);
        _animationIn->setEndWidth(_widthIn);
    }

    _animationIn->setDuration(_duration);
    _animationIn->start();
}

void QAnimatedListItem::animateOut()
{
    if(_animationOut->hasAnimationType(QWidgetAnimation::Position))
    {
        _animationOut->setStartPosition(_positionIn);
        _animationOut->setEndPosition(_positionOut);
    }

    if(_animationOut->hasAnimationType(QWidgetAnimation::Opacity))
    {
        _animationOut->setStartOpacity(_opacityIn);
        _animationOut->setEndOpacity(_opacityOut);
    }

    if(_animationOut->hasAnimationType(QWidgetAnimation::Geometry))
    {
        _animationOut->setStartGeometry(_geometryIn);
        _animationOut->setEndGeometry(_geometryOut);
    }

    if(_animationOut->hasAnimationType(QWidgetAnimation::Blur))
    {
        _animationOut->setStartBlur(_blurIn);
        _animationOut->setEndBlur(_blurOut);
    }

    if(_animationOut->hasAnimationType(QWidgetAnimation::Height))
    {
        _animationOut->setStartHeight(_heightIn);
        _animationOut->setEndHeight(_heightOut);
    }

    if(_animationOut->hasAnimationType(QWidgetAnimation::Width))
    {
        _animationOut->setStartWidth(_widthIn);
        _animationOut->setEndWidth(_widthOut);
    }

    _animationOut->setDuration(_duration);
    _animationOut->start();
}

void QAnimatedListItem::setSelectable(bool selectable)
{
    _selectable = selectable;
}

void QAnimatedListItem::setSelected(bool select)
{
    if(!_selectable)
        return;

    _selected = select;
    setProperty("selected", select);

    if(select)
        emit(selected(this));
    else
        emit(deselected(this));
}

void QAnimatedListItem::setWidget(QWidget *widget)
{
    _widget = widget;
    setLayout(new QVBoxLayout(this));
    setLayoutDirection(Qt::LayoutDirectionAuto);
    layout()->setContentsMargins(0,4,0,4);
    layout()->setSpacing(0);
    setLayoutDirection(Qt::LayoutDirectionAuto);
    layout()->addWidget(_widget);
}

QWidget *QAnimatedListItem::widget()
{
    return _widget;
}

void QAnimatedListItem::on_clickTimer_timeout()
{
    if(_pressed)
        _longPressed = true;
}

void QAnimatedListItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _clickTimer = new QTimer(this);
        _clickTimer->setInterval(500);
        _clickTimer->setSingleShot(true);
        connect(_clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
        _clickTimer->start();
        setProperty("pressed", true);
        _pressed = true;
        style()->polish(this);
        qDebug() << "Pressed";
    }
}

void QAnimatedListItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->setProperty("pressed", false);
        this->style()->polish(this);
        qDebug() << "Released";

        if(this->_clickTimer != nullptr)
        {
            _clickTimer->stop();
            disconnect(_clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
            delete _clickTimer;
            _clickTimer = nullptr;
        }

        if(_pressed && !_longPressed)
        {
            _pressed = false;
            _longPressed = false;
            setSelected(true);
        }
        else if(_longPressed)
        {
            _pressed = false;
            _longPressed = false;
            emit longPressed(this);
        }
    }
}

qint32 QAnimatedListItem::widthOut() const
{
    return _widthOut;
}

void QAnimatedListItem::setWidthOut(qint32 widthOut)
{
    _widthOut = widthOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Width));
}

qint32 QAnimatedListItem::widthIn() const
{
    return _widthIn;
}

void QAnimatedListItem::setWidthIn(qint32 widthIn)
{
    _widthIn = widthIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Width));
}

qint32 QAnimatedListItem::heightOut() const
{
    return _heightOut;
}

void QAnimatedListItem::setHeightOut(qint32 heightOut)
{
    _heightOut = heightOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Height));
}

qint32 QAnimatedListItem::heightIn() const
{
    return _heightIn;
}

void QAnimatedListItem::setHeightIn(qint32 heightIn)
{
    _heightIn = heightIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Height));
}

void QAnimatedListItem::setDuration(qint32 duration)
{
    _duration = duration;
}

void QAnimatedListItem::setOpacityOut(qreal opacityOut)
{
    _opacityOut = opacityOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedListItem::setOpacityIn(qreal opacityIn)
{
    _opacityIn = opacityIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedListItem::setBlurOut(qreal blurOut)
{
    _blurOut = blurOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedListItem::setBlurIn(qreal blurIn)
{
    _blurIn = blurIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedListItem::setPositionOut(QPoint positionOut)
{
    _positionOut = positionOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedListItem::setPositionIn(QPoint positionIn)
{
    _positionIn = positionIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedListItem::setGeometryOut(const QRect &geometryOut)
{
    _geometryOut = geometryOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Geometry));
}

void QAnimatedListItem::setGeometryIn(const QRect &geometryIn)
{
    _geometryIn = geometryIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Geometry));
}
