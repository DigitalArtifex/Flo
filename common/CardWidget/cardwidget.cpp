#include "cardwidget.h"

CardWidget::CardWidget(CardType type, QWidget *parent)
    : QFrame{parent}
{
    m_cardType = type;
    setupUi();
}

CardWidget::CardWidget(QWidget *parent)
    : QFrame{parent}
{
    m_cardType = CardType::Widget;
    setupUi();
}

CardWidget::~CardWidget()
{
    if(m_layout)
        m_layout->deleteLater();
}

void CardWidget::setCentralWidget(QWidget *widget)
{
    if(m_centralWidget)
        m_contentLayout->removeWidget(m_centralWidget);

    m_centralWidget = widget;
    m_contentLayout->addWidget(m_centralWidget);
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

void CardWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowTitleChange)
        m_titleLabel->setText(windowTitle());
    else if(event->type() == QEvent::WindowIconChange)
        setIcon(windowIcon());
}

QLayout *CardWidget::layout() const
{
    return m_contentLayout;
}

void CardWidget::setContentsMargins(int left, int top, int right, int bottom)
{
    if(m_contentLayout)
        m_contentLayout->setContentsMargins(left, top, right, bottom);
}

void CardWidget::setContentsMargins(const QMargins &margins)
{
    if(m_contentLayout)
        m_contentLayout->setContentsMargins(margins);
}

void CardWidget::setLayout(QLayout *layout)
{
    if (m_contentLayout == layout)
        return;

    if(m_contentLayout)
        m_layout->removeItem(m_contentLayout);

    m_contentLayout = layout;

    if(m_footerWidget)
        m_layout->removeWidget(m_footerWidget);

    m_layout->addLayout(m_contentLayout);

    if(m_footerWidget)
        m_layout->addWidget(m_footerWidget);

    // m_layout = layout;

    emit layoutChanged();
}

void CardWidget::setupUi()
{
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

    m_contentLayout = (QLayout*)new QVBoxLayout(m_contentWidget);
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentWidget->setLayout(m_contentLayout);

    m_layout->addWidget(m_contentWidget);

    QFrame::setLayout(m_layout);

    if(m_cardType == CardType::Widget)
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

CardWidget::CardFlags CardWidget::cardFlags() const
{
    return m_cardFlags;
}

QWidget *CardWidget::centralWidget() const
{
    return m_centralWidget;
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

    if(m_cardType == CardType::Widget)
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
