#include "filebrowseritem.h"
#include "../../../system/settings.h"

FileBrowserItem::FileBrowserItem(KlipperFile file, QWidget *parent) :
    QAnimatedListItem(parent)
{
    setFile(file);
    setupUi();
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

    if(_file.type == KlipperFile::Directory)
        _directory = true;
}

bool FileBrowserItem::isDirectory() const
{
    return (_file.type == KlipperFile::Directory);
}

void FileBrowserItem::setupUi()
{
    _layout = new QGridLayout();

    _iconContainer = new QWidget(this);
    _iconContainer->setLayout(new QVBoxLayout(_iconContainer));
    _iconContainer->setFixedWidth(50);
    _iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    _layout->addWidget(_iconContainer,0,0,2,1);

    _iconLabel = new QLabel(this);
    _iconLabel->setFixedSize(30,30);
    _iconLabel->setText(QString("Icon"));
    _iconContainer->layout()->addWidget(_iconLabel);

    if(_directory)
    {
        QPixmap icon = Settings::getThemeIcon(QString("folder-icon")).pixmap(30,30);
        _iconLabel->setPixmap(icon);

        _titleLabel = new QLabel(this);
        _titleLabel->setText(_file.name);
        _layout->addWidget(_titleLabel,0,1,1,1);
    }
    else
    {
        QPixmap icon = Settings::getThemeIcon(QString("file-icon")).pixmap(30,30);
        _iconLabel->setPixmap(icon);

        _titleLabel = new QLabel(this);
        _titleLabel->setText(_file.name);
        _layout->addWidget(_titleLabel,0,1,1,3);

        _sizeLabel = new QLabel(this);
        _sizeLabel->setText(QString::number(_file.fileSize) + QString(" Bytes"));
        _layout->addWidget(_sizeLabel,1,1,1,1);

        _spacer = new QSpacerItem(10,10, QSizePolicy::Ignored, QSizePolicy::Expanding);
        _layout->addWidget(_sizeLabel,1,2,1,1);

        _modifiedLabel = new QLabel(this);
        _modifiedLabel->setText(QDateTime::fromSecsSinceEpoch(_file.dateModified).toString());
        _layout->addWidget(_modifiedLabel,1,3,1,1);
    }

    setLayout(_layout);
    setFixedHeight(50);
}
