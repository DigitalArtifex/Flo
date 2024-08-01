#include "menubutton.h"
#include "ui_menubutton.h"

#include "../system/settings.h"

MenuButton::MenuButton(int id, QWidget *parent) :
    QFrame(parent),
    id(id),
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
    QPixmap pixmap = loadedIcon.pixmap(QSize(ui->icon->height() - 4, ui->icon->width() - 4));
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
    m_checked = checked;
    style()->polish(this);
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
        setProperty("pressed", true);
        m_pressed = true;
        style()->polish(this);
    }
}

void MenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_pressed)
    {
        setProperty("pressed", false);
        m_pressed = false;

        m_checked = !m_checked;
        setProperty("checked", m_checked);
        emit clicked(this);

        style()->polish(this);
    }
}

void MenuButton::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
}
