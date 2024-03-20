#include "filebrowserwidget.h"

FileBrowserWidget::FileBrowserWidget()
{
    this->scrollAreaContents = new QWidget(this);
    this->scrollAreaContents->setLayout(new QVBoxLayout(this->scrollAreaContents));
    this->scrollAreaContents->setLayoutDirection(Qt::LayoutDirectionAuto);
    this->scrollAreaContents->layout()->setContentsMargins(0,4,0,4);
    this->scrollAreaContents->layout()->setSpacing(0);
    this->setLayoutDirection(Qt::LayoutDirectionAuto);

    this->spacer = new QSpacerItem(20,20,QSizePolicy::Fixed,QSizePolicy::Expanding);
    this->scrollAreaContents->layout()->addItem(spacer);
    this->scrollAreaContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setWidget(scrollAreaContents);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setWidgetResizable(true);
}

FileBrowserWidget::~FileBrowserWidget()
{
    //delete this->spacer;
    //This might be being deleted by QScrollArea
    //delete this->scrollAreaContents;
}

void FileBrowserWidget::mouseMoveEvent(QMouseEvent *event)
{
    FileBrowserItem *item = (FileBrowserItem*)this->scrollAreaContents->childAt(event->position().x(), event->position().y());

    foreach(FileBrowserItem *otherItem, this->itemList)
    {
        if(otherItem != item)
            otherItem->showButtons(false);
        else
            item->showButtons(true);
    }

    qDebug() << event->position();
}

void FileBrowserWidget::addItem(FileBrowserItem *item)
{
    this->itemList.append(item);
    this->scrollAreaContents->layout()->removeItem(spacer);
    this->scrollAreaContents->layout()->addWidget(item);
    this->scrollAreaContents->layout()->addItem(spacer);

    connect(item, SIGNAL(clicked(FileBrowserItem*)), this, SLOT(on_itemClicked(FileBrowserItem*)));
    connect(item, SIGNAL(longPressed(FileBrowserItem*)), this, SLOT(on_itemLongPressed(FileBrowserItem*)));
}

void FileBrowserWidget::setItemList(QList<KlipperFile> files)
{
    this->clear();
    this->itemList.clear();
    this->fileList.clear();
    this->fileList.append(files);

    if(_currentDirectory != _rootDirectory)
    {
        FileBrowserItem *item = new FileBrowserItem(this);
        item->setName("..");
        item->setFileSize(0);
        item->setDateModified(QDateTime::fromSecsSinceEpoch(0));
        item->setDirectoryFlag(true);
        this->addItem(item);
    }

    foreach(KlipperFile file, this->fileList)
    {
        FileBrowserItem *item = new FileBrowserItem(this);
        item->setFile(file);
        item->setName(file.fileLocation);
        item->setFileSize(file.fileSize);
        item->setDateModified(QDateTime::fromSecsSinceEpoch(file.dateModified));
        item->setDirectoryFlag((file.type == KlipperFile::Directory));
        this->addItem(item);
    }
}

void FileBrowserWidget::clear()
{
    foreach(FileBrowserItem *item, this->itemList)
    {
        this->scrollAreaContents->layout()->removeWidget(item);
        disconnect(item, SIGNAL(clicked(FileBrowserItem*)), this, SLOT(on_itemClicked(FileBrowserItem*)));
        disconnect(item, SIGNAL(longPressed(FileBrowserItem*)), this, SLOT(on_itemLongPressed(FileBrowserItem*)));
        delete item;
    }

    this->itemList.clear();
}

QString FileBrowserWidget::currentDirectory()
{
    return this->_currentDirectory;
}

void FileBrowserWidget::setCurrentDirectory(QString directory)
{
    this->_currentDirectory = directory;
}

QString FileBrowserWidget::rootDirectory()
{
    return this->_rootDirectory;
}

void FileBrowserWidget::setRootDirectory(QString directory)
{
    this->_rootDirectory = directory;
}

void FileBrowserWidget::on_itemClicked(FileBrowserItem *item)
{
    emit(itemClicked(item));
}

void FileBrowserWidget::on_itemLongPressed(FileBrowserItem *item)
{
    emit(itemLongPressed(item));
}
