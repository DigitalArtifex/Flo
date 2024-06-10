#include "emptyprinterwebcamframe.h"

EmptyPrinterWebcamFrame::EmptyPrinterWebcamFrame(QWidget *parent) :
    QFrame(parent)
{
    setupUi();
    setIcons();
}

void EmptyPrinterWebcamFrame::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    setIcons();
}

void EmptyPrinterWebcamFrame::setupUi()
{
    _layout = new QGridLayout(this);
    _layout->setContentsMargins(0,0,0,0);
    setLayout(_layout);

    _topSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    _layout->addItem(_topSpacer,0,0);

    _iconLabel = new QLabel(this);
    _iconLabel->setFixedSize(32,32);
    _layout->addWidget(_iconLabel, 1, 0, Qt::AlignCenter);

    _label = new QLabel(this);
    _label->setText(QString("No connection"));
    _label->setAlignment(Qt::AlignHCenter);
    _layout->addWidget(_label, 2, 0, Qt::AlignCenter);

    _bottomSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    _layout->addItem(_bottomSpacer,3,0);
}

void EmptyPrinterWebcamFrame::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("no-video-icon").pixmap(28,28);
    _iconLabel->setPixmap(pixmap);
}
