#include "qanimatedemptylistitem.h"

QAnimatedEmptyListItem::QAnimatedEmptyListItem(QWidget *parent) : QFrame(parent)
{
    setupUi();
}

QAnimatedEmptyListItem::~QAnimatedEmptyListItem()
{

}

void QAnimatedEmptyListItem::setupUi()
{
    setLayout(new QGridLayout(this));

    m_label = new QLabel(this);
    m_label->setText(QString("No Items"));
    m_label->setAlignment(Qt::AlignCenter);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setText(QString(""));
    m_iconLabel->setAlignment(Qt::AlignCenter);

    // QPixmap pixmap = Settings::getThemeIcon(QString("empty")).pixmap(48,48);
    // m_iconLabel->setPixmap(pixmap);

    m_topSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_bottomSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_middleSpacer = new QSpacerItem(20,20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    QGridLayout *m_layout = (QGridLayout*)layout();
    m_layout->addItem(m_topSpacer,0,0);
    m_layout->addWidget(m_iconLabel);
    m_layout->addItem(m_middleSpacer,2,0);
    m_layout->addWidget(m_label);
    m_layout->addItem(m_bottomSpacer,4,0);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));
}

void QAnimatedEmptyListItem::setText(const QString &text)
{
    m_label->setText(text);
}

void QAnimatedEmptyListItem::setIcon(const QPixmap &pixmap)
{
    m_iconLabel->setPixmap(pixmap);
}

void QAnimatedEmptyListItem::setIcon(const QString &iconName)
{
    // QPixmap pixmap = Settings::getThemeIcon(iconName).pixmap(64,64);
    // m_iconLabel->setPixmap(pixmap);
}
