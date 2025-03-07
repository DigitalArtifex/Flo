#include "qanimatedwidget.h"

QAnimatedWidget::QAnimatedWidget(QWidget *parent)
    : QFrame{parent}
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);

    m_animationFinal = new QWidgetAnimation(this, this);
    m_animationIn = new QWidgetAnimation(this, this);
    m_animationOut = new QWidgetAnimation(this, this);

    connect(m_animationIn, SIGNAL(finished()), this, SLOT(on_animationIn_finished()));
    connect(m_animationFinal, SIGNAL(finished()), this, SLOT(on_animationFinal_finished()));
    connect(m_animationOut, SIGNAL(finished()), this, SLOT(on_animationOut_finished()));

    setLayout(m_layout);
}

QAnimatedWidget::~QAnimatedWidget()
{
    if(m_animationIn)
        m_animationIn->deleteLater();

    if(m_animationFinal)
        m_animationFinal->deleteLater();

    if(m_animationOut)
        m_animationOut->deleteLater();

    if(m_snapshotLabel)
    {
        if(m_layout)
            m_layout->removeWidget(m_snapshotLabel);

        m_snapshotLabel->deleteLater();
    }

    if(m_widget)
    {
        if(m_layout)
            m_layout->removeWidget(m_widget);

        m_widget->deleteLater();
    }

    if(m_layout)
        m_layout->deleteLater();
}

void QAnimatedWidget::animateIn()
{
    if(!m_snapshotLabel)
    {
        m_snapshotLabel = new QLabel(this);
        m_snapshotLabel->resize(size());
    }

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

    //switch to a snapshot of the actual widget to prevent performance issues
    QImage snapshot(size(), QImage::Format_ARGB32);
    snapshot.fill(Qt::transparent);

    QPainter painter(&snapshot);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    if(m_widget)
    {
        m_widget->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
        m_widget->setProperty("isAnimating", true);
    }

    m_snapshotLabel->setPixmap(QPixmap::fromImage(snapshot));
    m_snapshotLabel->resize(size());
    m_snapshotLabel->show();

    //hide after showing the snapshot to prevent flicker
    if(m_widget)
    {
        m_widget->hide();
        m_layout->removeWidget(m_widget);
    }

    m_animationIn->setDuration(m_duration);
    m_animationIn->start();
}

void QAnimatedWidget::animateOut()
{
    if(m_animationIn->isAnimating())
    {
        m_animationIn->stop();
    }

    if(!m_snapshotLabel)
    {
        m_snapshotLabel = new QLabel(this);
        m_snapshotLabel->resize(size());
    }

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

    //switch to a snapshot of the actual widget to prevent performance issues
    QImage snapshot(size(), QImage::Format_ARGB32);
    snapshot.fill(Qt::transparent);

    QPainter painter(&snapshot);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    if(m_widget)
    {
        m_widget->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
        m_widget->setProperty("isAnimating", true);
    }

    m_snapshotLabel->setPixmap(QPixmap::fromImage(snapshot));
    m_snapshotLabel->resize(size());
    m_snapshotLabel->show();

    //hide after showing the snapshot to prevent flicker
    if(m_widget)
    {
        m_widget->hide();
        m_layout->removeWidget(m_widget);
    }

    m_animationOut->setDuration(m_duration);
    m_animationOut->start();
}

QWidget *QAnimatedWidget::widget() const
{
    return m_widget;
}

void QAnimatedWidget::setWidget(QWidget *widget)
{
    if(m_widget)
    {
        m_layout->removeWidget(m_widget);
        m_widget->deleteLater();
        m_widget = nullptr;
    }

    m_widget = widget;
    m_layout->addWidget(m_widget);
}

void QAnimatedWidget::on_animationIn_finished()
{
    if(m_widget)
    {
        m_layout->addWidget(m_widget);
        m_widget->show();
    }

    if(m_snapshotLabel)
        m_snapshotLabel->hide();

    if(m_widget)
        m_widget->setProperty("isAnimating", false);

    emit animatedIn();
}

void QAnimatedWidget::on_animationOut_finished()
{
    if(!m_animationFinal)
    {
        if(m_snapshotLabel)
            m_snapshotLabel->hide();

        if(m_widget)
            m_widget->show();

        emit animatedOut();
    }
    else
        m_animationFinal->start();
}

void QAnimatedWidget::on_animationFinal_finished()
{
    if(m_snapshotLabel)
    {
        m_snapshotLabel->hide();
        m_snapshotLabel->deleteLater();
        m_snapshotLabel = nullptr;
    }

    if(m_widget)
        m_widget->show();

    emit animatedOut();
}

void QAnimatedWidget::setWidthOut(qint32 widthOut)
{
    m_widthOut = widthOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Width));
}

void QAnimatedWidget::setStyleSheet(const QString &styleSheet)
{
    if(m_widget)
        m_widget->setStyleSheet(styleSheet);

    QWidget::setStyleSheet(styleSheet);
}

void QAnimatedWidget::resizeEvent(QResizeEvent *event)
{
    if(m_snapshotLabel)
        m_snapshotLabel->resize(event->size());

    QFrame::resizeEvent(event);
}

void QAnimatedWidget::setWidthIn(qint32 widthIn)
{
    m_widthIn = widthIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Width));
}

void QAnimatedWidget::setHeightOut(qint32 heightOut)
{
    m_heightOut = heightOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Height));
}

void QAnimatedWidget::setHeightIn(qint32 heightIn)
{
    m_heightIn = heightIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Height));
}

void QAnimatedWidget::setDuration(qint32 duration)
{
    m_duration = duration;
}

void QAnimatedWidget::setOpacityOut(qreal opacityOut)
{
    m_opacityOut = opacityOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedWidget::setOpacityIn(qreal opacityIn)
{
    m_opacityIn = opacityIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Opacity));
}

void QAnimatedWidget::setBlurOut(qreal blurOut)
{
    m_blurOut = blurOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedWidget::setBlurIn(qreal blurIn)
{
    m_blurIn = blurIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Blur));
}

void QAnimatedWidget::setPositionOut(QPoint positionOut)
{
    m_positionOut = positionOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedWidget::setPositionIn(QPoint positionIn)
{
    m_positionIn = positionIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Position));
}

void QAnimatedWidget::setGeometryOut(const QRect &geometryOut)
{
    m_geometryOut = geometryOut;
    m_animationOut->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Geometry));
}

void QAnimatedWidget::setGeometryIn(const QRect &geometryIn)
{
    m_geometryIn = geometryIn;
    m_animationIn->setAnimationType(QWidgetAnimation::AnimationType(m_animationIn->animationType() | QWidgetAnimation::Geometry));
}
