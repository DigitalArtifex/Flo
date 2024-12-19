#include "circularprogressbar.h"

#include "../system/settings.h"

qreal CircularProgressBar::progress() const
{
    return m_progress;
}

void CircularProgressBar::setProgress(qreal progress)
{
    if (qFuzzyCompare(m_progress, progress))
        return;

    m_progress = progress;
    update();

    emit progressChanged();
}

void CircularProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter;

    QPixmap pixmap;

    QSize size = m_iconSize;

    qreal x = 10;
    qreal y = 10;

    //qss/qproperty overrides
    if(property("icon-right").isValid())
        x -= property("icon-right").toInt();
    if(property("icon-left").isValid())
        x += property("icon-left").toInt();

    if(property("icon-top").isValid())
        y += property("icon-top").toInt();
    if(property("icon-bottom").isValid())
        y -= property("icon-bottom").toInt();

    if(property("icon-size").isValid())
        size = property("icon-size").toSize();

    if((m_iconAlignment & Qt::AlignHCenter) == Qt::AlignHCenter)
        x = (width() / 2) - (size.width() / 2);

    else if((m_iconAlignment & Qt::AlignLeft) == Qt::AlignLeft)
        x = 10;

    else if((m_iconAlignment & Qt::AlignRight) == Qt::AlignRight)
        x = (width() - size.width()) - 10;

    if((m_iconAlignment & Qt::AlignVCenter) == Qt::AlignVCenter)
        y = (height() / 2) - (size.height() / 2);

    else if((m_iconAlignment & Qt::AlignTop) == Qt::AlignTop)
        y = 10;

    else if((m_iconAlignment & Qt::AlignBottom) == Qt::AlignBottom)
        y = (height() - size.height()) - 10;

    if(isEnabled())
        pixmap = (m_icon.pixmap(size, QIcon::Normal, QIcon::On));
    else
        pixmap = (m_icon.pixmap(size, QIcon::Disabled, QIcon::On));

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(QRect(x, y, size.width(), size.height()), pixmap);

    painter.translate(4, 4);
    QPen pen, pen2;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(m_backgroundColor);
    pen.setWidth(m_pathWidth);
    pen2.setWidth(m_pathWidth + 4);
    pen2.setColor(m_foregroundColor);
    pen2.setCapStyle(Qt::FlatCap);

    //draw background
    painter.setPen(pen2);
    painter.drawArc(QRectF(m_paddingX, m_paddingY, m_pathRadius - m_pathWidth, m_pathRadius - m_pathWidth), 225 * 16, (-270*16));

    //draw filler
    painter.setPen(pen);
    painter.drawArc(QRectF(m_paddingX, m_paddingY, m_pathRadius - m_pathWidth, m_pathRadius - m_pathWidth), 225 * 16, ((270*16) * m_progress) * -1);

    //painter.translate(0,0);

    qreal fontScale = (m_fontSize * (width() / 100));

    QFont font(Settings::digitalFontFamily());
    font.setPointSize(fontScale);
    QFontMetrics fontMetrics(font);

    QString text;

    if(m_mode == Percent)
        text = QString::number(m_progress * 100.00, 'f', 2) + QString("%");
    else if(m_mode == Temperature)
        text = QString::number(m_displayedValue, 'f', 2) + QString("°");
    else
        text = QString::number(m_displayedValue, 'f', 2);

    qreal textWidth = fontMetrics.horizontalAdvance(text);

    x = 0, y = 0;

    //Get true center
    x = width() / 2;
    x -= textWidth / 2;

    if(m_mode != Temperature)
        x -= 3;

    y = (height()/2);

    painter.setFont(font);
    painter.drawText(QPoint(x,y),text);
    painter.end();

    QWidget::paintEvent(event);
}

void CircularProgressBar::resizeEvent(QResizeEvent *event)
{
    if(this->width() > this->height())
    {
        m_paddingX = this->width() - this->height();
        m_paddingX /= 2;
        m_paddingY = m_pathWidth / 2;
        m_pathRadius = this->height() - m_pathWidth;
    }
    else
    {
        m_paddingY = this->height() - this->width();
        m_paddingY /= 2;
        m_paddingY += m_pathWidth / 2;
        m_paddingX = m_pathWidth / 2;
        m_pathRadius = this->width() - m_pathWidth;
    }
}

qreal CircularProgressBar::displayedValue() const
{
    return m_displayedValue;
}

void CircularProgressBar::setDisplayedValue(qreal displayedValue)
{
    if (qFuzzyCompare(m_displayedValue, displayedValue))
        return;

    m_displayedValue = displayedValue;
    emit displayedValueChanged();
}

qreal CircularProgressBar::value() const
{
    return m_value;
}

void CircularProgressBar::setValue(qreal value)
{
    if (qFuzzyCompare(m_value, value))
        return;

    if(value < m_minimum)
        value = m_minimum;
    else if(value > m_maximum)
        value = m_maximum;

    m_value = value;

    if(m_animationsEnabled)
    {
        if(m_animationGroup->state() == QParallelAnimationGroup::Running)
            m_animationGroup->stop();

        m_progressAnimation->setStartValue(m_progress);
        m_progressAnimation->setEndValue(m_value / m_maximum);

        m_displayedValueAnimation->setStartValue(m_displayedValue);
        m_displayedValueAnimation->setEndValue(m_value);

        m_animationGroup->start();
    }
    else
    {
        setProgress(m_value / m_maximum);
        setDisplayedValue(m_value);
    }

    emit valueChanged();
}

qreal CircularProgressBar::maximum() const
{
    return m_maximum;
}

void CircularProgressBar::setMaximum(qreal maximum)
{
    if (qFuzzyCompare(m_maximum, maximum))
        return;

    m_maximum = maximum;

    if(m_minimum == m_maximum)
        m_maximum += 1.0;

    emit maximumChanged();
}

qreal CircularProgressBar::minimum() const
{
    return m_minimum;
}

void CircularProgressBar::setMinimum(qreal minimum)
{
    if (qFuzzyCompare(m_minimum, minimum))
        return;
    m_minimum = minimum;
    emit minimumChanged();
}

QIcon CircularProgressBar::icon() const
{
    return m_icon;
}

void CircularProgressBar::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
    emit iconChanged();
}

QSize CircularProgressBar::iconSize() const
{
    return m_iconSize;
}

void CircularProgressBar::setIconSize(const QSize &iconSize)
{
    if (m_iconSize == iconSize)
        return;
    m_iconSize = iconSize;
    emit iconSizeChanged();
}

qreal CircularProgressBar::fontSize() const
{
    return m_fontSize;
}

void CircularProgressBar::setFontSize(qreal fontSize)
{
    if (qFuzzyCompare(m_fontSize, fontSize))
        return;
    m_fontSize = fontSize;
    emit fontSizeChanged();
}

QColor CircularProgressBar::foregroundColor() const
{
    return m_foregroundColor;
}

void CircularProgressBar::setForegroundColor(const QColor &foregroundColor)
{
    if (m_foregroundColor == foregroundColor)
        return;

    m_foregroundColor = foregroundColor;
    emit foregroundColorChanged();
}

QColor CircularProgressBar::backgroundColor() const
{
    return m_backgroundColor;
}

void CircularProgressBar::setBackgroundColor(const QColor &backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged();
}


