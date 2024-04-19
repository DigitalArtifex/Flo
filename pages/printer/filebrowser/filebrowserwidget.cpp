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

    setAnimationSlide(item);
    addItem(item);
}

void FileBrowserWidget::setFiles(const QList<KlipperFile> &files)
{
    for(int i = 0; i < files.count(); i++)
    {
        FileBrowserItem *item = new FileBrowserItem(files[i],this);
        item->setFixedHeight(75);

        setAnimationSlide(item);
        item->setDuration(100 + (50 * i));

        addItem(item);
    }
}

FileBrowserItem *FileBrowserWidget::selectedItem()
{
    return (FileBrowserItem*)_selectedItems[0];
}
