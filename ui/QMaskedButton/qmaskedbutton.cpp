#include "qmaskedbutton.h"

QMaskedButton::QMaskedButton(QWidget *parent)
    : QWidget{parent}
{
}

QMaskedButton::~QMaskedButton()
{
    if(_clickTimer)
        delete _clickTimer;
}

void QMaskedButton::on_clickTimer_timeout()
{
    if(property("pressed").toBool())
        setProperty("longPressed", true);
}

void QMaskedButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked(this);
}

void QMaskedButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setProperty("pressed", true);
        update();

        _clickTimer = new QTimer(this);
        connect(_clickTimer, SIGNAL(timeout()), this, SLOT(on_clickTimer_timeout()));

        _clickTimer->setInterval(500);
        _clickTimer->setSingleShot(true);
        _clickTimer->start();
    }

    QWidget::mousePressEvent(event);
}

void QMaskedButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(_clickTimer)
        {
            delete _clickTimer;
            _clickTimer = nullptr;
        }

        if(property("pressed").toBool() && !property("longPressed").toBool())
        {
            setProperty("pressed", false);
            setProperty("longPressed", false);
            update();

            emit clicked(this);
        }
        else if(property("longPressed").toBool())
        {
            setProperty("pressed", false);
            setProperty("longPressed", false);
            update();

            emit longPressed(this);
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void QMaskedButton::paintEvent(QPaintEvent *event)
{
    QImage image(size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    if(property("pressed").toBool())
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::LosslessImageRendering);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QRect(),image);
        painter.drawImage(_clickPixmap.rect(), _clickPixmap.toImage());
        setMask(_clickMask);
    }
    else if(property("hover").toBool())
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::LosslessImageRendering);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QRect(), image);
        painter.drawImage(_hoverPixmap.rect(), _hoverPixmap.toImage());
        setMask(_hoverMask);
    }
    else
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::LosslessImageRendering);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QRect(),image);
        painter.drawImage(_pixmap.rect(), _pixmap.toImage());
        setMask(_mask);
    }

    QWidget::paintEvent(event);
}

void QMaskedButton::setPixmap(const QPixmap &pixmap)
{
    _pixmap = pixmap;
    _mask = pixmap.createHeuristicMask();

    update();
}

void QMaskedButton::setHoverPixmap(const QPixmap &pixmap)
{
    _hoverPixmap = pixmap;
    _hoverMask = pixmap.createHeuristicMask();
}

void QMaskedButton::setClickPixmap(const QPixmap &pixmap)
{
    _clickPixmap = pixmap;
    _clickMask = pixmap.createHeuristicMask();
}

void QMaskedButton::enterEvent(QEnterEvent *event)
{
    setProperty("hover", true);

    update();
}

void QMaskedButton::leaveEvent(QEvent *event)
{
    setProperty("hover", false);
    setProperty("pressed", false);
    setProperty("longPressed", false);

    if(_clickTimer)
    {
        delete _clickTimer;
        _clickTimer = nullptr;
    }

    update();
}
