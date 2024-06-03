#include "qanimatedemptylistitem.h"

#include "../../system/settings.h"

QAnimatedEmptyListItem::QAnimatedEmptyListItem(QWidget *parent) : QAnimatedWidget(parent)
{
    setupUi();
}

QAnimatedEmptyListItem::~QAnimatedEmptyListItem()
{
    //delete _label;
    //delete _iconLabel;
    //delete _topSpacer;
    //delete _bottomSpacer;
    //delete _middleSpacer;
    delete _layout;
}

void QAnimatedEmptyListItem::setupUi()
{
    _label = new QLabel(this);
    _label->setText(QString("No Items"));
    _label->setAlignment(Qt::AlignCenter);

    _iconLabel = new QLabel(this);
    _iconLabel->setText(QString(""));
    _iconLabel->setAlignment(Qt::AlignCenter);

    QPixmap pixmap = Settings::getThemeIcon(QString("empty-icon")).pixmap(64,64);
    _iconLabel->setPixmap(pixmap);

    _topSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    _bottomSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    _middleSpacer = new QSpacerItem(20,20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    _layout = new QGridLayout();
    _layout->addItem(_topSpacer,0,0);
    _layout->addWidget(_label);
    _layout->addItem(_middleSpacer,2,0);
    _layout->addWidget(_iconLabel);
    _layout->addItem(_bottomSpacer,4,0);

    setLayout(_layout);
}

void QAnimatedEmptyListItem::setText(const QString &text)
{
    _label->setText(text);
}

void QAnimatedEmptyListItem::setIcon(const QPixmap &pixmap)
{
    _iconLabel->setPixmap(pixmap);
}

void QAnimatedEmptyListItem::setIcon(const QString &iconName)
{
    QPixmap pixmap = Settings::getThemeIcon(iconName).pixmap(64,64);
    _iconLabel->setPixmap(pixmap);
}
