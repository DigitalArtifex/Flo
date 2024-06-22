#include "qmaskedbutton.h"

QMaskedButton::QMaskedButton(QWidget *parent)
    : QWidget{parent}
{
}

QMaskedButton::~QMaskedButton()
{
    if(m_clickTimer)
        delete m_clickTimer;
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
    if(event->button() == Qt::LeftButton)
    {
        if(m_clickTimer)
        {
            delete m_clickTimer;
            m_clickTimer = nullptr;
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
        painter.drawImage(m_clickPixmap.rect(), m_clickPixmap.toImage());
        setMask(m_clickMask);
    }
    else if(property("hover").toBool())
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::LosslessImageRendering);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QRect(), image);
        painter.drawImage(m_hoverPixmap.rect(), m_hoverPixmap.toImage());
        setMask(m_hoverMask);
    }
    else
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::LosslessImageRendering);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(QRect(),image);
        painter.drawImage(m_pixmap.rect(), m_pixmap.toImage());
        setMask(m_mask);
    }

    QWidget::paintEvent(event);
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
}

void QMaskedButton::setClickPixmap(const QPixmap &pixmap)
{
    m_clickPixmap = pixmap;
    m_clickMask = pixmap.createHeuristicMask();
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

    if(m_clickTimer)
    {
        delete m_clickTimer;
        m_clickTimer = nullptr;
    }

    update();
}
