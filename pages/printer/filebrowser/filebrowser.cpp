#include "filebrowser.h"

#include "system/settings.h"
#include "filebrowseritem.h"
#include "ui/messagedialog.h"

FileBrowser::FileBrowser(QKlipperInstance *printer, QString root, QWidget *parent, Mode mode) :
    QWidget(parent)
{
    m_rootDirectory = root;
    m_mode = mode;

    setPrinter(printer);

    setupUi();
    setupConnections();

    setStyleSheet(Settings::currentTheme());
}

FileBrowser::~FileBrowser()
{
    if(m_overlay)
        m_overlay->deleteLater();

    if(m_editor)
        m_editor->deleteLater();

    if(m_layout)
        m_layout->deleteLater();
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
    connect(m_instance, SIGNAL(connected(QKlipperInstance*)), this, SLOT(onInstanceConnected(QKlipperInstance*)));
}

void FileBrowser::setupUi()
{
    m_layout = new QGridLayout();
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    //Action bar
    m_actionBar = new QWidget();
    m_actionBarLayout = new QGridLayout(m_actionBar);
    m_actionBarLayout->setContentsMargins(9,9,9,9);

    m_upDirectoryButton = new QToolButton(m_actionBar);
    m_upDirectoryButton->setEnabled(false);
    m_upDirectoryButton->setFixedSize(35,35);
    m_upDirectoryButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_upDirectoryButton, 0, 0, 1, 1);

    m_currentDirectoryLabel = new QLabel(m_actionBar);
    m_currentDirectoryLabel->setText(m_currentDirectory);
    m_currentDirectoryLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_actionBarLayout->addWidget(m_currentDirectoryLabel, 0, 1, 1, 1);

    QSpacerItem *actionSpacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_actionBarLayout->addItem(actionSpacer, 0, 2, 1, 1);

    m_refreshButton = new QToolButton(m_actionBar);
    m_refreshButton->setFixedSize(35,35);
    m_refreshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_refreshButton, 0, 3, 1, 1);

    m_uploadFileButton = new QToolButton(m_actionBar);
    m_uploadFileButton->setFixedSize(35,35);
    m_uploadFileButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_uploadFileButton, 0, 4, 1, 1);

    m_newFolderButton = new QToolButton(m_actionBar);
    m_newFolderButton->setFixedSize(35,35);
    m_newFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_newFolderButton, 0, 5, 1, 1);

    m_downloadFolderButton = new QToolButton(m_actionBar);
    m_downloadFolderButton->setFixedSize(35,35);
    m_downloadFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_downloadFolderButton, 0, 6, 1, 1);

    m_actionBar->setLayout(m_actionBarLayout);
    m_layout->addWidget(m_actionBar, 0, 0, 1, 2);


    m_filebrowserWidget = new FileBrowserWidget(this, FileBrowserWidget::Widget);

    m_filebrowserWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addWidget(m_filebrowserWidget, 1, 0, 1, 1);

    //Side bar
    if(m_mode == Page)
    {
        m_sideBar = new QWidget();
        m_sideBar->setFixedWidth(250);
        m_sideBarLayout = new QGridLayout(m_sideBar);
        m_sideBarLayout->setContentsMargins(0,0,0,0);

        m_thumbnailLabel = new QLabel();
        m_thumbnailLabel->setFixedSize(200,200);
        m_sideBarLayout->addWidget(m_thumbnailLabel, 1, 0, 1, 1, Qt::AlignLeft);

        QPixmap pixmap = Settings::getThemeIcon("print-icon").pixmap(28,28);
        m_printFileButton = new QIconButton(this);
        m_printFileButton->setFixedSize(250,50);
        m_printFileButton->setText("Print File");
        m_printFileButton->setIcon(Settings::getThemeIcon("print-icon"));

        m_printFileButton->setEnabled(false);
        m_sideBarLayout->addWidget(m_printFileButton, 2, 0, 1, 1);

        pixmap = Settings::getThemeIcon("edit-icon").pixmap(28,28);
        m_editFileButton = new QIconButton(this);
        m_editFileButton->setFixedSize(250,50);
        m_editFileButton->setText("Edit File");
        m_editFileButton->setIcon(Settings::getThemeIcon("edit-icon"));

        m_printFileButton->setEnabled(false);
        m_sideBarLayout->addWidget(m_editFileButton, 3, 0, 1, 1);

        QSpacerItem *spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
        m_sideBarLayout->addItem(spacer, 4, 0, 1, 1, Qt::AlignLeft);

        pixmap = Settings::getThemeIcon("delete-icon").pixmap(28,28);
        m_deleteFileButton = new QIconButton(this);
        m_deleteFileButton->setFixedSize(250,50);
        m_deleteFileButton->setText("Delete File");
        m_deleteFileButton->setIcon(Settings::getThemeIcon("delete-icon"));

        m_printFileButton->setEnabled(false);
        m_sideBarLayout->addWidget(m_deleteFileButton, 5, 0, 1, 1);
    }

    m_sideBar->setLayout(m_sideBarLayout);
    m_upDirectoryButton->setFixedSize(32,32);
    m_newFolderButton->setFixedSize(32,32);
    m_uploadFileButton->setFixedSize(32,32);
    m_downloadFolderButton->setFixedSize(32,32);
    m_refreshButton->setFixedSize(32,32);

    m_actionBarLayout->setContentsMargins(4,4,4,4);

    setLayout(m_layout);

    if(m_sideBar)
        m_sideBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageSideBar"));

    m_upDirectoryButton->setIcon(Settings::getThemeIcon(QString("up-directory-icon")));
    m_refreshButton->setIcon(Settings::getThemeIcon(QString("refresh-icon")));
    m_uploadFileButton->setIcon(Settings::getThemeIcon(QString("file-upload-icon")));
    m_newFolderButton->setIcon(Settings::getThemeIcon(QString("folder-create-icon")));
    m_downloadFolderButton->setIcon(Settings::getThemeIcon(QString("folder-download-icon")));

    if(m_mode == Page)
    {
        setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
        m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));

        if(m_rootDirectory != QString("gcodes"))
            m_printFileButton->setHidden(true);
        else
            m_printFileButton->setHidden(false);

        m_editor = new FileEditor(m_instance, this);
        m_editor->hide();
    }
    else
    {
        setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
        m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    }
}

