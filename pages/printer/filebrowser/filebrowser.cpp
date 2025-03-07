#include "filebrowser.h"

#include "flo/settings.h"
#include "filebrowseritem.h"
#include "dialogs/MessageDialog/messagedialog.h"

FileBrowser::FileBrowser(QKlipperInstance *printer, QString root, QWidget *parent, Mode mode) :
    Page(parent)
{
    m_rootDirectory = root;
    m_mode = mode;

    setPrinter(printer);

    setupUi();
    setupConnections();

    setStyleSheet(Settings::currentTheme());
    setWindowTitle("G-Code File Browser");

    m_viewer = new QQuickView();
    m_viewerWidget = QWidget::createWindowContainer(m_viewer, this);
    m_viewerWidget->setFixedSize(0,0);
    m_layout->addWidget(m_viewerWidget);
    m_viewer->show();
}

FileBrowser::~FileBrowser()
{
    if(m_editor)
        delete m_editor;

    if(m_layout)
        delete m_layout;
}

QKlipperInstance *FileBrowser::printer() const
{
    return m_instance;
}

void FileBrowser::setPrinter(QKlipperInstance *printer)
{
    m_startup = true;
    m_instance = printer;

    connect(m_instance->server(), SIGNAL(fileListChanged(QString)), this, SLOT(onServerFileListChanged(QString)));
    //connect(m_instance, SIGNAL(connected(QKlipperInstance*)), this, SLOT(onInstanceConnected(QKlipperInstance*)));
}

void FileBrowser::setupUi()
{
    m_layout = new QGridLayout();
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    //Action bar
    m_actionBar = new QWidget();
    m_actionBarLayout = new QGridLayout(m_actionBar);
    m_actionBarLayout->setContentsMargins(4,4,4,4);

    m_upDirectoryButton = new QToolButton(m_actionBar);
    m_upDirectoryButton->setFixedSize(50,50);
    m_upDirectoryButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_upDirectoryButton, 0, 0, 1, 1);

    m_currentDirectoryLabel = new QLabel(m_actionBar);
    m_currentDirectoryLabel->setText(m_currentDirectory);
    m_currentDirectoryLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_actionBarLayout->addWidget(m_currentDirectoryLabel, 0, 1, 1, 1);

    QSpacerItem *actionSpacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_actionBarLayout->addItem(actionSpacer, 0, 2, 1, 1);

    m_refreshButton = new QToolButton(m_actionBar);
    m_refreshButton->setFixedSize(50,50);
    m_refreshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_refreshButton, 0, 3, 1, 1);

    m_uploadFileButton = new QToolButton(m_actionBar);
    m_uploadFileButton->setFixedSize(50,50);
    m_uploadFileButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_uploadFileButton, 0, 4, 1, 1);

    m_newFolderButton = new QToolButton(m_actionBar);
    m_newFolderButton->setFixedSize(50,50);
    m_newFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_newFolderButton, 0, 5, 1, 1);

    m_downloadFolderButton = new QToolButton(m_actionBar);
    m_downloadFolderButton->setFixedSize(50,50);
    m_downloadFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_downloadFolderButton, 0, 6, 1, 1);

    m_closeButton = new QIconButton(m_actionBar);
    m_closeButton->setIcon(Settings::getThemeIcon(QString("multiply")));
    m_closeButton->setFixedSize(50,50);
    m_closeButton->setTextMargins(QMargins(34,0,0,0));
    m_closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_actionBarLayout->addWidget(m_closeButton, 0, 7, 1, 1);

    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));

    m_actionBar->setLayout(m_actionBarLayout);
    m_layout->addWidget(m_actionBar, 0, 0, 1, 2);

    m_filebrowserWidget = new FileBrowserWidget(this, FileBrowserWidget::Widget);

    m_filebrowserWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addWidget(m_filebrowserWidget, 1, 0, 1, 1);

    //Side bar
    if(m_mode == PageMode)
    {
        m_sideBar = new QWidget();
        m_sideBar->setFixedWidth(250);
        m_sideBarLayout = new QGridLayout(m_sideBar);
        m_sideBarLayout->setContentsMargins(0,0,0,0);

        m_thumbnailLabel = new QLabel();
        m_thumbnailLabel->setFixedSize(200,200);
        m_sideBarLayout->addWidget(m_thumbnailLabel, 1, 0, 1, 1, Qt::AlignLeft);

        QPixmap pixmap = Settings::getThemeIcon("print").pixmap(28,28);
        m_printFileButton = new QIconButton(this);
        m_printFileButton->setFixedSize(250,50);
        m_printFileButton->setText("Print File");
        m_printFileButton->setIcon(Settings::getThemeIcon("print"));

        m_printFileButton->setEnabled(false);
        m_sideBarLayout->addWidget(m_printFileButton, 2, 0, 1, 1);

        pixmap = Settings::getThemeIcon("edit").pixmap(28,28);
        m_editFileButton = new QIconButton(this);
        m_editFileButton->setFixedSize(250,50);
        m_editFileButton->setText("Edit File");
        m_editFileButton->setIcon(Settings::getThemeIcon("edit"));

        m_printFileButton->setEnabled(false);
        m_sideBarLayout->addWidget(m_editFileButton, 3, 0, 1, 1);

        QSpacerItem *spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
        m_sideBarLayout->addItem(spacer, 4, 0, 1, 1, Qt::AlignLeft);

        pixmap = Settings::getThemeIcon("delete").pixmap(28,28);
        m_deleteFileButton = new QIconButton(this);
        m_deleteFileButton->setFixedSize(250,50);
        m_deleteFileButton->setText("Delete File");
        m_deleteFileButton->setIcon(Settings::getThemeIcon("delete"));

        m_printFileButton->setEnabled(false);
        m_sideBarLayout->addWidget(m_deleteFileButton, 5, 0, 1, 1);
    }

    m_sideBar->setLayout(m_sideBarLayout);

    m_actionBarLayout->setContentsMargins(4,4,4,4);

    setLayout(m_layout);

    if(m_sideBar)
        m_sideBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageSideBar"));

    m_upDirectoryButton->setIcon(Settings::getThemeIcon(QString("up-directory")));
    m_refreshButton->setIcon(Settings::getThemeIcon(QString("refresh")));
    m_uploadFileButton->setIcon(Settings::getThemeIcon(QString("file-upload")));
    m_newFolderButton->setIcon(Settings::getThemeIcon(QString("folder-create")));
    m_downloadFolderButton->setIcon(Settings::getThemeIcon(QString("folder-download")));

    m_editor = new FileEditor(m_instance, this);
    m_editor->hide();

    if(m_mode == PageMode)
    {

        if(m_rootDirectory != QString("gcodes"))
            m_printFileButton->setHidden(true);
        else
            m_printFileButton->setHidden(false);

        setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
        m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    }
    else
    {
        setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
        m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    }
}

