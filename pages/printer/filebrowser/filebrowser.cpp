#include "filebrowser.h"

#include "../../../system/settings.h"

FileBrowser::FileBrowser(Printer *printer, QString root, QWidget *parent, Mode mode) :
    QWidget(parent)
{
    _rootDirectory = root;
    _mode = mode;

    setPrinter(printer);

    setupUi();
    setupConnections();

    setStyleSheet(Settings::currentTheme());
}

FileBrowser::~FileBrowser()
{
    delete _upDirectoryButton;
    delete _currentDirectoryLabel;
    delete _refreshButton;
    delete _newFolderButton;
    delete _uploadFileButton;
    delete _downloadFolderButton;

    delete _actionBarLayout;
    delete _actionBar;

    delete _thumbnailLabel;
    delete _printFileButton;
    delete _editFileButton;
    delete _deleteFileButton;

    delete _sideBarLayout;
    delete _sideBar;

    delete _layout;

    delete _overlay;
    delete _editor;
}

Printer *FileBrowser::printer() const
{
    return _printer;
}

void FileBrowser::setPrinter(Printer *printer)
{
    _startup = true;
    _printer = printer;

    connect(_printer, SIGNAL(directoryListing(QString,QString,QList<KlipperFile>,Printer*)), this, SLOT(on_printer_fileListing(QString,QString,QList<KlipperFile>,Printer*)));
    connect(_printer, SIGNAL(startup(Printer*)), this, SLOT(on_printer_startup(Printer*)));
}

void FileBrowser::setupUi()
{
    _layout = new QGridLayout();
    _layout->setContentsMargins(0,0,0,0);
    _layout->setSpacing(0);

    //Action bar
    _actionBar = new QWidget();
    _actionBarLayout = new QGridLayout(_actionBar);
    _actionBarLayout->setContentsMargins(9,9,9,9);

    _upDirectoryButton = new QToolButton(_actionBar);
    _upDirectoryButton->setEnabled(false);
    _upDirectoryButton->setFixedSize(35,35);
    _upDirectoryButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_upDirectoryButton, 0, 0, 1, 1);

    _currentDirectoryLabel = new QLabel(_actionBar);
    _currentDirectoryLabel->setText(_currentDirectory);
    _currentDirectoryLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    _actionBarLayout->addWidget(_currentDirectoryLabel, 0, 1, 1, 1);

    QSpacerItem *actionSpacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    _actionBarLayout->addItem(actionSpacer, 0, 2, 1, 1);

    _refreshButton = new QToolButton(_actionBar);
    _refreshButton->setFixedSize(35,35);
    _refreshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_refreshButton, 0, 3, 1, 1);

    _uploadFileButton = new QToolButton(_actionBar);
    _uploadFileButton->setFixedSize(35,35);
    _uploadFileButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_uploadFileButton, 0, 4, 1, 1);

    _newFolderButton = new QToolButton(_actionBar);
    _newFolderButton->setFixedSize(35,35);
    _newFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_newFolderButton, 0, 5, 1, 1);

    _downloadFolderButton = new QToolButton(_actionBar);
    _downloadFolderButton->setFixedSize(35,35);
    _downloadFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_downloadFolderButton, 0, 6, 1, 1);

    _actionBar->setLayout(_actionBarLayout);
    _layout->addWidget(_actionBar, 0, 0, 1, 2);

    if(_mode == Page)
        _filebrowserWidget = new FileBrowserWidget(this, FileBrowserWidget::Page);
    else
        _filebrowserWidget = new FileBrowserWidget(this, FileBrowserWidget::Widget);

    _filebrowserWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _layout->addWidget(_filebrowserWidget, 1, 0, 1, 1);

    //Side bar
    if(_mode == Page)
    {
        _sideBar = new QWidget();
        _sideBarLayout = new QGridLayout(_sideBar);

        _thumbnailLabel = new QLabel();
        _thumbnailLabel->setFixedSize(200,200);
        _sideBarLayout->addWidget(_thumbnailLabel, 1, 0, 1, 1, Qt::AlignLeft);

        _printFileButton = new QPushButton("Print File");
        _printFileButton->setFixedHeight(35);
        _printFileButton->setEnabled(false);
        _printFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        _sideBarLayout->addWidget(_printFileButton, 2, 0, 1, 1);

        _editFileButton = new QPushButton("Edit File");
        _editFileButton->setFixedHeight(35);
        _editFileButton->setEnabled(false);
        _editFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        _sideBarLayout->addWidget(_editFileButton, 3, 0, 1, 1);

        QSpacerItem *spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
        _sideBarLayout->addItem(spacer, 4, 0, 1, 1, Qt::AlignLeft);

        _deleteFileButton = new QPushButton("Delete File");
        _deleteFileButton->setFixedHeight(35);
        _deleteFileButton->setEnabled(false);
        _deleteFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        _sideBarLayout->addWidget(_deleteFileButton, 5, 0, 1, 1);
    }

    _sideBar->setLayout(_sideBarLayout);

    if(_mode == Page)
        _layout->addWidget(_sideBar, 1, 1, 1, 1);
    else
    {
        _upDirectoryButton->setFixedSize(32,32);
        _newFolderButton->setFixedSize(32,32);
        _uploadFileButton->setFixedSize(32,32);
        _downloadFolderButton->setFixedSize(32,32);
        _refreshButton->setFixedSize(32,32);

        _actionBarLayout->setContentsMargins(4,4,4,4);
    }

    setLayout(_layout);

    if(_sideBar)
        _sideBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageSideBar"));

    _upDirectoryButton->setIcon(Settings::getThemeIcon(QString("up-directory-icon")));
    _refreshButton->setIcon(Settings::getThemeIcon(QString("refresh-icon")));
    _uploadFileButton->setIcon(Settings::getThemeIcon(QString("file-upload-icon")));
    _newFolderButton->setIcon(Settings::getThemeIcon(QString("folder-create-icon")));
    _downloadFolderButton->setIcon(Settings::getThemeIcon(QString("folder-download-icon")));

    if(_mode == Page)
    {
        setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
        _actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));

        if(_rootDirectory != QString("gcodes"))
            _printFileButton->setHidden(true);
        else
            _printFileButton->setHidden(false);

        _editor = new FileEditor(_printer, this);
        _overlay = new FileBrowserOverlay(this);
        _overlay->setGeometry(0,0,width(),height());
        _overlay->raise();
        _overlay->setHidden(false);
    }
    else
    {
        setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
        _actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    }
}

