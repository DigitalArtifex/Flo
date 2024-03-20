#ifndef FILEBROWSERPAGE_H
#define FILEBROWSERPAGE_H

#include <QFrame>
#include <QList>
#include <QLayout>
#include <QLayout>

#include "../../types/klipperfile.h"
#include "filebrowseritem.h"
#include "filebrowserwidget.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QScreen>
#include <QRegularExpression>
#include "../../ui/popup.h"

namespace Ui {
class FileBrowserPage;
}



class FileBrowserPage : public QFrame
{
    Q_OBJECT

    QList<KlipperFile> fileList;
    QList<FileBrowserItem*> itemList;
    QSpacerItem *spacer;

    FileBrowserWidget *fileWidget;

    QString _rootDirectory = "gcodes";
    QString _currentDirectory = "gcodes";
    Popup *popup;

public:
    explicit FileBrowserPage(QString rootDirectory = "gcodes", QWidget *parent = nullptr);
    ~FileBrowserPage();

    void setFileList(QList<KlipperFile> files);
    void setIcons();

    void setCurrentDirectory(QString directory);

signals:
    void refreshRequested(QString directory);
    void printRequested(KlipperFile file);
    void deleteRequested(KlipperFile file);
    void createDirectory(KlipperFile directory);
    void deleteDirectory(KlipperFile directory);

private slots:
    void on_fileRefreshButton_clicked();
    void on_fileRefreshButton_2_clicked();
    void on_itemClicked(FileBrowserItem* item);
    void on_itemLongPressed(FileBrowserItem* item);

    void on_folderCreateButton_clicked();

    void on_popupCancelled(QVariant data);
    void on_popupAccepted(QVariant data);
    void on_popupFileDelete(QVariant file);
    void on_popupFilePrint(QVariant file);
    void on_popupNewFolder(QVariant folder);
    void on_popupDeleteFolder(QVariant folder);

    void on_fileUploadButton_clicked();

private:
    Ui::FileBrowserPage *ui;

    void setupUiClasses();
};

#endif // FILEBROWSERPAGE_H