void FileBrowser::setupConnections()
{
    connect(m_uploadFileButton, SIGNAL(clicked()), this, SLOT(onUploadFileButtonClicked()));
    connect(m_newFolderButton, SIGNAL(clicked()), this, SLOT(onNewFolderButtonClicked()));
    connect(m_downloadFolderButton, SIGNAL(clicked()), this, SLOT(onDownloadFolderButtonClicked()));
    connect(m_refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshButtonClicked()));
    connect(m_upDirectoryButton, SIGNAL(clicked()), this, SLOT(onUpDirectoryButtonClicked()));

    connect(m_filebrowserWidget, SIGNAL(itemSelected(QAnimatedListItem*)), this, SLOT(onFileBrowserWidgetFileSelected(QAnimatedListItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemDoubleClicked(QAnimatedListItem*)), this, SLOT(onFileBrowserWidgetItemDoubleClicked(QAnimatedListItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemDeleteRequested(FileBrowserItem*)), this, SLOT(onItemDeleteRequested(FileBrowserItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemEditRequested(FileBrowserItem*)), this, SLOT(onItemEditRequested(FileBrowserItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemPrintRequested(FileBrowserItem*)), this, SLOT(onItemPrintRequested(FileBrowserItem*)));
}

void FileBrowser::setIcons()
{
        m_upDirectoryButton->setIcon(Settings::getThemeIcon(QString("up-directory")));
        m_refreshButton->setIcon(Settings::getThemeIcon(QString("refresh")));
        m_uploadFileButton->setIcon(Settings::getThemeIcon(QString("file-upload")));
        m_newFolderButton->setIcon(Settings::getThemeIcon(QString("folder-create")));
        m_downloadFolderButton->setIcon(Settings::getThemeIcon(QString("folder-download")));
}

void FileBrowser::resizeEvent(QResizeEvent *event)
{
    // if(m_overlay)
    //     m_overlay->setGeometry(0,0,width(),height());

    Page::resizeEvent(event);
}

void FileBrowser::setActionsEnabled(bool enabled)
{
    m_refreshButton->setEnabled(enabled);
    m_uploadFileButton->setEnabled(enabled);
    m_newFolderButton->setEnabled(enabled);
    m_downloadFolderButton->setEnabled(enabled);
    m_upDirectoryButton->setEnabled(enabled);

    if(m_mode == PageMode)
    {
        m_printFileButton->setEnabled(enabled);
        m_editFileButton->setEnabled(enabled);
        m_deleteFileButton->setEnabled(enabled);
    }
}

void FileBrowser::showEvent(QShowEvent *event)
{
    if(m_instance->isConnected() && m_startup)
    {
        m_startup = false;
        m_instance->console()->serverFilesList(m_rootDirectory + QString("/") + m_currentDirectory);
    }
}

void FileBrowser::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();

    Page::changeEvent(event);
}

void FileBrowser::onUploadFileButtonClicked()
{
    //showOverlay(QString("Uploading Files"), QString("refresh"));

    QString fileTypes = QString("GCode (*.g *.gcode)");

    if(m_rootDirectory == "gcodes")
        fileTypes = QString("GCode (*.g *.gcode)");
    else if(m_rootDirectory == "config")
        fileTypes = QString("Config (*.cfg *.conf)");

    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "Select one or more files to open",
        QDir::homePath(),
        fileTypes);

    if(!files.isEmpty())
    {
        foreach(QString fileLocation, files)
        {
            QFile file(fileLocation);
            QString fileName = file.fileName();
            fileName.remove(0, fileName.lastIndexOf(QDir::separator()) + 1);

            if(file.open(QFile::ReadOnly))
            {
                m_instance->console()->serverFileUpload(
                    m_rootDirectory,
                    m_currentDirectory,
                    fileName,
                    file.readAll()
                );

                file.close();
            }
        }

        onRefreshButtonClicked();
    }
}

void FileBrowser::onNewFolderButtonClicked()
{
    if(!m_newFolderDialog)
    {
        m_newFolderDialog = new NewFolderDialog(this);

        dialogRequested(m_newFolderDialog);

        connect(m_newFolderDialog, SIGNAL(accepted(QString)), this, SLOT(newFolderDialogAcceptEvent(QString)));
        connect(m_newFolderDialog, SIGNAL(finished(int)), this, SLOT(onNewFolderDialogFinished(int)));
    }
}

void FileBrowser::onDownloadFolderButtonClicked()
{

}

void FileBrowser::onRefreshButtonClicked()
{
    m_currentDirectoryLabel->setText(m_rootDirectory + QString("/") + m_currentDirectory + QString("/"));
    m_instance->console()->serverFilesList(m_rootDirectory + QString("/") + m_currentDirectory);
}

void FileBrowser::onUpDirectoryButtonClicked()
{
    if(m_closeOnBack)
    {
        close();
        return;
    }

    //showOverlay(QString("Requesting Directory"), QString("refresh"));

    if(m_currentDirectory.contains(QString("/")))
        m_currentDirectory = m_currentDirectory.mid(0, m_currentDirectory.lastIndexOf(QString("/")));
    else
        m_currentDirectory.clear();

    onRefreshButtonClicked();
}

void FileBrowser::onInstanceConnected(QKlipperInstance *instance)
{
    Q_UNUSED(instance)

    m_instance->console()->serverFilesList(m_rootDirectory + QString("/") + m_currentDirectory);
}

void FileBrowser::onServerFileListChanged(const QString &directory)
{
    QString thisDirectory;

    if(m_currentDirectory.isEmpty())
        thisDirectory = m_rootDirectory + QString("/");
    else
        thisDirectory = m_rootDirectory + QString("/") + m_currentDirectory + QString("/");

    if(directory == thisDirectory)
    {
        QKlipperFileList files = m_instance->server()->fileList(thisDirectory);

        if(m_currentDirectory.isEmpty())
            m_closeOnBack = true;
        else
            m_closeOnBack = false;

        m_currentDirectoryLabel->setText(thisDirectory);

        m_filebrowserWidget->clear();
        m_filebrowserWidget->setFiles(files);

        m_refreshButton->setEnabled(true);
        m_uploadFileButton->setEnabled(true);
        m_newFolderButton->setEnabled(true);
        m_downloadFolderButton->setEnabled(files.count() > 0);

        //hideOverlay();
    }
}

void FileBrowser::onFileBrowserWidgetFileSelected(QAnimatedListItem *item)
{
    if(item)
    {
        if(m_mode == PageMode)
        {
            if(m_instance->printer()->status() == QKlipperPrinter::Ready)
                m_printFileButton->setEnabled(true);
            else
                m_printFileButton->setEnabled(false);
        }

        if(((FileBrowserItem*)item)->isDirectory())
        {
            if(m_currentDirectory.isEmpty())
                m_currentDirectory = ((FileBrowserItem*)item)->file()->filename();
            else
                m_currentDirectory += ((FileBrowserItem*)item)->file()->filename();

            m_currentDirectory.remove(m_rootDirectory);

            onRefreshButtonClicked();
        }
        else if(m_mode == PageMode)
        {
            m_editFileButton->setEnabled(true);
            m_deleteFileButton->setEnabled(true);
        }
    }
    else if(m_mode == PageMode)
    {
        m_editFileButton->setEnabled(false);
        m_deleteFileButton->setEnabled(false);
    }
}

void FileBrowser::onFileBrowserWidgetItemDoubleClicked(QAnimatedListItem *item)
{
    FileBrowserItem *fileItem = qobject_cast<FileBrowserItem*>(item);

    if(fileItem)
    {
        if(!fileItem->isDirectory())
        {
            if(fileItem->file()->fileType() == QKlipperFile::GCode)
            {

                m_filePreview = new FilePreviewWindow(fileItem->file(), m_instance, this);

                m_currentFile = fileItem->file();

                dialogRequested(m_filePreview);

                connect(m_filePreview, SIGNAL(finished(int)), this, SLOT(onFilePreviewDialogFinished(int)));
            }

            else
            {
                m_editor = new FileEditor(m_instance, this);
                m_editor->setFile(fileItem->file());

                int ret = m_editor->exec();
                delete m_editor;
                m_editor = nullptr;

                switch(ret)
                {
                case FileEditor::SaveAndRestart:
                    m_instance->console()->restartKlipper();
                    break;

                default:
                    break;
                }
            }
        }
    }
}

void FileBrowser::onItemDeleteRequested(FileBrowserItem *item)
{
    m_currentFile = item->file();

    m_messageBox = new MessageDialog(this);

    m_messageBox->setText("Confirm Delete");
    m_messageBox->setInformativeText("Are you sure you want to delete this file?");
    m_messageBox->setIcon(Settings::getThemeIcon("question"));
    m_messageBox->setRejectEnabled(true);

    emit dialogRequested(m_messageBox);
    connect(m_messageBox, SIGNAL(finished(int)), this, SLOT(onItemDeleteRequestDialogFinished(int)));

}

void FileBrowser::onItemDeleteRequestDialogFinished(int returnCode)
{
    switch(returnCode)
    {
    case QMessageBox::Ok:
        m_instance->console()->serverFileDelete(m_currentFile);
        break;
    default:
        break;
    }

    delete m_messageBox;
    m_currentFile = nullptr;
}

void FileBrowser::onItemEditRequested(FileBrowserItem *item)
{
    if(!m_editor)
        m_editor = new FileEditor(m_instance, this);

    m_editor->setFile(item->file());
    wizardRequested((QWizard*)m_editor);
}

void FileBrowser::onItemPrintRequested(FileBrowserItem *item)
{
    if(!m_filePreview && item->file()->fileType() == QKlipperFile::GCode)
    {
        QString theme = Settings::currentTheme();
        m_filePreview = new FilePreviewWindow(item->file(), m_instance, this);

        m_currentFile = item->file();

        dialogRequested(m_filePreview);

        connect(m_filePreview, SIGNAL(finished(int)), this, SLOT(onFilePreviewDialogFinished(int)));
    }
}

void FileBrowser::onFilePreviewDialogFinished(int returnCode)
{
    switch(returnCode)
    {
        case QDialog::Accepted:
            if(m_instance->printer()->status() == QKlipperPrinter::Ready)
            {
                m_instance->console()->printerPrintStart(m_currentFile);
            }
            else
            {
                m_messageBox = new MessageDialog(this);

                m_messageBox->setText("Could Not Start print");
                m_messageBox->setInformativeText("Printer is not ready");
                m_messageBox->setIcon(Settings::getThemeIcon("info"));

                emit dialogRequested(m_messageBox);
                connect(m_messageBox, SIGNAL(finished(int)), this, SLOT(onMessageDialogFinished(int)));
            }
            break;
        default:
            break;
    }

    delete m_filePreview;
    m_filePreview = nullptr;
    m_currentFile = nullptr;
}

void FileBrowser::onNewFolderDialogFinished(int returnCode)
{
    QString path;

    switch(returnCode)
    {
    case QDialog::Accepted:
        path = m_rootDirectory + QString("/");

        if(!m_currentDirectory.isEmpty())
            path += m_currentDirectory + QString("/");

        path += m_newFolderDialog->value();

        if(m_newFolderDialog)
        {
            delete m_newFolderDialog;
            m_newFolderDialog = nullptr;
        }

        //showOverlay(QString("Creating Folder"), QString("folder"));

        m_instance->console()->serverDirectoryPost(path);
        break;
    default:
        break;
    }

    delete m_newFolderDialog;
    m_newFolderDialog = nullptr;
}

void FileBrowser::onMessageDialogFinished(int returnCode)
{
    Q_UNUSED(returnCode)

    delete m_messageBox;
    m_messageBox = nullptr;
}
