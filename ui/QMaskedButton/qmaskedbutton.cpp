#include "qmaskedbutton.h"

QMaskedButton::QMaskedButton(QWidget *parent)
    : QWidget{parent}
{
    m_hoverAnimation = new QPropertyAnimation(this, "hoverOpacity");
    m_hoverAnimation->setStartValue(0.0);
    m_hoverAnimation->setEndValue(1.0);
    m_hoverAnimation->setDuration(100);

    m_clickAnimation = new QPropertyAnimation(this, "clickOpacity");
    m_clickAnimation->setStartValue(0.0);
    m_clickAnimation->setEndValue(1.0);
    m_clickAnimation->setDuration(100);

    m_pixmapAnimation = new QPropertyAnimation(this, "opacity");
    m_pixmapAnimation->setStartValue(1.0);
    m_pixmapAnimation->setEndValue(0.0);
    m_pixmapAnimation->setDuration(100);
}

QMaskedButton::~QMaskedButton()
{
    if(m_clickTimer)
        delete m_clickTimer;

    if(m_hoverAnimation)
        delete m_hoverAnimation;

    if(m_clickAnimation)
        delete m_clickAnimation;
}

void QMaskedButton::onClickTimerTimeout()
{
    if(property("pressed").toBool())
        setProperty("longPressed", true);
}

void QMaskedButton::setOpacity(qreal opacity)
{
    if (qFuzzyCompare(m_opacity, opacity))
        return;
    m_opacity = opacity;

    update();
}

void QMaskedButton::setClickOpacity(qreal clickOpacity)
{
    if (qFuzzyCompare(m_clickOpacity, clickOpacity))
        return;
    m_clickOpacity = clickOpacity;

    update();
}

void QMaskedButton::setHoverOpacity(qreal hoverOpacity)
{
    if (qFuzzyCompare(m_hoverOpacity, hoverOpacity))
        return;
    m_hoverOpacity = hoverOpacity;

    update();
}

void QMaskedButton::setClickPixmap(const QPixmap &clickPixmap)
{
    if (m_clickPixmap.toImage() == clickPixmap.toImage())
        return;

    m_clickPixmap = clickPixmap;
    emit clickPixmapChanged();

    update();
}

void QMaskedButton::setHoverPixmap(const QPixmap &hoverPixmap)
{
    if (m_hoverPixmap.toImage() == hoverPixmap.toImage())
        return;

    m_hoverPixmap = hoverPixmap;
    emit hoverPixmapChanged();

    update();
}

void QMaskedButton::setPixmap(const QPixmap &pixmap)
{
    if (m_pixmap.toImage() == pixmap.toImage())
        return;

    m_pixmap = pixmap;

    setMask(m_pixmap.createHeuristicMask());
    emit pixmapChanged();

    update();
}

void QMaskedButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(isEnabled())
    {
        emit doubleClicked();
        emit doubleClicked(this);
    }

    QWidget::mouseDoubleClickEvent(event);
}

void QMaskedButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && isEnabled())
    {
        if(m_clickAnimation->state() == QPropertyAnimation::Running)
            m_clickAnimation->stop();
        if(m_hoverAnimation->state() == QPropertyAnimation::Running)
            m_hoverAnimation->stop();

        m_clickAnimation->setStartValue(m_clickOpacity);
        m_clickAnimation->setEndValue(1.0);
        m_clickAnimation->start();

        m_hoverAnimation->setStartValue(m_hoverOpacity);
        m_hoverAnimation->setEndValue(0.0);
        m_hoverAnimation->start();

        setProperty("pressed", true);

        m_clickTimer = new QTimer(this);
        connect(m_clickTimer, SIGNAL(timeout()), this, SLOT(onClickTimerTimeout()));

        m_clickTimer->setInterval(500);
        m_clickTimer->setSingleShot(true);
        m_clickTimer->start();
    }

    QWidget::mousePressEvent(event);
}

void QMaskedButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && isEnabled())
    {
        if(m_clickAnimation->state() == QPropertyAnimation::Running)
            m_clickAnimation->stop();
        if(m_hoverAnimation->state() == QPropertyAnimation::Running)
            m_hoverAnimation->stop();

        m_clickAnimation->setStartValue(m_clickOpacity);
        m_clickAnimation->setEndValue(0.0);
        m_clickAnimation->start();

        m_hoverAnimation->setStartValue(m_hoverOpacity);
        m_hoverAnimation->setEndValue(1.0);
        m_hoverAnimation->start();

        if(m_clickTimer)
        {
            m_clickTimer->deleteLater();
            m_clickTimer = nullptr;
        }

        if(property("pressed").toBool() && !property("longPressed").toBool())
        {
            setProperty("pressed", false);
            setProperty("longPressed", false);
            style()->polish(this);

            emit clicked();
            emit clicked(this);
        }
        else if(property("longPressed").toBool())
        {
            setProperty("pressed", false);
            setProperty("longPressed", false);
            style()->polish(this);

            emit longClicked();
            emit longClicked(this);
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void QMaskedButton::paintEvent(QPaintEvent *event)
{
    QImage image(size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter;

    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::LosslessImageRendering);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(QRect(), image);

    if(!isEnabled())
    {
        painter.setOpacity(0.5);
        painter.drawPixmap(m_pixmap.rect(), m_pixmap);
    }
    else
    {
        painter.setOpacity(m_opacity);
        painter.drawPixmap(m_pixmap.rect(), m_pixmap);
        painter.setOpacity(m_hoverOpacity);
        painter.drawPixmap(m_hoverPixmap.rect(), m_hoverPixmap);
        painter.setOpacity(m_clickOpacity);
        painter.drawPixmap(m_clickPixmap.rect(), m_clickPixmap);
    }

    painter.end();

    QWidget::paintEvent(event);
}

void QMaskedButton::enterEvent(QEnterEvent *event)
{
    if(isEnabled())
    {
        if(m_hoverAnimation->state() == QPropertyAnimation::Running)
            m_hoverAnimation->stop();
        if(m_pixmapAnimation->state() == QPropertyAnimation::Running)
            m_pixmapAnimation->stop();

        setProperty("hover", true);
        setProperty("pressed", false);
        setProperty("longPressed", false);

        m_hoverAnimation->setStartValue(m_hoverOpacity);
        m_hoverAnimation->setEndValue(1.0);
        m_hoverAnimation->start();

        m_pixmapAnimation->setStartValue(m_opacity);
        m_pixmapAnimation->setEndValue(0.0);
        m_pixmapAnimation->start();
    }

    update();

    QWidget::enterEvent(event);
}

void QMaskedButton::leaveEvent(QEvent *event)
{
    if(m_hoverAnimation->state() == QPropertyAnimation::Running)
        m_hoverAnimation->stop();
    if(m_pixmapAnimation->state() == QPropertyAnimation::Running)
        m_pixmapAnimation->stop();

    setProperty("hover", false);
    setProperty("pressed", false);
    setProperty("longPressed", false);

    m_hoverAnimation->setStartValue(m_hoverOpacity);
    m_hoverAnimation->setEndValue(0.0);
    m_hoverAnimation->start();

    m_pixmapAnimation->setStartValue(m_opacity);
    m_pixmapAnimation->setEndValue(1.0);
    m_pixmapAnimation->start();

    if(m_clickTimer)
    {
        m_clickTimer->deleteLater();
        m_clickTimer = nullptr;
    }

    update();

    QWidget::leaveEvent(event);
}
