#include "filebrowserpage.h"
#include "ui_filebrowserpage.h"

#include "../../settings.h"

FileBrowserPage::FileBrowserPage(QString rootDirectory, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FileBrowserPage)
{
    ui->setupUi(this);
    this->fileWidget = new FileBrowserWidget();
    this->fileWidget->setRootDirectory(rootDirectory);
    this->fileWidget->setCurrentDirectory(rootDirectory);
    ui->TitleBar->setHidden(true);
    setupUiClasses();
    QGridLayout *pageLayout = (QGridLayout*)ui->pageContents->layout();
    pageLayout->addWidget(fileWidget,1,0,1,4);

    spacer = new QSpacerItem(0,40,QSizePolicy::Maximum,QSizePolicy::Expanding);

    ui->fileUploadButton->setIcon(Settings::getThemeIcon("file-upload-icon"));
    ui->folderCreateButton->setIcon(QIcon(Settings::getThemeIcon("folder-create-icon")));

    connect(fileWidget, SIGNAL(itemClicked(FileBrowserItem*)), this, SLOT(on_itemClicked(FileBrowserItem*)));
    connect(fileWidget, SIGNAL(itemLongPressed(FileBrowserItem*)), this, SLOT(on_itemLongPressed(FileBrowserItem*)));
}

FileBrowserPage::~FileBrowserPage()
{
    delete ui;
}

void FileBrowserPage::setFileList(QList<KlipperFile> files)
{
    ui->currentDirectory->setText(this->fileWidget->currentDirectory());
    this->fileWidget->setItemList(files);
}

void FileBrowserPage::setIcons()
{
    ui->searchButton->setIcon(QIcon(Settings::getThemeIcon("search-icon")));
    ui->fileUploadButton->setIcon(QIcon(Settings::getThemeIcon("file-upload-icon")));
    ui->folderCreateButton->setIcon(QIcon(Settings::getThemeIcon("folder-create-icon")));
    ui->fileRefreshButton_2->setIcon(QIcon(Settings::getThemeIcon("refresh-icon")));

    foreach(FileBrowserItem *item, this->itemList)
    {
        item->setIcons();
    }

    this->style()->polish(this);
}

void FileBrowserPage::setCurrentDirectory(QString directory)
{
    fileWidget->setCurrentDirectory(directory);
    fileWidget->clear();
    this->itemList.clear();
}

void FileBrowserPage::setupUiClasses()
{
    ui->filePageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle"));
    ui->actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));
    this->fileWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "FileBrowser"));
    ui->TitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitleBar"));
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
}

void FileBrowserPage::on_fileRefreshButton_clicked()
{
    this->fileWidget->clear();
    this->itemList.clear();
    emit(refreshRequested(_currentDirectory));
}

void FileBrowserPage::on_fileRefreshButton_2_clicked()
{
    this->fileWidget->clear();
    this->itemList.clear();
    emit(refreshRequested(_currentDirectory));
}

void FileBrowserPage::on_itemClicked(FileBrowserItem *item)
{
    if(item->isDirectory())
    {
        //Up directory
        if(item->name() == QString(".."))
        {
            QString directory = _currentDirectory.remove(
                _currentDirectory.lastIndexOf(QDir::separator()),
                (_currentDirectory.length() - _currentDirectory.lastIndexOf(QDir::separator())));

            _currentDirectory = directory;
            this->fileWidget->setCurrentDirectory(directory);
            on_fileRefreshButton_2_clicked();
        }
        else
        {
            QString directory = _currentDirectory + QDir::separator() + item->name();
            _currentDirectory = directory;
            this->fileWidget->setCurrentDirectory(directory);
            on_fileRefreshButton_2_clicked();
        }
    }
    else
    {
        this->setEnabled(true);
        QString styleKey = Settings::get("system.theme").toString();
        QString style = Settings::getTheme(styleKey);

        KlipperFile file = item->file();

        popup = new Popup("File Data");
        popup->setFileMode(file);
        connect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
        connect(this->popup, SIGNAL(deleteFile(QVariant)), this, SLOT(on_popupFileDelete(QVariant)));
        connect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupFilePrint(QVariant)));
        popup->setStyleSheet(style);
        popup->showPopup();
    }
}

void FileBrowserPage::on_itemLongPressed(FileBrowserItem *item)
{
    QString styleKey = Settings::get("system.theme").toString();
    QString style = Settings::getTheme(styleKey);

    KlipperFile file = item->file();

    if(file.type != KlipperFile::Directory)
    {
        popup = new Popup("File Data");
        popup->setFileMode(file);
        connect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
        connect(this->popup, SIGNAL(deleteFile(QVariant)), this, SLOT(on_popupFileDelete(QVariant)));
        connect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupFilePrint(QVariant)));
        popup->setStyleSheet(style);
        popup->showPopup();
    }
    else
    {
        popup = new Popup("File Data");
        popup->setFileMode(file);
        connect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
        connect(this->popup, SIGNAL(deleteFile(QVariant)), this, SLOT(on_popupDeleteFolder(QVariant)));
        connect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
        popup->setStyleSheet(style);
        popup->showPopup();
    }
}