void FileBrowser::setupConnections()
{
    connect(_uploadFileButton, SIGNAL(clicked(bool)), this, SLOT(on_uploadFileButton_clicked(bool)));
    connect(_newFolderButton, SIGNAL(clicked(bool)), this, SLOT(on_newFolderButton_clicked(bool)));
    connect(_downloadFolderButton, SIGNAL(clicked(bool)), this, SLOT(on_downloadFolderButton_clicked(bool)));
    connect(_refreshButton, SIGNAL(clicked(bool)), this, SLOT(on_refreshButton_clicked(bool)));
    connect(_upDirectoryButton, SIGNAL(clicked(bool)), this, SLOT(on_upDirectoryButton_clicked(bool)));
    connect(_filebrowserWidget, SIGNAL(itemSelected(QAnimatedListItem*)), this, SLOT(on_fileBrowserWidget_fileSelected(QAnimatedListItem*)));

    if(_mode == Page)
    {
        connect(_editFileButton, SIGNAL(clicked(bool)), this, SLOT(on_editFileButton_clicked()));
        connect(_printFileButton, SIGNAL(clicked(bool)), this, SLOT(on_printFileButton_clicked()));
        connect(_deleteFileButton, SIGNAL(clicked(bool)), this, SLOT(on_deleteFileButton_clicked()));
        connect(_overlay,SIGNAL(animatedOut()),this,SLOT(on_overlay_animatedOut()));
    }
}

void FileBrowser::setStyleSheet(const QString &styleSheet)
{
    QWidget::setStyleSheet(styleSheet);

    if(_filebrowserWidget)
        _filebrowserWidget->setStyleSheet(styleSheet);

    if(_overlay)
        _overlay->setStyleSheet(styleSheet);

    _upDirectoryButton->setIcon(Settings::getThemeIcon(QString("up-directory-icon")));
    _refreshButton->setIcon(Settings::getThemeIcon(QString("refresh-icon")));
    _uploadFileButton->setIcon(Settings::getThemeIcon(QString("file-upload-icon")));
    _newFolderButton->setIcon(Settings::getThemeIcon(QString("folder-create-icon")));
    _downloadFolderButton->setIcon(Settings::getThemeIcon(QString("folder-download-icon")));
}

void FileBrowser::resizeEvent(QResizeEvent *event)
{
    if(_overlay)
        _overlay->setGeometry(0,0,width(),height());
}

void FileBrowser::on_uploadFileButton_clicked(bool clicked)
{
    QString fileTypes = QString("GCode (*.g *.gcode)");

    if(_rootDirectory == "gcodes")
        fileTypes = QString("GCode (*.g *.gcode)");
    else if(_rootDirectory == "config")
        fileTypes = QString("Config (*.cfg *.conf)");

    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "Select one or more files to open",
        QDir::homePath(),
        fileTypes);
        _overlay->setText(QString("Uploading Files"));
        _overlay->setIcon(Settings::getThemeIcon(QString("file-upload-icon")));
        _overlay->raise();
        _overlay->setHidden(false);
        _overlay->animateIn();
    foreach(QString fileLocation, files)
    {
        QFile file(fileLocation);
        QString fileName = file.fileName();
        fileName.remove(0, fileName.lastIndexOf(QDir::separator()) + 1);

        if(file.open(QFile::ReadOnly))
        {
            _printer->console()->uploadFile(
                _rootDirectory,
                _currentDirectory,
                fileName,
                file.readAll()
            );

            file.close();
        }
    }

    if(!files.isEmpty())
        on_refreshButton_clicked(false);
}

