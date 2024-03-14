#include "circularprogressbar.h"



void CircularProgressBar::setMinimum(qreal min)
{
    this->min = min;
    update();
}

void CircularProgressBar::setMaximum(qreal max)
{
    this->max = max;
    update();
}

void CircularProgressBar::setProgress(qreal progress)
{
    if(progress < this->min)
        progress = 0;
    else if(progress > this->max)
        progress = max;

    this->current = progress;
    update();
}

void CircularProgressBar::paintEvent(QPaintEvent *event)
{
    this->progress = (current / max);

    qreal pd = progress * 360;
    qreal rd = 360 - pd;
    QPainter p(this);
    int pathWidth = 12;
    int pathRadius = 0;
    int paddingX, paddingY;

    if(this->width() > this->height())
    {
        paddingX = this->width() - this->height();
        paddingX /= 2;
        paddingY = pathWidth / 2;
        pathRadius = this->height() - pathWidth;
    }
    else
    {
        paddingY = this->height() - this->width();
        paddingY /= 2;
        paddingY += pathWidth / 2;
        paddingX = pathWidth / 2;
        pathRadius = this->width() - pathWidth;
    }

    //p.fillRect(rect(), Qt::white);
    p.translate(4, 4);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path1, path2;
    path1.moveTo((pathRadius / 2) + paddingX, paddingY);
    path1.arcTo(QRectF(paddingX, paddingY, pathRadius - pathWidth, pathRadius - pathWidth), 90, -pd);
    QPen pen, pen2;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(QColor("#30b7e0"));
    pen.setWidth(pathWidth);
    p.strokePath(path1, pen);
    path2.moveTo((pathRadius / 2) + paddingX, paddingY);
    pen2.setWidth(pathWidth);
    pen2.setColor(QColor("#d7d7d7"));
    pen2.setCapStyle(Qt::FlatCap);
    //pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
    path2.arcTo(QRectF(paddingX, paddingY, pathRadius - pathWidth, pathRadius - pathWidth), 90, rd);
    //pen2.setDashOffset(2.2);
    p.strokePath(path2, pen2);

    int fontScale = (12 * (width() / minimumWidth()));
    //fontScale = 24;

    QFont font;
    QString text = QString::number(progress * 100.00, 'f', 2);

    font.setFamily(font.defaultFamily());
    font.setPointSize(fontScale);
    p.setFont(font);

    //Change point to pixels
    fontScale *= 1.33;

    qreal x = 0, y = 0;
    //Get true center
    x = width() / 2;
    x -= (fontScale * text.length()) / 2;

    y = (height()/2);
    //y += (fontScale / 2);
    p.drawText(QPoint(x,y),text);
}


