#include "toolheadcontrolframe.h"

ToolHeadControlFrame::ToolHeadControlFrame(QKlipperToolHead *toolhead, QWidget *parent) : QFrame(parent)
{
    QPixmap xDownImage(":/images/ui/toolhead/x_down_control_image.png");
    QPixmap xDownClickedImage(":/images/ui/toolhead/x_down_control_image_clicked.png");
    QPixmap xDownHoverImage(":/images/ui/toolhead/x_down_control_image_hover.png");

    QPixmap xUpImage(":/images/ui/toolhead/x_up_control_image.png");
    QPixmap xUpClickedImage(":/images/ui/toolhead/x_up_control_image_clicked.png");
    QPixmap xUpHoverImage(":/images/ui/toolhead/x_up_control_image_hover.png");

    m_xDownWidget = new QMaskedButton(this);
    m_xDownWidget->setPixmap(xDownImage);
    m_xDownWidget->setClickPixmap(xDownClickedImage);
    m_xDownWidget->setHoverPixmap(xDownHoverImage);
    m_xDownWidget->setFixedSize(size());
    connect(m_xDownWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(xDownClickEvent()));

    m_xUpWidget = new QMaskedButton(this);
    m_xUpWidget->setPixmap(xUpImage);
    m_xUpWidget->setClickPixmap(xUpClickedImage);
    m_xUpWidget->setHoverPixmap(xUpHoverImage);
    m_xUpWidget->setFixedSize(size());
    connect(m_xUpWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(xUpClickEvent()));

    QPixmap yDownImage(":/images/ui/toolhead/y_down_control_image.png");
    QPixmap yDownClickedImage(":/images/ui/toolhead/y_down_control_image_clicked.png");
    QPixmap yDownHoverImage(":/images/ui/toolhead/y_down_control_image_hover.png");

    QPixmap yUpImage(":/images/ui/toolhead/y_up_control_image.png");
    QPixmap yUpClickedImage(":/images/ui/toolhead/y_up_control_image_clicked.png");
    QPixmap yUpHoverImage(":/images/ui/toolhead/y_up_control_image_hover.png");

    m_yDownWidget = new QMaskedButton(this);
    m_yDownWidget->setPixmap(yUpImage);
    m_yDownWidget->setClickPixmap(yUpClickedImage);
    m_yDownWidget->setHoverPixmap(yUpHoverImage);
    m_yDownWidget->setFixedSize(size());
    connect(m_yDownWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(yDownClickEvent()));

    m_yUpWidget = new QMaskedButton(this);
    m_yUpWidget->setPixmap(yDownImage);
    m_yUpWidget->setClickPixmap(yDownClickedImage);
    m_yUpWidget->setHoverPixmap(yDownHoverImage);
    m_yUpWidget->setFixedSize(size());
    connect(m_yUpWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(yUpClickEvent()));

    QPixmap zDownImage(":/images/ui/toolhead/z_down_control_image.png");
    QPixmap zDownClickedImage(":/images/ui/toolhead/z_down_control_image_clicked.png");
    QPixmap zDownHoverImage(":/images/ui/toolhead/z_down_control_image_hover.png");

    QPixmap zUpImage(":/images/ui/toolhead/z_up_control_image.png");
    QPixmap zUpClickedImage(":/images/ui/toolhead/z_up_control_image_clicked.png");
    QPixmap zUpHoverImage(":/images/ui/toolhead/z_up_control_image_hover.png");

    m_zDownWidget = new QMaskedButton(this);
    m_zDownWidget->setPixmap(zDownImage);
    m_zDownWidget->setClickPixmap(zDownClickedImage);
    m_zDownWidget->setHoverPixmap(zDownHoverImage);
    m_zDownWidget->setFixedSize(size());
    connect(m_zDownWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(zDownClickEvent()));

    m_zUpWidget = new QMaskedButton(this);
    m_zUpWidget->setPixmap(zUpImage);
    m_zUpWidget->setClickPixmap(zUpClickedImage);
    m_zUpWidget->setHoverPixmap(zUpHoverImage);
    m_zUpWidget->setFixedSize(size());
    connect(m_zUpWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(zUpClickEvent()));

    QPixmap homeImage(":/images/ui/toolhead/home_default.png");
    QPixmap homeClickedImage(":/images/ui/toolhead/home_clicked.png");
    QPixmap homeHoverImage(":/images/ui/toolhead/home_hover.png");

    m_homeWidget = new QMaskedButton(this);
    m_homeWidget->setPixmap(homeImage);
    m_homeWidget->setClickPixmap(homeClickedImage);
    m_homeWidget->setHoverPixmap(homeHoverImage);
    m_homeWidget->setFixedSize(size());
    connect(m_homeWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(homeClickEvent()));

    m_toolhead = toolhead;
    connect(m_toolhead, SIGNAL(isHomedChanged()), this, SLOT(toolheadUpdateEvent()));

    toolheadUpdateEvent();
}

ToolHeadControlFrame::~ToolHeadControlFrame()
{
}

void ToolHeadControlFrame::resizeEvent(QResizeEvent *event)
{
    m_zUpWidget->setFixedSize(size());
    m_zDownWidget->setFixedSize(size());
    m_yUpWidget->setFixedSize(size());
    m_yDownWidget->setFixedSize(size());
    m_xUpWidget->setFixedSize(size());
    m_xDownWidget->setFixedSize(size());
    m_homeWidget->setFixedSize(size());

    QFrame::resizeEvent(event);
}

void ToolHeadControlFrame::xUpClickEvent()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_toolhead->parent());

    //Move toolhead if printer is online
    switch(printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        printer->toolhead()->moveX(m_increment);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolHeadControlFrame::xDownClickEvent()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_toolhead->parent());

    //Move toolhead if printer is online
    switch(printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        printer->toolhead()->moveX(m_increment * -1);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolHeadControlFrame::yUpClickEvent()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_toolhead->parent());

    //Move toolhead if printer is online
    switch(printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        printer->toolhead()->moveY(m_increment);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolHeadControlFrame::yDownClickEvent()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_toolhead->parent());

    //Move toolhead if printer is online
    switch(printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        printer->toolhead()->moveY(m_increment * -1);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolHeadControlFrame::zUpClickEvent()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_toolhead->parent());

    //Move toolhead if printer is online
    switch(printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        printer->toolhead()->moveZ(m_increment);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolHeadControlFrame::zDownClickEvent()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_toolhead->parent());

    //Move toolhead if printer is online
    switch(printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        printer->toolhead()->moveZ(m_increment * -1);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolHeadControlFrame::homeClickEvent()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_toolhead->parent());

    //Move toolhead if printer is online
    switch(printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        printer->toolhead()->home();
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolHeadControlFrame::toolheadUpdateEvent()
{
    m_homeWidget->setEnabled(!m_toolhead->isHomed());
    m_xDownWidget->setEnabled(m_toolhead->isHomed());
    m_xUpWidget->setEnabled(m_toolhead->isHomed());
    m_yDownWidget->setEnabled(m_toolhead->isHomed());
    m_yUpWidget->setEnabled(m_toolhead->isHomed());
    m_zDownWidget->setEnabled(m_toolhead->isHomed());
    m_zUpWidget->setEnabled(m_toolhead->isHomed());
}

qreal ToolHeadControlFrame::increment() const
{
    return m_increment;
}

void ToolHeadControlFrame::setIncrement(qreal increment)
{
    m_increment = increment;
}
