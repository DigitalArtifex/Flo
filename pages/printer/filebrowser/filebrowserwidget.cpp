#include "filebrowserwidget.h"
#include "filebrowseritem.h"

FileBrowserWidget::FileBrowserWidget(QWidget *parent, DisplayMode mode) :
    QAnimatedListWidget(parent)
{
    _displayMode = mode;
}

void FileBrowserWidget::addFile(KlipperFile file)
{
    FileBrowserItem *item;

    if(_displayMode == Page)
        item = new FileBrowserItem(file,this);
    else
        item = new FileBrowserItem(file,this, FileBrowserItem::Widget);

    setAnimationSlide(item);
    addItem(item);
}

void FileBrowserWidget::setFiles(const QList<KlipperFile> &files)
{
    for(int i = 0; i < files.count(); i++)
    {
        FileBrowserItem *item;

        if(_displayMode == Page)
            item = new FileBrowserItem(files[i],this);
        else
            item = new FileBrowserItem(files[i],this, FileBrowserItem::Widget);

        setAnimationSlide(item);
        item->setDuration(100 + (50 * i));

        addItem(item);
    }
}

FileBrowserItem *FileBrowserWidget::selectedItem()
{
    return (FileBrowserItem*)_selectedItems[0];
}
