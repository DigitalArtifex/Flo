#include "filebrowserwidget.h"
#include "filebrowseritem.h"

FileBrowserWidget::FileBrowserWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{

}

void FileBrowserWidget::addFile(KlipperFile file)
{
    FileBrowserItem *item = new FileBrowserItem(file,this);
    item->setFixedHeight(75);
    addItem(item);
}

void FileBrowserWidget::setFiles(const QList<KlipperFile> &files)
{
    foreach(KlipperFile file, files)
        addFile(file);
}

FileBrowserItem *FileBrowserWidget::selectedItem()
{
    return (FileBrowserItem*)_selectedItems[0];
}
