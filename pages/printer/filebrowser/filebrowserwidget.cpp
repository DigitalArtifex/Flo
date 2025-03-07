#include "filebrowserwidget.h"
#include "filebrowseritem.h"

FileBrowserWidget::FileBrowserWidget(QWidget *parent, DisplayMode mode) :
    QAnimatedListWidget(parent)
{
    m_displayMode = mode;
    scrollAreaContents()->layout()->setContentsMargins(0,0,0,0);
}

FileBrowserWidget::~FileBrowserWidget()
{
}

void FileBrowserWidget::addFile(QKlipperFile *file)
{
    FileBrowserItem *item;

    if(m_displayMode == Page)
        item = new FileBrowserItem(file,this);
    else
        item = new FileBrowserItem(file,this, FileBrowserItem::Widget);

    connect(item, SIGNAL(deleteRequested(FileBrowserItem*)), this, SLOT(itemDeleteRequestedEvent(FileBrowserItem*)));
    connect(item, SIGNAL(editRequested(FileBrowserItem*)), this, SLOT(itemEditRequestedEvent(FileBrowserItem*)));
    connect(item, SIGNAL(printRequested(FileBrowserItem*)), this, SLOT(itemPrintRequestedEvent(FileBrowserItem*)));

    addItem(item);
}

void FileBrowserWidget::setFiles(const QKlipperFileList &files)
{
    for(int i = 0; i < files.count(); i++)
    {
        FileBrowserItem *item;

        if(m_displayMode == Page)
            item = new FileBrowserItem(files[i],this);
        else
            item = new FileBrowserItem(files[i],this, FileBrowserItem::Widget);

        connect(item, SIGNAL(deleteRequested(FileBrowserItem*)), this, SLOT(itemDeleteRequestedEvent(FileBrowserItem*)));
        connect(item, SIGNAL(editRequested(FileBrowserItem*)), this, SLOT(itemEditRequestedEvent(FileBrowserItem*)));
        connect(item, SIGNAL(printRequested(FileBrowserItem*)), this, SLOT(itemPrintRequestedEvent(FileBrowserItem*)));

        addItem(item);
    }
}

FileBrowserItem *FileBrowserWidget::selectedItem()
{
    return (FileBrowserItem*)m_selectedItems[0];
}

void FileBrowserWidget::itemDeleteRequestedEvent(FileBrowserItem *item)
{
    emit itemDeleteRequested(item);
}

void FileBrowserWidget::itemEditRequestedEvent(FileBrowserItem *item)
{
    emit itemEditRequested(item);
}

void FileBrowserWidget::itemPrintRequestedEvent(FileBrowserItem *item)
{
    emit itemPrintRequested(item);
}
