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
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>

#include <QKlipper/qklipper.h>
#include "common/Page/page.h"
#include "filebrowserwidget.h"
#include <qquickview.h>

#include "editor/fileeditor.h"
#include "preview/filepreviewwindow.h"
#include "newfolder/newfolderdialog.h"

#include "ui/QIconButton/qiconbutton.h"
#include "common/dialog/dialog.h"
#include "dialogs/MessageDialog/messagedialog.h"

class FileBrowser : public Page
{
    Q_OBJECT
public:
    enum Mode
    {
        PageMode,
        WidgetMode
    };

    FileBrowser(QKlipperInstance *printer, QString root, QWidget *parent = nullptr, Mode mode = PageMode);
    ~FileBrowser();

    QKlipperInstance *printer() const;
    void setPrinter(QKlipperInstance *printer);

    virtual void setupUi();
    virtual void setupConnections();
    virtual void setIcons();
    virtual void resizeEvent(QResizeEvent *event) override;

    void setActionsEnabled(bool enabled);

signals:
    void dialogRequested(QDialog *);
    void wizardRequested(QWizard *);

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void changeEvent(QEvent *event) override;

private slots:
    //Tool buttons
    void onUploadFileButtonClicked();
    void onNewFolderButtonClicked();
    void onDownloadFolderButtonClicked();
    void onRefreshButtonClicked();
    void onUpDirectoryButtonClicked();

    //Printer
    void onInstanceConnected(QKlipperInstance *instance);
    void onServerFileListChanged(const QString &directory);

    //FileBrowserWidget
    void onFileBrowserWidgetFileSelected(QAnimatedListItem *item);
    void onFileBrowserWidgetItemDoubleClicked(QAnimatedListItem *item);

    //Item context menu
    void onItemDeleteRequested(FileBrowserItem *item);
    void onItemDeleteRequestDialogFinished(int returnCode);

    void onItemEditRequested(FileBrowserItem *item);
    void onItemPrintRequested(FileBrowserItem *item);

    void onFilePreviewDialogFinished(int returnCode);
    void onNewFolderDialogFinished(int returnCode);
    void onMessageDialogFinished(int returnCode);

private:
    bool m_startup = true;
    bool m_closeOnBack = false;

    QKlipperInstance *m_instance = nullptr;
    QString m_rootDirectory = QString("");
    QString m_currentDirectory = QString("");

    QKlipperFile *m_currentFile = nullptr;
    MessageDialog *m_messageBox = nullptr;

    //UI
    FileBrowserWidget *m_filebrowserWidget = nullptr;

    QToolButton *m_refreshButton = nullptr;
    QToolButton *m_uploadFileButton = nullptr;
    QToolButton *m_newFolderButton = nullptr;
    QToolButton *m_downloadFolderButton = nullptr;
    QToolButton *m_upDirectoryButton = nullptr;
    QIconButton *m_closeButton = nullptr;

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

    FilePreviewWindow  *m_filePreview = nullptr;
    NewFolderDialog    *m_newFolderDialog = nullptr;

    Mode m_mode = PageMode;
    QQuickView *m_viewer = nullptr;
    QWidget *m_viewerWidget = nullptr;
    QQuickWidget *m_quickWidget = nullptr;
};

#endif // FILEBROWSER_H
