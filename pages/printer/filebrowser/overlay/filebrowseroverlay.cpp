#include "filebrowseroverlay.h"
#include "../../../../system/settings.h"

FileBrowserOverlay::FileBrowserOverlay(QWidget *parent) :
    QAnimatedWidget(parent)
{
    setupUi();
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
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

    _layout = new QGridLayout(this);
    _layout->addWidget(_label);

    setLayout(_layout);
}

void FileBrowserOverlay::setText(const QString &text)
{
    _label->setText(text);
}
