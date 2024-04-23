#ifndef FILEBROWSERWIDGET_H
#define FILEBROWSERWIDGET_H

#include <QObject>

#include "../../../ui/list/qanimatedlistwidget.h"
#include "../../../types/klipperfile.h"
#include "filebrowseritem.h"

class FileBrowserWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    FileBrowserWidget(QWidget *parent = nullptr);

    void addFile(KlipperFile file);
    void setFiles(const QList<KlipperFile> &files);

    FileBrowserItem *selectedItem();

private:
};

#endif // FILEBROWSERWIDGET_H
