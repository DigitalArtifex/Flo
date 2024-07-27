#include "qiconbutton.h"

QIconButton::QIconButton(QWidget *parent)
    : QFrame{parent}
{
    setupUi();
}

QIconButton::~QIconButton()
{
    if(m_iconLabel)
        delete m_iconLabel;

    if(m_textLabel)
        delete m_textLabel;

    if(m_layout)
        delete m_layout;
}

void QIconButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setProperty("pressed", true);
        m_pressed = true;
        style()->polish(this);
    }
}

void QIconButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_pressed)
    {
        setProperty("pressed", false);
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

bool QIconButton::exclusive() const
{
    return m_exclusive;
}

void QIconButton::setExclusive(bool newExclusive)
{
    m_exclusive = newExclusive;
}

bool QIconButton::isChecked() const
{
    return m_checked;
}

void QIconButton::setChecked(bool newChecked)
{
    setProperty("checked", newChecked);
    m_checked = newChecked;
    style()->polish(this);
}

QString QIconButton::text() const
{
    return m_text;
}

void QIconButton::setText(const QString &newText)
{
    m_text = newText;
    m_textLabel->setText(newText);
    style()->polish(this);
}

void QIconButton::setStyleSheet(QString &styleSheet)
{

    if(m_iconLabel)
        m_iconLabel->setStyleSheet(styleSheet);

    if(m_textLabel)
        m_textLabel->setStyleSheet(styleSheet);

    QWidget::setStyleSheet(styleSheet);
    style()->polish(this);
}

void QIconButton::setupUi()
{
    m_layout = new QHBoxLayout(this);
    setLayout(m_layout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->resize(24,24);
    m_iconLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_layout->addWidget(m_iconLabel);

    m_textLabel = new QLabel(this);
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_textLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(m_textLabel);

    setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "Button"));
    m_textLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "ButtonText"));
    m_iconLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "ButtonIcon"));
    style()->polish(this);
}

QPixmap QIconButton::pixmap() const
{
    return m_pixmap;
}

void QIconButton::setPixmap(const QPixmap &newPixmap)
{
    m_pixmap = newPixmap;
    m_iconLabel->setPixmap(m_pixmap);
    style()->polish(this);
}

bool QIconButton::isCheckable() const
{
    return m_checkable;
}

void QIconButton::setCheckable(bool newCheckable)
{
    m_checkable = newCheckable;
    setChecked(m_checked);
}
