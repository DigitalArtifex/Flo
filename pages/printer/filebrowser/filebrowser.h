#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QObject>
#include <QLabel>
#include <QToolButton>
#include <QIcon>
#include <QPixmap>
#include <QGridLayout>

#include "../../../types/printer.h"
#include "../../../types/klipperfile.h"
#include "filebrowserwidget.h"

class FileBrowser : public QWidget
{
    Q_OBJECT
public:
    FileBrowser(Printer *printer, QString root, QWidget *parent = nullptr);

    QString fileRoot() const;
    void setFileRoot(const QString &fileRoot);

    Printer *printer() const;
    void setPrinter(Printer *printer);

    QString currentDirectory() const;
    void setCurrentDirectory(const QString &currentDirectory);

    QList<KlipperFile> files() const;
    void setFiles(const QList<KlipperFile> &files);

    virtual void setupUi();
    virtual void setupConnections();
    virtual void setStyleSheet(QString styleSheet);

private slots:
    void on_uploadFileButton_clicked(bool clicked);
    void on_newFolderButton_clicked(bool clicked);
    void on_downloadFolderButton_clicked(bool clicked);
    void on_refreshButton_clicked(bool clicked);

private:
    Printer *_printer = nullptr;
    QString _fileRoot = QString("");
    QString _currentDirectory = QString("");
    QList<KlipperFile> _files = QList<KlipperFile>();

    //UI
    FileBrowserWidget *_filebrowserWidget = nullptr;

    QToolButton *_refreshButton = nullptr;
    QToolButton *_uploadFileButton = nullptr;
    QToolButton *_newFolderButton = nullptr;
    QToolButton *_downloadFolderButton = nullptr;

    QLabel *_currentDirectoryLabel = nullptr;

    QWidget *_actionBar = nullptr;

    QGridLayout *_layout = nullptr;
    QGridLayout *_actionBarLayout = nullptr;
};

#endif // FILEBROWSER_H
