#include "filebrowseroverlay.h"
#include "../../../../system/settings.h"

FileBrowserOverlay::FileBrowserOverlay(QWidget *parent) :
    QAnimatedWidget(parent)
{
    setupUi();
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));
    setOpacityIn(0.8);
    setOpacityOut(0);
    setDuration(100);

    setStyleSheet(Settings::currentTheme());
}

FileBrowserOverlay::~FileBrowserOverlay()
{
    if(_label)
        delete _label;

    if(_layout)
        delete _layout;
}

void FileBrowserOverlay::setupUi()
{
    _label = new QLabel(this);
    _label->setText(QString("Loading"));
    _label->setAlignment(Qt::AlignCenter);

    _iconLabel = new QLabel(this);
    _iconLabel->setText(QString(""));
    _iconLabel->setAlignment(Qt::AlignCenter);

    QPixmap pixmap = Settings::getThemeIcon(QString("empty-icon")).pixmap(64,64);
    _iconLabel->setPixmap(pixmap);

    _topSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    _bottomSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    _layout = new QGridLayout(this);
    _layout->addItem(_topSpacer,0,0);
    _layout->addWidget(_label);
    _layout->addWidget(_iconLabel);
    _layout->addItem(_bottomSpacer,3,0);

    setLayout(_layout);
}

void FileBrowserOverlay::setText(const QString &text)
{
    _label->setText(text);
}

void FileBrowserOverlay::setIcon(const QPixmap &pixmap)
{
    _iconLabel->setPixmap(pixmap);
}

void FileBrowserOverlay::setIcon(const QIcon &icon)
{
    QPixmap pixmap = icon.pixmap(64,64);
    _iconLabel->setPixmap(pixmap);
}