void FileBrowser::on_newFolderButton_clicked(bool clicked)
{

}

void FileBrowser::on_downloadFolderButton_clicked(bool clicked)
{

}

void FileBrowser::on_refreshButton_clicked(bool clicked)
{
    if(_mode == Page)
    {
        _overlay->setText(QString("Refreshing Directory"));
        _overlay->setIcon(Settings::getThemeIcon(QString("refresh-icon")));
        _overlay->raise();
        _overlay->setHidden(false);
        _overlay->animateIn();
    }

    _refreshButton->setEnabled(false);
    _uploadFileButton->setEnabled(false);
    _newFolderButton->setEnabled(false);
    _downloadFolderButton->setEnabled(false);
    _upDirectoryButton->setEnabled(false);

    if(_mode == Page)
    {
        _printFileButton->setEnabled(false);
        _editFileButton->setEnabled(false);
        _deleteFileButton->setEnabled(false);
    }

    _currentDirectoryLabel->setText(_rootDirectory + QString("/") + _currentDirectory);

    _filebrowserWidget->clear();
    _printer->getFiles(_rootDirectory, _currentDirectory);
}

void FileBrowser::on_upDirectoryButton_clicked(bool clicked)
{
    if(_currentDirectory.contains(QString("/")))
        _currentDirectory = _currentDirectory.mid(0, _currentDirectory.lastIndexOf(QString("/")));
    else
        _currentDirectory.clear();

    on_refreshButton_clicked(clicked);
}

void FileBrowser::on_printFileButton_clicked()
{
    if(_printer->status() == Printer::Ready)
    {
        QMessageBox msgBox;
        msgBox.setText("Confirm Print");
        msgBox.setInformativeText("Are you sure you want to start this print?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
}

void FileBrowser::on_editFileButton_clicked()
{
    if(_mode == Page)
    {
        if(_filebrowserWidget->selectedItem())
        {
            _editor->setFile(_filebrowserWidget->selectedItem()->file());
            _editor->show();
        }
    }
}

void FileBrowser::on_deleteFileButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Confirm Delete");
    msgBox.setInformativeText("Are you sure you want to delete this file?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch(ret)
    {
    case QMessageBox::Ok:
        _printer->console()->deleteFile(_filebrowserWidget->selectedItem()->file());
        break;
    default:
        break;
    }
}

void FileBrowser::on_printer_update(Printer *printer)
{

}

void FileBrowser::on_printer_fileListing(QString root, QString directory, QList<KlipperFile> files, Printer *printer)
{
    if(root != _rootDirectory)
        return;

    if(_mode == Page)
        _overlay->animateOut();

    _currentDirectory = directory;

    if(_currentDirectory.isEmpty())
        _upDirectoryButton->setEnabled(false);
    else
        _upDirectoryButton->setEnabled(true);

    _currentDirectoryLabel->setText(root + QString("/") + directory);

    _filebrowserWidget->clear();
    _filebrowserWidget->setFiles(files);

    _refreshButton->setEnabled(true);
    _uploadFileButton->setEnabled(true);
    _newFolderButton->setEnabled(true);
    _downloadFolderButton->setEnabled(files.count() > 0);
}

void FileBrowser::on_printer_startup(Printer *printer)
{
    printer->getFiles(_rootDirectory, _currentDirectory);
}

void FileBrowser::on_fileBrowserWidget_fileSelected(QAnimatedListItem *item)
{
    if(item)
    {
        if(_mode == Page)
        {
            if((_printer->status() == Printer::Ready))
                _printFileButton->setEnabled(true);
            else
                _printFileButton->setEnabled(false);
        }

        if(((FileBrowserItem*)item)->isDirectory())
        {
            if(_currentDirectory.isEmpty())
                _currentDirectory = ((FileBrowserItem*)item)->file().name;
            else
                _currentDirectory += QString("/") + ((FileBrowserItem*)item)->file().name;

            on_refreshButton_clicked(false);
        }
        else if(_mode == Page)
        {
            _editFileButton->setEnabled(true);
            _deleteFileButton->setEnabled(true);
        }
    }
    else if(_mode == Page)
    {
        _editFileButton->setEnabled(false);
        _deleteFileButton->setEnabled(false);
    }
}

void FileBrowser::on_overlay_animatedOut()
{
    if(_overlay)
    {
        _overlay->lower();
        _overlay->setHidden(true);
    }
}
