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

    explicit FileBrowserWidget(QWidget *parent = nullptr, DisplayMode mode = Page);
    ~FileBrowserWidget();

    void addFile(KlipperFile file);
    void setFiles(const QList<KlipperFile> &files);

    FileBrowserItem *selectedItem();

signals:
    void itemDeleteRequested(FileBrowserItem *item);
    void itemEditRequested(FileBrowserItem *item);
    void itemPrintRequested(FileBrowserItem *item);

protected slots:
    void itemDeleteRequestedEvent(FileBrowserItem *item);
    void itemEditRequestedEvent(FileBrowserItem *item);
    void itemPrintRequestedEvent(FileBrowserItem *item);

private:
    DisplayMode m_displayMode = Page;
};

#endif // FILEBROWSERWIDGET_H
