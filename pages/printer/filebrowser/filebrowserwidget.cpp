#include "filebrowserwidget.h"

FileBrowserWidget::FileBrowserWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{

}

void FileBrowserWidget::addFile(KlipperFile file)
{

}

void FileBrowserWidget::setFiles(const QList<KlipperFile> &files)
{
    clear();

    foreach(KlipperFile file, files)
        addFile(file);
}
