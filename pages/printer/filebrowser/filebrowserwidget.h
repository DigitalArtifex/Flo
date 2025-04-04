#ifndef FILEBROWSERWIDGET_H
#define FILEBROWSERWIDGET_H

#include <QObject>

#include <QKlipper/qklipper.h>
#include "../../../ui/list/qanimatedlistwidget.h"
#include "filebrowseritem.h"
#include <qwizard.h>

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

    void addFile(QKlipperFile *file);
    void setFiles(const QKlipperFileList &files);

    FileBrowserItem *selectedItem();

signals:
    void itemDeleteRequested(FileBrowserItem *item);
    void itemEditRequested(FileBrowserItem *item);
    void itemPrintRequested(FileBrowserItem *item);
    void dialogRequested(QDialog *);
    void wizardRequested(QWizard *);

protected slots:
    void itemDeleteRequestedEvent(FileBrowserItem *item);
    void itemEditRequestedEvent(FileBrowserItem *item);
    void itemPrintRequestedEvent(FileBrowserItem *item);

private:
    DisplayMode m_displayMode = Page;
};

#endif // FILEBROWSERWIDGET_H
