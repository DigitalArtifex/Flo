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

#include <QKlipper/qklipper.h>
#include "filebrowserwidget.h"

#include "editor/fileeditor.h"
#include "overlay/filebrowseroverlay.h"
#include "preview/filepreviewwindow.h"
#include "newfolder/newfolderdialog.h"

#include "ui/QIconButton/qiconbutton.h"
#include "ui/common/dialog/dialog.h"

class FileBrowser : public Dialog
{
    Q_OBJECT
public:
    enum Mode
    {
        Page,
        Widget
    };

    FileBrowser(QKlipperInstance *printer, QString root, QWidget *parent = nullptr, Mode mode = Page);
    ~FileBrowser();

    QKlipperInstance *printer() const;
    void setPrinter(QKlipperInstance *printer);

    virtual void setupUi();
    virtual void setupConnections();
    virtual void setStyleSheet(const QString &styleSheet);
    virtual void resizeEvent(QResizeEvent *event);

    void showOverlay(QString title, QString icon);
    void hideOverlay();
    void setActionsEnabled(bool enabled);

private slots:
    //Tool buttons
    void uploadFileButtonClickEvent();
    void newFolderButtonClickEvent();
    void downloadFolderButtonClickEvent();
    void refreshButtonClickEvent();
    void upDirectoryButtonClickEvent();

    //Pushbuttons
    void printFileButtonClickEvent();
    void editFileButtonClickEvent();
    void deleteFileButtonClickEvent();

    //Printer
    void onInstanceConnected(QKlipperInstance *instance);
    void onServerFileListChanged(const QString &directory);

    //FileBrowserWidget
    void onFileBrowserWidgetFileSelected(QAnimatedListItem *item);
    void onFileBrowserWidgetItemDoubleClicked(QAnimatedListItem *item);

    //Overlay
    void overlayAnimatedOutEvent();
    void overlayAnimatedInEvent();

    //New Folder Dialog
    void newFolderDialogAcceptEvent(QString value);
    void newFolderDialogRejectEvent();

    //Item context menu
    void itemDeleteRequestedEvent(FileBrowserItem *item);
    void itemEditRequestedEvent(FileBrowserItem *item);
    void itemPrintRequestedEvent(FileBrowserItem *item);

private:
    bool m_startup = true;

    QKlipperInstance *m_instance = nullptr;
    QString m_rootDirectory = QString("");
    QString m_currentDirectory = QString("");

    //UI
    FileBrowserWidget *m_filebrowserWidget = nullptr;

    QToolButton *m_refreshButton = nullptr;
    QToolButton *m_uploadFileButton = nullptr;
    QToolButton *m_newFolderButton = nullptr;
    QToolButton *m_downloadFolderButton = nullptr;
    QToolButton *m_upDirectoryButton = nullptr;

    QIconButton *m_printFileButton = nullptr;
    QIconButton *m_editFileButton = nullptr;
    QIconButton *m_deleteFileButton = nullptr;

    QLabel *m_currentDirectoryLabel = nullptr;
    QLabel *m_thumbnailLabel = nullptr;

    QWidget *m_actionBar = nullptr;
    QWidget *m_sideBar = nullptr;

    QGridLayout *m_layout = nullptr;
    QGridLayout *m_actionBarLayout = nullptr;
    QGridLayout *m_sideBarLayout = nullptr;

    FileEditor *m_editor = nullptr;

    FileBrowserOverlay *m_overlay = nullptr;
    FilePreviewWindow  *m_filePreview = nullptr;
    NewFolderDialog    *m_newFolderDialog = nullptr;

    Mode m_mode = Page;
};

#endif // FILEBROWSER_H
