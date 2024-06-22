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
    enum Mode
    {
        Page,
        Widget
    };

    FileBrowser(Printer *printer, QString root, QWidget *parent = nullptr, Mode mode = Page);
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
    void on_printer_startup(Printer *printer);

    //FileBrowserWidget
    void on_fileBrowserWidget_fileSelected(QAnimatedListItem *item);

    //Overlay
    void on_overlay_animatedOut();

private:
    bool m_startup = true;

    Printer *m_printer = nullptr;
    QString m_rootDirectory = QString("");
    QString m_currentDirectory = QString("");

    //UI
    FileBrowserWidget *m_filebrowserWidget = nullptr;

    QToolButton *m_refreshButton = nullptr;
    QToolButton *m_uploadFileButton = nullptr;
    QToolButton *m_newFolderButton = nullptr;
    QToolButton *m_downloadFolderButton = nullptr;
    QToolButton *m_upDirectoryButton = nullptr;

    QPushButton *m_printFileButton = nullptr;
    QPushButton *m_editFileButton = nullptr;
    QPushButton *m_deleteFileButton = nullptr;

    QLabel *m_currentDirectoryLabel = nullptr;
    QLabel *m_thumbnailLabel = nullptr;

    QWidget *m_actionBar = nullptr;
    QWidget *m_sideBar = nullptr;

    QGridLayout *m_layout = nullptr;
    QGridLayout *m_actionBarLayout = nullptr;
    QGridLayout *m_sideBarLayout = nullptr;

    FileEditor *m_editor = nullptr;

    FileBrowserOverlay *m_overlay = nullptr;

    Mode m_mode = Page;
};

#endif // FILEBROWSER_H
