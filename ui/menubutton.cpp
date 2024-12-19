#include "menubutton.h"
#include "ui_menubutton.h"

#include "../system/settings.h"

MenuButton::MenuButton(int id, QWidget *parent) :
    QFrame(parent),
    id(id),
    ui(new Ui::MenuButton)
{
    ui->setupUi(this);
    //ui->text->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButtonText"));
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton"));
}

MenuButton::~MenuButton()
{
    delete ui;
}

void MenuButton::setIcon(QIcon icon)
{
    m_icon = icon;
    update();
}

void MenuButton::setText(QString text)
{
    this->text = text;
    //ui->text->setText(this->text);
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
    QPixmap pixmap;

    QSize size(36,36);

    if(property("iconSize").isValid())
        size = property("iconSize").toSize();

    int x = ((width() / 2) - (size.width() / 2));
    int y = ((height() / 2) - (size.height() / 2));

    if(property("iconRight").isValid())
        x = property("iconRight").toInt();

    if(property("iconTop").isValid())
        y = property("iconTop").toInt();

    if(isEnabled())
        pixmap = (m_icon.pixmap(size, QIcon::Normal, QIcon::On));
    else
        pixmap = (m_icon.pixmap(size, QIcon::Disabled, QIcon::On));

    QPainter painter;

    painter.begin(this);
    painter.drawPixmap(QRect(x, y, size.width(), size.height()), pixmap);
    painter.end();
}

void MenuButton::changeEvent(QEvent *event)
{
    QFrame::changeEvent(event);
}

QSize MenuButton::iconSize() const
{
    return m_iconSize;
}

void MenuButton::setIconSize(const QSize &iconSize)
{
    if (m_iconSize == iconSize)
        return;

    m_iconSize = iconSize;

    update();

    emit iconSizeChanged();
}
