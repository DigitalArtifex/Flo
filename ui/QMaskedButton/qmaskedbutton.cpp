#include "qmaskedbutton.h"

QMaskedButton::QMaskedButton(QWidget *parent)
    : QWidget{parent}
{
    m_hover_animation = new QPropertyAnimation(this, "hover_opacity");
    m_hover_animation->setStartValue(0.0);
    m_hover_animation->setEndValue(1.0);
    m_hover_animation->setDuration(50);

    m_click_animation = new QPropertyAnimation(this, "click_opacity");
    m_click_animation->setStartValue(0.0);
    m_click_animation->setEndValue(1.0);
    m_click_animation->setDuration(50);
}

QMaskedButton::~QMaskedButton()
{
    if(m_clickTimer)
        m_clickTimer->deleteLater();

    if(m_hover_animation)
        m_hover_animation->deleteLater();

    if(m_click_animation)
        m_click_animation->deleteLater();
}

void QMaskedButton::on_clickTimer_timeout()
{
    if(property("pressed").toBool())
        setProperty("longPressed", true);
}

qreal QMaskedButton::hoverOpacity() const
{
    return m_hover_opacity;
}

void QMaskedButton::setHoverOpacity(qreal hover_opacity)
{
    if(hover_opacity == m_hover_opacity)
        return;

    m_hover_opacity = hover_opacity;

    if(!m_updating)
    {
        m_updating = true;
        update();
    }
}

qreal QMaskedButton::clickOpacity() const
{
    return m_click_opacity;
}

void QMaskedButton::setClickOpacity(qreal click_opacity)
{
    if(click_opacity == m_click_opacity)
        return;

    m_click_opacity = click_opacity;

    if(!m_updating)
    {
        m_updating = true;
        update();
    }
}
qreal QMaskedButton::widgetOpacity() const
{
    return m_opacity;
}

void QMaskedButton::setOpacity(qreal opacity)
{
    if(opacity == m_opacity)
        return;

    m_opacity = opacity;

    if(!m_updating)
    {
        m_updating = true;
        update();
    }
}

void QMaskedButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(isEnabled())
        emit doubleClicked(this);

    QWidget::mouseDoubleClickEvent(event);
}

void QMaskedButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && isEnabled())
    {
        if(m_click_animation->state() == QPropertyAnimation::Running)
            m_click_animation->stop();

        m_click_animation->setStartValue(m_click_opacity);
        m_click_animation->setEndValue(1.0);
        m_click_animation->start();

        setProperty("pressed", true);

        m_clickTimer = new QTimer(this);
        connect(m_clickTimer, SIGNAL(timeout()), this, SLOT(on_clickTimer_timeout()));

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
        if(m_click_animation->state() == QPropertyAnimation::Running)
            m_click_animation->stop();

        m_click_animation->setStartValue(m_click_opacity);
        m_click_animation->setEndValue(0.0);
        m_click_animation->start();

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

            emit clicked(this);
        }
        else if(property("longPressed").toBool())
        {
            setProperty("pressed", false);
            setProperty("longPressed", false);
            style()->polish(this);

            emit longPressed(this);
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
        painter.drawImage(m_pixmap.rect(), m_pixmap.toImage());
    }
    else
    {
        if(m_hover_opacity > 0)
        {
            painter.setOpacity(m_hover_opacity);
            painter.drawImage(m_hoverPixmap.rect(), m_hoverPixmap.toImage());
        }
        if(m_click_opacity > 0)
        {
            painter.setOpacity(m_click_opacity);
            painter.drawImage(m_clickPixmap.rect(), m_clickPixmap.toImage());
        }
        if(m_opacity > 0)
        {
            painter.setOpacity(m_opacity);
            painter.drawImage(m_pixmap.rect(), m_pixmap.toImage());
        }
    }

    painter.end();
    setMask(m_mask);

    QWidget::paintEvent(event);

    m_updating = false;
}

void QMaskedButton::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    m_mask = pixmap.createHeuristicMask();

    update();
}

void QMaskedButton::setHoverPixmap(const QPixmap &pixmap)
{
    m_hoverPixmap = pixmap;
    m_hoverMask = pixmap.createHeuristicMask();

    update();
}

void QMaskedButton::setClickPixmap(const QPixmap &pixmap)
{
    m_clickPixmap = pixmap;
    m_clickMask = pixmap.createHeuristicMask();

    update();
}

void QMaskedButton::enterEvent(QEnterEvent *event)
{
    if(isEnabled())
    {
        if(m_hover_animation->state() == QPropertyAnimation::Running)
            m_hover_animation->stop();

        setProperty("hover", true);
        setProperty("pressed", false);
        setProperty("longPressed", false);
        setProperty("opacity", m_hover_opacity);

        m_hover_animation->setStartValue(m_hover_opacity);
        m_hover_animation->setEndValue(1.0);
        m_hover_animation->setDuration(15);
        m_hover_animation->start();
    }

    update();

    QWidget::enterEvent(event);
}

void QMaskedButton::leaveEvent(QEvent *event)
{
    if(m_hover_animation->state() == QPropertyAnimation::Running)
        m_hover_animation->stop();

    setProperty("hover", false);
    setProperty("pressed", false);
    setProperty("longPressed", false);
    setProperty("opacity", m_hover_opacity);

    m_hover_animation->setStartValue(m_hover_opacity);
    m_hover_animation->setEndValue(0.0);
    m_hover_animation->setDuration(15);
    m_hover_animation->start();

    if(m_clickTimer)
    {
        m_clickTimer->deleteLater();
        m_clickTimer = nullptr;
    }

    update();

    QWidget::leaveEvent(event);
}
