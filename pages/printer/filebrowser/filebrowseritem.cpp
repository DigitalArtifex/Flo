#include "filebrowseritem.h"

FileBrowserItem::FileBrowserItem(KlipperFile file, QWidget *parent) :
    QAnimatedListItem(parent)
{
    setupUi();
    setFile(file);
}

FileBrowserItem::~FileBrowserItem()
{

    delete _iconLabel;
    delete _iconContainer;
    delete _titleLabel;
    delete _sizeLabel;
    delete _modifiedLabel;
    delete _spacer;
    delete _layout;
}

KlipperFile FileBrowserItem::file() const
{
    return _file;
}

void FileBrowserItem::setFile(const KlipperFile &file)
{
    _file = file;
}

bool FileBrowserItem::isDirectory() const
{
    return _directory;
}

void FileBrowserItem::setDirectory(bool directory)
{
    _directory = directory;
}

void FileBrowserItem::setupUi()
{
    _layout = new QGridLayout();

    _iconContainer = new QWidget(this);
    _iconContainer->setLayout(new QVBoxLayout(_iconContainer));
    _iconContainer->setBaseSize(100,100);
    _iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    _layout->addWidget(_iconContainer,0,0,2,1);

    _iconLabel = new QLabel(this);
    _iconLabel->setFixedSize(100,100);
    _iconLabel->setAlignment(Qt::AlignCenter);
    _iconLabel->setText(QString("Icon"));
    _iconContainer->layout()->addWidget(_iconLabel);

    _titleLabel = new QLabel(this);
    _titleLabel->setText(QString("Name"));
    _layout->addWidget(_titleLabel,0,1,1,3);

    _sizeLabel = new QLabel(this);
    _sizeLabel->setText(QString("Printer"));
    _layout->addWidget(_sizeLabel,1,1,1,1);

    _spacer = new QSpacerItem(10,10, QSizePolicy::Ignored, QSizePolicy::Expanding);
    _layout->addWidget(_sizeLabel,1,2,1,1);

    _modifiedLabel = new QLabel(this);
    _modifiedLabel->setText(QString("Time Remaining"));
    _layout->addWidget(_modifiedLabel,1,3,1,1);

    setLayout(_layout);
}
