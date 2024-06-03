#include "filebrowseritem.h"
#include "../../../system/settings.h"

FileBrowserItem::FileBrowserItem(KlipperFile file, QWidget *parent, DisplayMode mode) :
    QAnimatedListItem(parent)
{
    _displayMode = mode;
    setFile(file);
    setupUi();
}

FileBrowserItem::~FileBrowserItem()
{
    if(_iconLabel)
        delete _iconLabel;

    if(_iconContainer)
        delete _iconContainer;

    if(_titleLabel)
        delete _titleLabel;

    if(_sizeLabel)
        delete _sizeLabel;

    if(_modifiedLabel)
        delete _modifiedLabel;

    if(_spacer)
        delete _spacer;

    if(_layout)
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
    _iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    _iconContainer->layout()->setContentsMargins(0,0,0,0);
    _layout->addWidget(_iconContainer,0,0,2,1);

    _iconLabel = new QLabel(this);
    _iconContainer->layout()->addWidget(_iconLabel);

    if(_displayMode == Page)
    {
        setFixedHeight(75);
        _iconContainer->setFixedWidth(50);
        _iconLabel->setFixedSize(30,30);
    }

    else
    {
        setFixedHeight(50);
        _iconContainer->setFixedWidth(45);
        _iconLabel->setFixedSize(30,30);
    }

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
        _titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _titleLabel->setWordWrap(true);
        _titleLabel->setText(_file.name);

        QString sizeFormat = " Bytes";
        qreal size = _file.fileSize;

        if(size > 1024)
        {
            size /= 1024;
            sizeFormat = " KB";

            if(size > 1024)
            {
                size /= 1024;
                sizeFormat = " MB";
            }
        }

        _sizeLabel = new QLabel(this);
        _sizeLabel->setText(QString::number(size) + sizeFormat);

        //_spacer = new QSpacerItem(10,10, QSizePolicy::Ignored, QSizePolicy::Expanding);

        _modifiedLabel = new QLabel(this);

        if(_displayMode == Page)
        {
            _layout->addWidget(_titleLabel,0,1,1,3);
            _layout->addWidget(_sizeLabel,1,1,1,1);
            //_layout->addItem(_spacer, 1, 2, 1, 1);
            _layout->addWidget(_modifiedLabel,1,2,1,1);
            _modifiedLabel->setText(QDateTime::fromSecsSinceEpoch(_file.dateModified).toString());
            _sizeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }

        else
        {
            _layout->addWidget(_titleLabel,0,1,1,1);
            _layout->addWidget(_sizeLabel,0,2,1,1);
            //_layout->addItem(_spacer, 0, 3, 1, 1);
            _layout->addWidget(_modifiedLabel,0,3,1,1);
            _modifiedLabel->setText(QDateTime::fromSecsSinceEpoch(_file.dateModified).toString("MM/dd/yy"));
            _sizeLabel->setFixedWidth(120);
        }
    }

    setLayout(_layout);
}
