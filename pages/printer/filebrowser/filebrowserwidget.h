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
    enum DisplayMode
    {
        Page,
        Widget
    };

    FileBrowserWidget(QWidget *parent = nullptr, DisplayMode mode = Page);

    void addFile(KlipperFile file);
    void setFiles(const QList<KlipperFile> &files);

    FileBrowserItem *selectedItem();

private:
    DisplayMode m_displayMode = Page;
};

#endif // FILEBROWSERWIDGET_H
