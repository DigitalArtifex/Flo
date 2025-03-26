#include "locationindicator.h"
#include "qpainter.h"
#include <QStyle>
#include <QStyleOption>

LocationIndicator::LocationIndicator(QWidget *parent)
    : QFrame{parent}
{
    m_private = new LocationIndicatorPrivate(this);

    connect(m_private, SIGNAL(xChanged()), this, SLOT(update()));
    connect(m_private, SIGNAL(yChanged()), this, SLOT(update()));
}

qreal LocationIndicator::x() const
{
    return m_x;
}

void LocationIndicator::setX(qreal x)
{
    if (qFuzzyCompare(m_x, x))
        return;

    m_private->setX(x);

    m_x = x;
    emit xChanged();
}

qreal LocationIndicator::y() const
{
    return m_y;
}

void LocationIndicator::setY(qreal y)
{
    if (qFuzzyCompare(m_y, y))
        return;

    m_private->setY(y);

    m_y = y;
    emit yChanged();
}

qreal LocationIndicator::xMaximum() const
{
    return m_xMaximum;
}

void LocationIndicator::setXMaximum(qreal xMaximum)
{
    if (qFuzzyCompare(m_xMaximum, xMaximum))
        return;

    m_xMaximum = xMaximum;
    emit xMaximumChanged();
    update();
}

qreal LocationIndicator::yMaximum() const
{
    return m_yMaximum;
}

void LocationIndicator::setYMaximum(qreal yMaximum)
{
    if (qFuzzyCompare(m_yMaximum, yMaximum))
        return;

    m_yMaximum = yMaximum;
    emit yMaximumChanged();
    update();
}

void LocationIndicator::paintEvent(QPaintEvent *event)
{
    if(visibleRegion().isNull())
        return;

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QStyleOptionFrame option;
    initStyleOption(&option);

    if(visibleRegion().isNull())
        return;

    QColor crosshairColor = m_crosshairColor.isValid() ? m_crosshairColor : style()->standardPalette().color(QPalette::Highlight);
    QColor pointColor = m_pointColor.isValid() ? m_pointColor : style()->standardPalette().color(QPalette::Highlight);

    qreal xpoint = width() * (m_private->x() / xMaximum());
    qreal ypoint = height() * (m_private->y() / yMaximum());

    QPen crosshairShadowPen;
    crosshairShadowPen.setWidth(1);

    crosshairShadowPen.setColor(QColor(0,0,0,16));
    painter.setPen(crosshairShadowPen);
    painter.drawEllipse(QPointF(xpoint + 3, ypoint + 3), 5, 5);
    crosshairShadowPen.setColor(QColor(0,0,0,32));
    painter.setPen(crosshairShadowPen);
    painter.drawEllipse(QPointF(xpoint + 2, ypoint + 2), 5, 5);
    crosshairShadowPen.setColor(QColor(0,0,0,64));
    painter.setPen(crosshairShadowPen);
    painter.drawEllipse(QPointF(xpoint + 1, ypoint + 1), 5, 5);

    // X Cross
    crosshairShadowPen.setColor(QColor(0,0,0,16));
    painter.setPen(crosshairShadowPen);
    painter.drawLine(QPointF(xpoint + 3,0),QPointF(xpoint + 3, height()));

    crosshairShadowPen.setColor(QColor(0,0,0,32));
    painter.setPen(crosshairShadowPen);
    painter.drawLine(QPointF(xpoint + 2,0),QPointF(xpoint + 2, height()));

    crosshairShadowPen.setColor(QColor(0,0,0,64));
    painter.setPen(crosshairShadowPen);
    painter.drawLine(QPointF(xpoint + 1,0),QPointF(xpoint + 1, height()));

    QPen crosshairPen(crosshairColor);
    crosshairPen.setWidth(2);
    painter.setPen(crosshairPen);

    painter.drawLine(QPointF(xpoint,0),QPointF(xpoint, height()));

    // Y Cross
    crosshairShadowPen.setColor(QColor(0,0,0,16));
    painter.setPen(crosshairShadowPen);
    painter.drawLine(QPointF(0,ypoint + 3),QPointF(width(), ypoint + 3));

    crosshairShadowPen.setColor(QColor(0,0,0,32));
    painter.setPen(crosshairShadowPen);
    painter.drawLine(QPointF(0,ypoint + 2),QPointF(width(), ypoint + 2));

    crosshairShadowPen.setColor(QColor(0,0,0,64));
    painter.setPen(crosshairShadowPen);
    painter.drawLine(QPointF(0,ypoint + 1),QPointF(width(), ypoint + 1));

    painter.setPen(crosshairPen);
    painter.drawLine(QPointF(0,ypoint),QPointF(width(), ypoint));

    QBrush pointBrush(pointColor);
    painter.setBrush(pointBrush);
    painter.drawEllipse(QPointF(xpoint, ypoint), 5, 5);

    QBrush transparent(Qt::transparent);
    painter.setBrush(transparent);

    style()->drawPrimitive(QStyle::PE_Frame, &option, &painter, this);

    painter.end();
}

QColor LocationIndicator::pointColor() const
{
    return m_pointColor;
}

void LocationIndicator::setPointColor(const QColor &pointColor)
{
    if (m_pointColor == pointColor)
        return;
    m_pointColor = pointColor;
    emit pointColorChanged();
}

QColor LocationIndicator::crosshairColor() const
{
    return m_crosshairColor;
}

void LocationIndicator::setCrosshairColor(const QColor &crosshairColor)
{
    if (m_crosshairColor == crosshairColor)
        return;

    m_crosshairColor = crosshairColor;
    emit crosshairColorChanged();
}
