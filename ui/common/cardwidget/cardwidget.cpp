#include "cardwidget.h"

CardWidget::CardWidget(CardType type, QWidget *parent)
    : QFrame{parent}
{
    m_cardType = type;

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    m_titleBarWidget = new QWidget(this);
    m_titleBarLayout = new QHBoxLayout(m_titleBarWidget);
    m_titleBarWidget->setLayout(m_titleBarLayout);
    m_titleBarWidget->setFixedHeight(40);

    m_iconLabel = new QLabel(m_titleBarWidget);
    m_iconLabel->setFixedSize(24,24);
    m_titleBarLayout->addWidget(m_iconLabel);

    m_titleLabel = new QLabel(m_titleBarWidget);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_titleBarLayout->addWidget(m_titleLabel);

    m_layout->addWidget(m_titleBarWidget);

    m_contentWidget = new QWidget(m_titleBarWidget);
    m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_contentLayout = new QVBoxLayout(m_contentWidget);
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentWidget->setLayout(m_contentLayout);

    m_layout->addWidget(m_contentWidget);

    setLayout(m_layout);

    if(m_cardType == Widget)
    {
        setProperty("class", "Widget");
        m_titleBarWidget->setProperty("class", "WidgetTitleBar");
    }
    else
    {
        setProperty("class", "SubWidget");
        m_titleBarWidget->setProperty("class", "SubWidgetTitleBar");
    }

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

CardWidget::~CardWidget()
{
    if(m_layout)
        m_layout->deleteLater();
}

void CardWidget::setCentralWidget(QWidget *widget)
{
    m_contentLayout->addWidget(widget);
}

void CardWidget::setupFooter()
{
    if(!m_footerWidget)
    {
        m_footerWidget = new QWidget(this);
        m_footerLayout = new QHBoxLayout(m_footerWidget);
        m_footerWidget->setLayout(m_footerLayout);

        m_layout->addWidget(m_footerWidget);
    }
}

void CardWidget::setupActionBar()
{
    if(!m_actionBarWidget)
    {
        m_actionBarWidget = new QWidget(this);
        m_actionBarLayout = new QHBoxLayout(m_actionBarWidget);
        m_actionBarLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        m_actionBarWidget->setLayout(m_actionBarLayout);

        m_layout->removeWidget(m_contentWidget);

        if(m_footerWidget)
            m_layout->removeWidget(m_footerWidget);

        m_layout->addWidget(m_actionBarWidget);
        m_layout->addWidget(m_contentWidget);

        if(m_footerWidget)
            m_layout->addWidget(m_footerWidget);
    }
}

CardWidget::CardFlags CardWidget::cardFlags() const
{
    return m_cardFlags;
}

void CardWidget::setCardFlags(CardFlags cardFlags)
{
    if (m_cardFlags == cardFlags)
        return;
    m_cardFlags = cardFlags;

    if(m_cardFlags & NoTitleBar)
        m_titleBarWidget->setFixedHeight(0);
    else
        m_titleBarWidget->setFixedHeight(35);

    emit cardFlagsChanged();
}

QIcon CardWidget::icon() const
{
    return m_icon;
}

void CardWidget::setIcon(const QIcon &icon)
{
    m_icon = icon;
    m_iconLabel->setPixmap(m_icon.pixmap(m_iconLabel->size()));
}

CardWidget::CardType CardWidget::cardType() const
{
    return m_cardType;
}

void CardWidget::setCardType(CardType newCardType)
{
    if(newCardType == m_cardType)
        return;

    m_cardType = newCardType;

    if(m_cardType == Widget)
    {
        setProperty("class", "Widget");
        m_titleBarWidget->setProperty("class", "WidgetTitleBar");
    }
    else
    {
        setProperty("class", "SubWidget");
        m_titleBarWidget->setProperty("class", "SubWidgetTitleBar");
    }

    style()->polish(this);
}

QString CardWidget::title() const
{
    return m_title;
}

void CardWidget::setTitle(const QString &newTitle)
{
    m_title = newTitle;
    m_titleLabel->setText(m_title);
}

void CardWidget::addToolButton(QToolButton *toolbutton)
{
    setupActionBar();

    m_actionBarLayout->addWidget(toolbutton);
}

void CardWidget::addFooterWidget(QWidget *widget)
{
    setupFooter();

    m_footerLayout->addWidget(widget);
}

void CardWidget::addFooterItem(QLayoutItem *item)
{
    setupFooter();

    m_footerLayout->addItem(item);
}
