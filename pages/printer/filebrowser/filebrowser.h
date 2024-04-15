#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QObject>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>

#include "../../../types/printer.h"
#include "../../../types/klipperfile.h"
#include "filebrowserwidget.h"
#include "filebrowseritem.h"

#include "editor/fileeditor.h"
#include "overlay/filebrowseroverlay.h"

class FileBrowser : public QWidget
{
    Q_OBJECT
public:
    FileBrowser(Printer *printer, QString root, QWidget *parent = nullptr);
    ~FileBrowser();

    Printer *printer() const;
    void setPrinter(Printer *printer);

    virtual void setupUi();
    virtual void setupConnections();
    virtual void setStyleSheet(const QString &styleSheet);
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    //Tool buttons
    void on_uploadFileButton_clicked(bool clicked);
    void on_newFolderButton_clicked(bool clicked);
    void on_downloadFolderButton_clicked(bool clicked);
    void on_refreshButton_clicked(bool clicked);
    void on_upDirectoryButton_clicked(bool clicked);

    //Pushbuttons
    void on_printFileButton_clicked();
    void on_editFileButton_clicked();
    void on_deleteFileButton_clicked();

    //Printer
    void on_printer_update(Printer *printer);
    void on_printer_fileListing(QString root, QString directory, QList<KlipperFile> files, Printer *printer);

    //FileBrowserWidget
    void on_fileBrowserWidget_fileSelected(QAnimatedListItem *item);

    //Overlay
    void on_overlay_animatedOut();

private:
    bool _startup = true;

    Printer *_printer = nullptr;
    QString _rootDirectory = QString("");
    QString _currentDirectory = QString("");

    //UI
    FileBrowserWidget *_filebrowserWidget = nullptr;

    QToolButton *_refreshButton = nullptr;
    QToolButton *_uploadFileButton = nullptr;
    QToolButton *_newFolderButton = nullptr;
    QToolButton *_downloadFolderButton = nullptr;
    QToolButton *_upDirectoryButton = nullptr;

    QPushButton *_printFileButton = nullptr;
    QPushButton *_editFileButton = nullptr;
    QPushButton *_deleteFileButton = nullptr;

    QLabel *_currentDirectoryLabel = nullptr;
    QLabel *_thumbnailLabel = nullptr;

    QWidget *_actionBar = nullptr;
    QWidget *_sideBar = nullptr;

    QGridLayout *_layout = nullptr;
    QGridLayout *_actionBarLayout = nullptr;
    QGridLayout *_sideBarLayout = nullptr;

    FileEditor *_editor = nullptr;

    FileBrowserOverlay *_overlay = nullptr;
};

#endif // FILEBROWSER_H
