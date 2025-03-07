#include "qanimatedtoolboxbutton.h"

QAnimatedToolBoxButton::QAnimatedToolBoxButton(QWidget *parent)
    : QIconButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

QAnimatedToolBoxButton::QAnimatedToolBoxButton(QString text, QWidget *parent)
    : QIconButton(parent)
{
    setText(text);
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

QAnimatedToolBoxButton::QAnimatedToolBoxButton(QIcon icon, QString text, QWidget *parent)
    : QIconButton(parent)
{
    setIcon(icon);
    setText(text);
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

void QAnimatedToolBoxButton::onClicked()
{
    emit clicked(this);
}
