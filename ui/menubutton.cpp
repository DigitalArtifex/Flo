#include "menubutton.h"
#include "ui_menubutton.h"

#include "../system/settings.h"

MenuButton::MenuButton(int id, QWidget *parent) :
    id(id),
    QFrame(parent),
    ui(new Ui::MenuButton)
{
    ui->setupUi(this);
    ui->icon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButtonIcon"));
    ui->text->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButtonText"));
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton"));
}

MenuButton::~MenuButton()
{
    delete ui;
}

void MenuButton::setIcon(QString icon)
{
    this->icon = icon;
    QIcon loadedIcon(Settings::getThemeIcon(this->icon));
    QPixmap pixmap = loadedIcon.pixmap(QSize(ui->icon->height(), ui->icon->width()));
    ui->icon->setPixmap(pixmap);
}

void MenuButton::setText(QString text)
{
    this->text = text;
    ui->text->setText(this->text);
}

void MenuButton::setChecked(bool checked)
{
    this->setProperty("checked", checked);
    repaint();
}

QString MenuButton::getText()
{
    return this->text;
}

int MenuButton::getId()
{
    return this->id;
}

void MenuButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->setProperty("pressed", true);
        pressed = true;
        this->style()->polish(this);
        qDebug() << "Pressed";
    }
}

void MenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && this->pressed)
    {
        this->setProperty("pressed", false);
        pressed = false;
        this->style()->polish(this);
        qDebug() << "Released";

        emit(clicked(this));
    }
}

void MenuButton::repaint()
{
    setIcon(this->icon);
    this->style()->polish(this);
    QFrame::repaint();
}
