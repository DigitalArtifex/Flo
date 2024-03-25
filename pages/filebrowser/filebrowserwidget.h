#ifndef FILEBROWSERWIDGET_H
#define FILEBROWSERWIDGET_H

#include <QScrollArea>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QLayout>
#include <QSpacerItem>

#include "../../system/settings.h"
#include "filebrowseritem.h"

class FileBrowserWidget : public QScrollArea
{
    Q_OBJECT

public:
    FileBrowserWidget();
    ~FileBrowserWidget();

    virtual void mouseMoveEvent(QMouseEvent *event);
    void addItem(FileBrowserItem *item);
    void setItemList(QList<KlipperFile> list);
    void clear();

    QString currentDirectory();
    void setCurrentDirectory(QString directory);

    QString rootDirectory();
    void setRootDirectory(QString directory);

signals:
    void itemClicked(FileBrowserItem *item);
    void itemLongPressed(FileBrowserItem *item);

private slots:
    void on_itemClicked(FileBrowserItem *item);
    void on_itemLongPressed(FileBrowserItem *item);

private:

    QWidget *scrollAreaContents;
    QSpacerItem *spacer;
    QString _rootDirectory;
    QString _currentDirectory;
    QList<FileBrowserItem*> itemList;
    QList<KlipperFile> fileList;

};

#endif // FILEBROWSERWIDGET_H
