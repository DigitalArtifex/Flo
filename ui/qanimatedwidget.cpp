#include "qanimatedwidget.h"

QAnimatedWidget::QAnimatedWidget(QWidget *parent)
    : QFrame{parent}
{
    _layout = new QGridLayout(this);
    _layout->setSpacing(0);
    _layout->setContentsMargins(0,0,0,0);

    _snapshotLabel = new QLabel(this);
    _snapshotLabel->resize(size());
    _snapshotLabel->hide();

    _animationFinal = new QWidgetAnimation(this, parent);
    _animationIn = new QWidgetAnimation(this, parent);
    _animationOut = new QWidgetAnimation(this, parent);

    connect(_animationIn, SIGNAL(finished()), this, SLOT(on_animationIn_finished()));
    connect(_animationFinal, SIGNAL(finished()), this, SLOT(on_animationFinal_finished()));
    connect(_animationOut, SIGNAL(finished()), this, SLOT(on_animationOut_finished()));

    setLayout(_layout);
}

QAnimatedWidget::~QAnimatedWidget()
{
    if(_animationIn)
        delete _animationIn;

    if(_animationFinal)
        delete _animationFinal;

    if(_animationOut)
        delete _animationOut;

    if(_snapshotLabel)
        delete _snapshotLabel;

    if(_widget)
        _widget->deleteLater();

    if(_layout)
        delete _layout;
}

void QAnimatedWidget::animateIn()
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

    //switch to a snapshot of the actual widget to prevent performance issues
    QImage snapshot(size(), QImage::Format_ARGB32);
    snapshot.fill(Qt::transparent);

    QPainter painter(&snapshot);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    if(_widget)
        _widget->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);

    _snapshotLabel->setPixmap(QPixmap::fromImage(snapshot));
    _snapshotLabel->resize(size());
    _snapshotLabel->show();

    //hide after showing the snapshot to prevent flicker
    if(_widget)
    {
        _widget->hide();
        _layout->removeWidget(_widget);
    }

    _animationIn->setDuration(_duration);
    _animationIn->start();
}

void QAnimatedWidget::animateOut()
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

    //switch to a snapshot of the actual widget to prevent performance issues
    QImage snapshot(size(), QImage::Format_ARGB32);
    snapshot.fill(Qt::transparent);

    QPainter painter(&snapshot);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    if(_widget)
        _widget->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);

    _snapshotLabel->setPixmap(QPixmap::fromImage(snapshot));
    _snapshotLabel->resize(size());
    _snapshotLabel->show();

    //hide after showing the snapshot to prevent flicker
    if(_widget)
    {
        _widget->hide();
        _layout->removeWidget(_widget);
    }

    _animationOut->setDuration(_duration);
    _animationOut->start();
}

QWidget *QAnimatedWidget::widget() const
{
    return _widget;
}

void QAnimatedWidget::setWidget(QWidget *widget)
{
    if(_widget)
    {
        _layout->removeWidget(_widget);
        delete _widget;
    }

    _widget = widget;
    _layout->addWidget(_widget);
}

void QAnimatedWidget::on_animationIn_finished()
{
    if(_widget)
    {
        _layout->addWidget(_widget);
        _widget->show();
    }

    _snapshotLabel->hide();

    emit animatedIn();
}

void QAnimatedWidget::on_animationOut_finished()
{
    if(!_animationFinal)
    {
        if(_widget)
        {
            _layout->addWidget(_widget);
            _widget->show();
        }

        _snapshotLabel->hide();

        emit animatedOut();
    }
    else
        _animationFinal->start();
}

void QAnimatedWidget::on_animationFinal_finished()
{
    if(_widget)
    {
        _layout->addWidget(_widget);
        _widget->show();
    }

    _snapshotLabel->hide();

    emit animatedOut();
}

void QAnimatedWidget::setWidthOut(qint32 widthOut)
{
    _widthOut = widthOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Width));
}

void QAnimatedWidget::setStyleSheet(QString styleSheet)
{
    if(_widget)
        _widget->setStyleSheet(styleSheet);
}

void QAnimatedWidget::resizeEvent(QResizeEvent *event)
{
    if(_snapshotLabel)
        _snapshotLabel->resize(event->size());

    QFrame::resizeEvent(event);
}

void QAnimatedWidget::setWidthIn(qint32 widthIn)
{
    _widthIn = widthIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Width));
}

void QAnimatedWidget::setHeightOut(qint32 heightOut)
{
    _heightOut = heightOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Height));
}

void QAnimatedWidget::setHeightIn(qint32 heightIn)
{
    _heightIn = heightIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Height));
}

void QAnimatedWidget::setDuration(qint32 duration)
{
    _duration = duration;
}

void QAnimatedWidget::setOpacityOut(qreal opacityOut)
{
    _opacityOut = opacityOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedWidget::setOpacityIn(qreal opacityIn)
{
    _opacityIn = opacityIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedWidget::setBlurOut(qreal blurOut)
{
    _blurOut = blurOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedWidget::setBlurIn(qreal blurIn)
{
    _blurIn = blurIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedWidget::setPositionOut(QPoint positionOut)
{
    _positionOut = positionOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedWidget::setPositionIn(QPoint positionIn)
{
    _positionIn = positionIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedWidget::setGeometryOut(const QRect &geometryOut)
{
    _geometryOut = geometryOut;
    _animationOut->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Geometry));
}

void QAnimatedWidget::setGeometryIn(const QRect &geometryIn)
{
    _geometryIn = geometryIn;
    _animationIn->setAnimationType(QWidgetAnimation::AnimationType(_animationIn->animationType() | QWidgetAnimation::Geometry));
}