void FileBrowser::setupConnections()
{
    connect(m_uploadFileButton, SIGNAL(clicked()), this, SLOT(uploadFileButtonClickEvent()));
    connect(m_newFolderButton, SIGNAL(clicked()), this, SLOT(newFolderButtonClickEvent()));
    connect(m_downloadFolderButton, SIGNAL(clicked()), this, SLOT(downloadFolderButtonClickEvent()));
    connect(m_refreshButton, SIGNAL(clicked()), this, SLOT(refreshButtonClickEvent()));
    connect(m_upDirectoryButton, SIGNAL(clicked()), this, SLOT(upDirectoryButtonClickEvent()));

    connect(m_filebrowserWidget, SIGNAL(itemSelected(QAnimatedListItem*)), this, SLOT(onFileBrowserWidgetFileSelected(QAnimatedListItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemDoubleClicked(QAnimatedListItem*)), this, SLOT(onFileBrowserWidgetItemDoubleClicked(QAnimatedListItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemDeleteRequested(FileBrowserItem*)), this, SLOT(itemDeleteRequestedEvent(FileBrowserItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemEditRequested(FileBrowserItem*)), this, SLOT(itemEditRequestedEvent(FileBrowserItem*)));
    connect(m_filebrowserWidget, SIGNAL(itemPrintRequested(FileBrowserItem*)), this, SLOT(itemPrintRequestedEvent(FileBrowserItem*)));
}

void FileBrowser::setStyleSheet(const QString &styleSheet)
{
    QWidget::setStyleSheet(styleSheet);

    if(m_filebrowserWidget)
        m_filebrowserWidget->setStyleSheet(styleSheet);

    if(m_overlay)
        m_overlay->setStyleSheet(styleSheet);

    m_upDirectoryButton->setIcon(Settings::getThemeIcon(QString("up-directory-icon")));
    m_refreshButton->setIcon(Settings::getThemeIcon(QString("refresh-icon")));
    m_uploadFileButton->setIcon(Settings::getThemeIcon(QString("file-upload-icon")));
    m_newFolderButton->setIcon(Settings::getThemeIcon(QString("folder-create-icon")));
    m_downloadFolderButton->setIcon(Settings::getThemeIcon(QString("folder-download-icon")));
}

void FileBrowser::resizeEvent(QResizeEvent *event)
{
    if(m_overlay)
        m_overlay->setGeometry(0,0,width(),height());
}

void FileBrowser::showOverlay(QString title, QString icon)
{
    if(!m_overlay)
    {
        m_overlay = new FileBrowserOverlay(this);

        connect(m_overlay,SIGNAL(animatedOut()),this,SLOT(overlayAnimatedOutEvent()));

        m_overlay->resize(size());
        m_overlay->setText(title);
        m_overlay->setIcon(Settings::getThemeIcon(icon));
        m_overlay->show();
        m_overlay->animateIn();
    }
}

void FileBrowser::hideOverlay()
{
    if(m_overlay)
        m_overlay->animateOut();
}

void FileBrowser::setActionsEnabled(bool enabled)
{
    m_refreshButton->setEnabled(enabled);
    m_uploadFileButton->setEnabled(enabled);
    m_newFolderButton->setEnabled(enabled);
    m_downloadFolderButton->setEnabled(enabled);
    m_upDirectoryButton->setEnabled(enabled);

    if(m_mode == Page)
    {
        m_printFileButton->setEnabled(enabled);
        m_editFileButton->setEnabled(enabled);
        m_deleteFileButton->setEnabled(enabled);
    }
}

void FileBrowser::uploadFileButtonClickEvent()
{
    showOverlay(QString("Uploading Files"), QString("refresh-icon"));

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

        refreshButtonClickEvent();
    }
    else
        hideOverlay();
}

void FileBrowser::newFolderButtonClickEvent()
{
    if(!m_newFolderDialog)
    {
        QString theme = Settings::currentTheme();

        m_newFolderDialog = new NewFolderDialog(this);
        m_newFolderDialog->setStyleSheet(theme);

        connect(m_newFolderDialog, SIGNAL(accepted(QString)), this, SLOT(newFolderDialogAcceptEvent(QString)));
        connect(m_newFolderDialog, SIGNAL(rejected()), this, SLOT(newFolderDialogRejectEvent()));

        m_newFolderDialog->exec();
    }
}

void FileBrowser::downloadFolderButtonClickEvent()
{

}

void FileBrowser::refreshButtonClickEvent()
{
    showOverlay(QString("Refreshing Directory"), QString("refresh-icon"));

    m_currentDirectoryLabel->setText(m_rootDirectory + QString("/") + m_currentDirectory + QString("/"));

    m_filebrowserWidget->clear();
    m_instance->console()->serverFilesList(m_rootDirectory + QString("/") + m_currentDirectory);
}

void FileBrowser::upDirectoryButtonClickEvent()
{
    showOverlay(QString("Requesting Directory"), QString("refresh-icon"));

    if(m_currentDirectory.contains(QString("/")))
        m_currentDirectory = m_currentDirectory.mid(0, m_currentDirectory.lastIndexOf(QString("/")));
    else
        m_currentDirectory.clear();

    refreshButtonClickEvent();
}

void FileBrowser::printFileButtonClickEvent()
{
    FileBrowserItem *fileItem = m_filebrowserWidget->selectedItem();

    if(!m_filePreview && fileItem)
    {
        QString theme = Settings::currentTheme();
        m_filePreview = new FilePreviewWindow(fileItem->file(), m_instance, this);
        m_filePreview->setWindowFlag(Qt::Popup);
        m_filePreview->setStyleSheet(theme);

        int ret = m_filePreview->exec();

        switch(ret)
        {
        case QDialog::Accepted:
            if(m_instance->printer()->status() == QKlipperPrinter::Ready)
            {
                m_instance->console()->printerPrintStart(fileItem->file());
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("Could Not Start print");
                msgBox.setInformativeText("Printer is not ready");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.exec();
            }
            break;
        default:
            break;
        }
    }
}

void FileBrowser::editFileButtonClickEvent()
{
    if(m_mode == Page)
    {
        if(m_filebrowserWidget->selectedItem())
        {
            m_editor->setFile(m_filebrowserWidget->selectedItem()->file());
            m_editor->show();
        }
    }
}

void FileBrowser::deleteFileButtonClickEvent()
{
    QMessageBox msgBox;
    msgBox.setText("Confirm Delete");
    msgBox.setInformativeText("Are you sure you want to this file?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch(ret)
    {
    case QMessageBox::Ok:
        m_instance->console()->serverFileDelete(m_filebrowserWidget->selectedItem()->file());
        break;
    default:
        break;
    }
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

        if(m_mode == Page && m_overlay)
            m_overlay->animateOut();

        if(m_currentDirectory.isEmpty())
            m_upDirectoryButton->setEnabled(false);
        else
            m_upDirectoryButton->setEnabled(true);

        m_currentDirectoryLabel->setText(thisDirectory);

        m_filebrowserWidget->clear();
        m_filebrowserWidget->setFiles(files);

        m_refreshButton->setEnabled(true);
        m_uploadFileButton->setEnabled(true);
        m_newFolderButton->setEnabled(true);
        m_downloadFolderButton->setEnabled(files.count() > 0);

        hideOverlay();
    }
}

void FileBrowser::onFileBrowserWidgetFileSelected(QAnimatedListItem *item)
{
    if(item)
    {
        if(m_mode == Page)
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

            refreshButtonClickEvent();
        }
        else if(m_mode == Page)
        {
            m_editFileButton->setEnabled(true);
            m_deleteFileButton->setEnabled(true);
        }
    }
    else if(m_mode == Page)
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
                QString theme = Settings::currentTheme();
                m_filePreview = new FilePreviewWindow(fileItem->file(), m_instance, this);
                m_filePreview->resize(700, 350);
                m_filePreview->setStyleSheet(theme);

                int ret = m_filePreview->exec();

                if(ret == QDialog::Accepted)
                {
                    if(m_instance->printer()->status() == QKlipperPrinter::Ready)
                        m_instance->console()->printerPrintStart(fileItem->file());
                    else
                    {
                        MessageDialog *message = new MessageDialog(this);
                        message->setText("Printer is not ready");
                        message->setWindowTitle("Could not print");

                        message->exec();

                        message->deleteLater();
                    }
                }

                m_filePreview->deleteLater();
            }

            else
            {
                m_editor = new FileEditor(m_instance, this);
                m_editor->setFile(fileItem->file());

                int ret = m_editor->exec();
                m_editor->deleteLater();

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

void FileBrowser::overlayAnimatedOutEvent()
{
    if(m_overlay)
    {
        m_overlay->lower();
        m_overlay->setHidden(true);

        m_overlay->deleteLater();
        m_overlay = nullptr;
    }
}

void FileBrowser::overlayAnimatedInEvent()
{

}

void FileBrowser::newFolderDialogAcceptEvent(QString value)
{
    QString path = m_rootDirectory + QString("/");

    if(!m_currentDirectory.isEmpty())
        path += m_currentDirectory + QString("/");

    path += value;

    if(m_newFolderDialog)
    {
        m_newFolderDialog->deleteLater();
        m_newFolderDialog = nullptr;
    }

    showOverlay(QString("Creating Folder"), QString("folder-icon"));

    m_instance->console()->serverDirectoryPost(path);
}

void FileBrowser::newFolderDialogRejectEvent()
{
    if(m_newFolderDialog)
    {
        m_newFolderDialog->deleteLater();
        m_newFolderDialog = nullptr;
    }
}

void FileBrowser::itemDeleteRequestedEvent(FileBrowserItem *item)
{
    QMessageBox msgBox;
    msgBox.setText("Confirm Delete");
    msgBox.setInformativeText("Are you sure you want to this file?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch(ret)
    {
    case QMessageBox::Ok:
        m_instance->console()->serverFileDelete(item->file());
        break;
    default:
        break;
    }
}

void FileBrowser::itemEditRequestedEvent(FileBrowserItem *item)
{
    m_editor->setFile(item->file());
    m_editor->show();
}

void FileBrowser::itemPrintRequestedEvent(FileBrowserItem *item)
{
    if(!m_filePreview && item->file()->fileType() == QKlipperFile::GCode)
    {
        QString theme = Settings::currentTheme();
        m_filePreview = new FilePreviewWindow(item->file(), m_instance, this);
        m_filePreview->setWindowFlag(Qt::Popup);
        m_filePreview->setStyleSheet(theme);

        int ret = m_filePreview->exec();

        switch(ret)
        {
            case QDialog::Accepted:
                if(m_instance->printer()->status() == QKlipperPrinter::Ready)
                {
                    m_instance->console()->printerPrintStart(item->file());
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setText("Could Not Start print");
                    msgBox.setInformativeText("Printer is not ready");
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.setDefaultButton(QMessageBox::Ok);
                    msgBox.exec();
                }
                break;
            default:
                break;
        }
    }
}