void FileBrowserPage::on_folderCreateButton_clicked()
{
    this->setEnabled(false);


    QString styleKey = Settings::get("system.theme").toString();
    QString style = Settings::getTheme(styleKey);

    popup = new Popup("New Folder");
    popup->setInputMode();
    connect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupNewFolder(QVariant)));
    connect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    popup->setStyleSheet(style);
    popup->showPopup();
}

void FileBrowserPage::on_popupCancelled(QVariant data)
{
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    disconnect(this->popup, SIGNAL(deleteFile(QString)), this, SLOT(on_popupFileDelete(QString)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupFilePrint(QVariant)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupNewFolder(QVariant)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupAccepted(QVariant)));
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    delete this->popup;

    this->setEnabled(true);
}

void FileBrowserPage::on_popupAccepted(QVariant data)
{
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    disconnect(this->popup, SIGNAL(deleteFile(QString)), this, SLOT(on_popupFileDelete(QString)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupFilePrint(QVariant)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupNewFolder(QVariant)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupAccepted(QVariant)));
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    delete this->popup;

    this->setEnabled(true);
}

void FileBrowserPage::on_popupFileDelete(QVariant file)
{
    KlipperFile dataFile = file.value<KlipperFile>();
    dataFile.fileLocation = this->fileWidget->currentDirectory() + QDir::separator() + dataFile.fileLocation;
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    disconnect(this->popup, SIGNAL(deleteFile(QString)), this, SLOT(on_popupFileDelete(QString)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupFilePrint(QVariant)));
    delete this->popup;

    this->setEnabled(true);
    emit(deleteRequested(dataFile));
}

void FileBrowserPage::on_popupFilePrint(QVariant file)
{
    KlipperFile dataFile = file.value<KlipperFile>();
    dataFile.fileLocation = this->fileWidget->currentDirectory() + QDir::separator() + dataFile.fileLocation;
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    disconnect(this->popup, SIGNAL(deleteFile(QString)), this, SLOT(on_popupFileDelete(QString)));
    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupFilePrint(QVariant)));
    delete this->popup;

    this->setEnabled(true);
    emit(printRequested(dataFile));
}

void FileBrowserPage::on_popupNewFolder(QVariant folder)
{
    KlipperFile dataFile = folder.value<KlipperFile>();
    dataFile.fileLocation = this->fileWidget->currentDirectory() + QDir::separator() + folder.toString();

    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupNewFolder(QVariant)));
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    delete this->popup;

    emit(createDirectory(dataFile));

    this->setEnabled(true);
}

void FileBrowserPage::on_popupDeleteFolder(QVariant folder)
{
    KlipperFile dataFile = folder.value<KlipperFile>();
    dataFile.fileLocation = this->fileWidget->currentDirectory() + QDir::separator() + dataFile.fileLocation;

    disconnect(this->popup, SIGNAL(accepted(QVariant)), this, SLOT(on_popupNewFolder(QVariant)));
    disconnect(this->popup, SIGNAL(canceled(QVariant)), this, SLOT(on_popupCancelled(QVariant)));
    delete this->popup;

    emit(deleteDirectory(dataFile));

    this->setEnabled(true);
}


void FileBrowserPage::on_fileUploadButton_clicked()
{
    QString gcodeLocation = Settings::get("system.klipper.gcode_location").toString();
    QFileDialog dialog(this, tr("Upload GCode"), QDir::homePath(), tr("GCode Files (*.gcode *.g)"));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList uploadFiles;
    QString currentLocation = this->fileWidget->currentDirectory();
    currentLocation.remove(QRegularExpression("^gcodes(\\/|)"));

    if (dialog.exec())
    {
        uploadFiles = dialog.selectedFiles();

        foreach(QString uploadFile,uploadFiles)
        {
            QFile file(uploadFile);

            QString fileName = file.fileName();
            fileName.remove(0,fileName.lastIndexOf(QString("/")) + 1);

            QString uploadLocation;

            if(!currentLocation.isEmpty())
                uploadLocation = gcodeLocation + QDir::separator() + currentLocation + QDir::separator()  + fileName;
            else
                uploadLocation = gcodeLocation + QDir::separator() + fileName;

            if(!file.copy(uploadLocation))
            {
                qDebug() << uploadLocation;
            }

        }
        on_fileRefreshButton_clicked();
    }
}

