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
        event->accept();
    }

    //QFrame::mousePressEvent(event);
}

void QIconButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_pressed)
    {
        setProperty("clicked", false);
        m_pressed = false;
        event->accept();

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

    //QFrame::mouseReleaseEvent(event);
}

void QIconButton::paintEvent(QPaintEvent *event)
{
    //QFrame::paintEvent(event);

    if(visibleRegion().isNull())
        return;

    QPixmap pixmap;

    QSize size = m_iconSize;

    int x = 10;
    int y = 10;

    //qss/qproperty overrides
    if(property("icon-right").isValid())
        x -= property("icon-right").toInt();
    if(property("icon-left").isValid())
        x += property("icon-left").toInt();

    if(property("icon-top").isValid())
        y += property("icon-top").toInt();
    if(property("icon-bottom").isValid())
        y -= property("icon-bottom").toInt();

    if(property("icon-size").isValid())
        size = property("icon-size").toSize();

    if((m_iconAlignment & Qt::AlignHCenter) == Qt::AlignHCenter)
        x = (width() / 2) - (size.width() / 2);

    else if((m_iconAlignment & Qt::AlignLeft) == Qt::AlignLeft)
        x = 10;

    else if((m_iconAlignment & Qt::AlignRight) == Qt::AlignRight)
        x = (width() - size.width()) - 10;

    if((m_iconAlignment & Qt::AlignVCenter) == Qt::AlignVCenter)
        y = (height() / 2) - (size.height() / 2);

    else if((m_iconAlignment & Qt::AlignTop) == Qt::AlignTop)
        y = 10;

    else if((m_iconAlignment & Qt::AlignBottom) == Qt::AlignBottom)
        y = (height() - size.height()) - 10;

    if(isEnabled())
        pixmap = (m_icon.pixmap(size, QIcon::Normal, QIcon::On));
    else
        pixmap = (m_icon.pixmap(size, QIcon::Disabled, QIcon::On));

    if(m_checkable && !m_checked)
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

QGraphicsEffect *QIconButton::iconEffect() const
{
    return m_iconEffect;
}

void QIconButton::setIconEffect(QGraphicsEffect *iconEffect)
{
    if (m_iconEffect == iconEffect)
        return;

    m_iconEffect = iconEffect;

    emit iconEffectChanged();
}

QGraphicsEffect *QIconButton::textEffect() const
{
    return m_textEffect;
}

void QIconButton::setTextEffect(QGraphicsEffect *textEffect)
{
    if (m_textEffect == textEffect)
        return;

    //clear previous effect
    if(m_textEffect)
    {
        m_textLabel->setGraphicsEffect(nullptr);
        m_textEffect->deleteLater();
    }

    m_textEffect = textEffect;
    m_textLabel->setGraphicsEffect(m_textEffect);

    emit textEffectChanged();
}

Qt::Alignment QIconButton::iconAlignment() const
{
    return m_iconAlignment;
}

void QIconButton::setIconAlignment(const Qt::Alignment &iconAlignment)
{
    if (m_iconAlignment == iconAlignment)
        return;

    m_iconAlignment = iconAlignment;
    emit iconAlignmentChanged();
}

Qt::Alignment QIconButton::textAlignment() const
{
    return m_textAlignment;
}

void QIconButton::setTextAlignment(const Qt::Alignment &textAlignment)
{
    if (m_textAlignment == textAlignment)
        return;

    m_textLabel->setAlignment(textAlignment);

    m_textAlignment = textAlignment;
    emit textAlignmentChanged();
}

QMargins QIconButton::textMargins() const
{
    return m_textMargins;
}

void QIconButton::setTextMargins(const QMargins &textMargins)
{
    if (m_textMargins == textMargins)
        return;

    m_textMargins = textMargins;
    m_textLabel->setContentsMargins(m_textMargins);

    emit textMarginsChanged();
}

QSize QIconButton::iconSize() const
{
    return m_iconSize;
}

void QIconButton::setIconSize(const QSize &iconSize)
{
    if (m_iconSize == iconSize)
        return;

    m_iconSize = iconSize;
    emit iconSizeChanged();
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
    m_textLabel->setContentsMargins(m_textMargins);
    m_textLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_textLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(m_textLabel);

    setProperty("class", QStringList { "Button" } + property("class").toStringList());
    m_textLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "ButtonText"));

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(3);
    effect->setOffset(0,0);
    effect->setColor(QColor::fromRgba(qRgba(0, 0, 0, 255)));
    setTextEffect(effect);

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
