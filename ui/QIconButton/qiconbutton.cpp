#include "qiconbutton.h"

QIconButton::QIconButton(QWidget *parent)
    : QFrame{parent}
{
    setupUi();
}

QIconButton::~QIconButton()
{
    if(m_textLabel)
        m_textLabel->deleteLater();

    if(m_layout)
        m_layout->deleteLater();
}

void QIconButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setProperty("clicked", true);
        m_pressed = true;
        style()->polish(this);
    }
}

void QIconButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_pressed)
    {
        setProperty("clicked", false);
        m_pressed = false;

        if(!m_checkable)
        {
            style()->polish(this);
            emit clicked();
        }
        else
        {
            if(m_exclusive && !m_checked)
            {
                m_checked = true;
                setProperty("checked", m_checked);

                style()->polish(this);
                emit toggled(m_checked);
                emit clicked();
            }
            else if(!m_exclusive)
            {
                m_checked = !m_checked;
                setProperty("checked", m_checked);

                style()->polish(this);
                emit toggled(m_checked);
                emit clicked();
            }
        }
    }
}

void QIconButton::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPixmap pixmap;

    QSize size(24,24);

    int x = 10;
    int y = ((height() / 2) - (size.height() / 2));

    if(property("icon-right").isValid())
        x = property("icon-right").toInt();

    if(property("icon-top").isValid())
        y = property("icon-top").toInt();

    if(property("icon-size").isValid())
        size = property("icon-size").toSize();

    if(isEnabled())
        pixmap = (m_icon.pixmap(size, QIcon::Normal, QIcon::On));
    else
        pixmap = (m_icon.pixmap(size, QIcon::Disabled, QIcon::On));

    QPainter painter;

    painter.begin(this);
    painter.drawPixmap(QRect(x, y, size.width(), size.height()), pixmap);
    painter.end();
}

void QIconButton::changeEvent(QEvent *event)
{
    QFrame::changeEvent(event);
}

bool QIconButton::exclusive() const
{
    return m_exclusive;
}

void QIconButton::setExclusive(bool exclusive)
{
    m_exclusive = exclusive;
}

bool QIconButton::isChecked() const
{
    return m_checked;
}

void QIconButton::setChecked(bool checked)
{
    setProperty("checked", checked);
    m_checked = checked;
    style()->polish(this);
}

QString QIconButton::text() const
{
    return m_text;
}

void QIconButton::setText(const QString &text)
{
    m_text = text;
    m_textLabel->setText(text);
}

void QIconButton::setStyleSheet(const QString &styleSheet)
{
    if(m_textLabel)
        m_textLabel->setStyleSheet(styleSheet);

    QWidget::setStyleSheet(styleSheet);
}

QIcon QIconButton::icon() const
{
    return m_icon;
}

void QIconButton::setIcon(const QIcon &icon)
{
    m_icon = icon;
}

void QIconButton::setupUi()
{
    m_layout = new QHBoxLayout(this);
    setLayout(m_layout);

    m_textLabel = new QLabel(this);
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_textLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(m_textLabel);

    setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "Button"));
    m_textLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "ButtonText"));
    style()->polish(this);
}

bool QIconButton::isCheckable() const
{
    return m_checkable;
}

void QIconButton::setCheckable(bool checkable)
{
    m_checkable = checkable;
    setChecked(m_checked);
}
