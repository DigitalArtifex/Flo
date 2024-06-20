#include "toolheadcontrolframe.h"

ToolHeadControlFrame::ToolHeadControlFrame(Toolhead *toolhead, QWidget *parent) : QFrame(parent)
{
    QPixmap xDownImage(":/images/ui/toolhead/x_down_control_image.png");
    QPixmap xDownClickedImage(":/images/ui/toolhead/x_down_control_image_clicked.png");
    QPixmap xDownHoverImage(":/images/ui/toolhead/x_down_control_image_hover.png");

    QPixmap xUpImage(":/images/ui/toolhead/x_up_control_image.png");
    QPixmap xUpClickedImage(":/images/ui/toolhead/x_up_control_image_clicked.png");
    QPixmap xUpHoverImage(":/images/ui/toolhead/x_up_control_image_hover.png");

    _xDownWidget = new QMaskedButton(this);
    _xDownWidget->setPixmap(xDownImage);
    _xDownWidget->setClickPixmap(xDownClickedImage);
    _xDownWidget->setHoverPixmap(xDownHoverImage);
    _xDownWidget->setFixedSize(size());
    connect(_xDownWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(xDownClickEvent()));

    _xUpWidget = new QMaskedButton(this);
    _xUpWidget->setPixmap(xUpImage);
    _xUpWidget->setClickPixmap(xUpClickedImage);
    _xUpWidget->setHoverPixmap(xUpHoverImage);
    _xUpWidget->setFixedSize(size());
    connect(_xUpWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(xUpClickEvent()));

    QPixmap yDownImage(":/images/ui/toolhead/y_down_control_image.png");
    QPixmap yDownClickedImage(":/images/ui/toolhead/y_down_control_image_clicked.png");
    QPixmap yDownHoverImage(":/images/ui/toolhead/y_down_control_image_hover.png");

    QPixmap yUpImage(":/images/ui/toolhead/y_up_control_image.png");
    QPixmap yUpClickedImage(":/images/ui/toolhead/y_up_control_image_clicked.png");
    QPixmap yUpHoverImage(":/images/ui/toolhead/y_up_control_image_hover.png");

    _yDownWidget = new QMaskedButton(this);
    _yDownWidget->setPixmap(yUpImage);
    _yDownWidget->setClickPixmap(yUpClickedImage);
    _yDownWidget->setHoverPixmap(yUpHoverImage);
    _yDownWidget->setFixedSize(size());
    connect(_yDownWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(yDownClickEvent()));

    _yUpWidget = new QMaskedButton(this);
    _yUpWidget->setPixmap(yDownImage);
    _yUpWidget->setClickPixmap(yDownClickedImage);
    _yUpWidget->setHoverPixmap(yDownHoverImage);
    _yUpWidget->setFixedSize(size());
    connect(_yUpWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(yUpClickEvent()));

    QPixmap zDownImage(":/images/ui/toolhead/z_down_control_image.png");
    QPixmap zDownClickedImage(":/images/ui/toolhead/z_down_control_image_clicked.png");
    QPixmap zDownHoverImage(":/images/ui/toolhead/z_down_control_image_hover.png");

    QPixmap zUpImage(":/images/ui/toolhead/z_up_control_image.png");
    QPixmap zUpClickedImage(":/images/ui/toolhead/z_up_control_image_clicked.png");
    QPixmap zUpHoverImage(":/images/ui/toolhead/z_up_control_image_hover.png");

    _zDownWidget = new QMaskedButton(this);
    _zDownWidget->setPixmap(zDownImage);
    _zDownWidget->setClickPixmap(zDownClickedImage);
    _zDownWidget->setHoverPixmap(zDownHoverImage);
    _zDownWidget->setFixedSize(size());
    connect(_zDownWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(zDownClickEvent()));

    _zUpWidget = new QMaskedButton(this);
    _zUpWidget->setPixmap(zUpImage);
    _zUpWidget->setClickPixmap(zUpClickedImage);
    _zUpWidget->setHoverPixmap(zUpHoverImage);
    _zUpWidget->setFixedSize(size());
    connect(_zUpWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(zUpClickEvent()));

    QPixmap homeImage(":/images/ui/toolhead/home_default.png");
    QPixmap homeClickedImage(":/images/ui/toolhead/home_clicked.png");
    QPixmap homeHoverImage(":/images/ui/toolhead/home_hover.png");

    _homeWidget = new QMaskedButton(this);
    _homeWidget->setPixmap(homeImage);
    _homeWidget->setClickPixmap(homeClickedImage);
    _homeWidget->setHoverPixmap(homeHoverImage);
    _homeWidget->setFixedSize(size());
    connect(_homeWidget, SIGNAL(clicked(QMaskedButton*)), this, SLOT(homeClickEvent()));

    _toolhead = toolhead;
}

ToolHeadControlFrame::~ToolHeadControlFrame()
{
    if(_homeWidget)
        delete _homeWidget;

    if(_xDownWidget)
        delete _xDownWidget;

    if(_xUpWidget)
        delete _xUpWidget;

    if(_yUpWidget)
        delete _yUpWidget;

    if(_yDownWidget)
        delete _yDownWidget;

    if(_zUpWidget)
        delete _zUpWidget;

    if(_zDownWidget)
        delete _zDownWidget;
}

void ToolHeadControlFrame::resizeEvent(QResizeEvent *event)
{
    _zUpWidget->setFixedSize(size());
    _zDownWidget->setFixedSize(size());
    _yUpWidget->setFixedSize(size());
    _yDownWidget->setFixedSize(size());
    _xUpWidget->setFixedSize(size());
    _xDownWidget->setFixedSize(size());
    _homeWidget->setFixedSize(size());

    QFrame::resizeEvent(event);
}

void ToolHeadControlFrame::xUpClickEvent()
{
    qDebug() << "x up clicked";
}

void ToolHeadControlFrame::xDownClickEvent()
{
    qDebug() << "x down clicked";
}

void ToolHeadControlFrame::yUpClickEvent()
{
    qDebug() << "y up clicked";
}

void ToolHeadControlFrame::yDownClickEvent()
{
    qDebug() << "y down clicked";
}

void ToolHeadControlFrame::zUpClickEvent()
{
    qDebug() << "z up clicked";
}

void ToolHeadControlFrame::zDownClickEvent()
{
    qDebug() << "z down clicked";
}

void ToolHeadControlFrame::homeClickEvent()
{
    qDebug() << "home all clicked";
}

void ToolHeadControlFrame::toolheadUpdateEvent()
{
    _homeWidget->setEnabled(!_toolhead->isHomed());
    _xDownWidget->setEnabled(_toolhead->isHomed());
    _xUpWidget->setEnabled(_toolhead->isHomed());
    _yDownWidget->setEnabled(_toolhead->isHomed());
    _yUpWidget->setEnabled(_toolhead->isHomed());
    _zDownWidget->setEnabled(_toolhead->isHomed());
    _zUpWidget->setEnabled(_toolhead->isHomed());
}
