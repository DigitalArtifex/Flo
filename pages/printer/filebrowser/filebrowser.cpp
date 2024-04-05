#include "filebrowser.h"

FileBrowser::FileBrowser(Printer *printer, QString root, QWidget *parent) :
    QWidget(parent)
{
    _printer = printer;
    _fileRoot = root;
    _currentDirectory = root;

    setupUi();
}

QString FileBrowser::fileRoot() const
{
    return _fileRoot;
}

void FileBrowser::setFileRoot(const QString &fileRoot)
{
    _fileRoot = fileRoot;
}

Printer *FileBrowser::printer() const
{
    return _printer;
}

void FileBrowser::setPrinter(Printer *printer)
{
    _printer = printer;
}

QString FileBrowser::currentDirectory() const
{
    return _currentDirectory;
}

void FileBrowser::setCurrentDirectory(const QString &currentDirectory)
{
    _currentDirectory = currentDirectory;
}

QList<KlipperFile> FileBrowser::files() const
{
    return _files;
}

void FileBrowser::setFiles(const QList<KlipperFile> &files)
{
    _files = files;
    _filebrowserWidget->setFiles(files);
}

void FileBrowser::setupUi()
{
    _layout = new QGridLayout(this);

    //Action bar
    _actionBar = new QWidget();
    _actionBarLayout = new QGridLayout(_actionBar);

    _currentDirectoryLabel = new QLabel(_actionBar);
    _currentDirectoryLabel->setText(_currentDirectory);
    _currentDirectoryLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    _actionBarLayout->addWidget(_currentDirectoryLabel, 0, 0, 1, 1, Qt::AlignLeft);

    _refreshButton = new QToolButton(_actionBar);
    _refreshButton->setFixedSize(32,32);
    _refreshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_refreshButton, 0, 1, 1, 1, Qt::AlignCenter);

    _uploadFileButton = new QToolButton(_actionBar);
    _uploadFileButton->setFixedSize(32,32);
    _uploadFileButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_uploadFileButton, 0, 2, 1, 1, Qt::AlignCenter);

    _newFolderButton = new QToolButton(_actionBar);
    _newFolderButton->setFixedSize(32,32);
    _newFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_newFolderButton, 0, 1, 3, 1, Qt::AlignCenter);

    _downloadFolderButton = new QToolButton(_actionBar);
    _downloadFolderButton->setFixedSize(32,32);
    _downloadFolderButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _actionBarLayout->addWidget(_downloadFolderButton, 0, 2, 4, 1, Qt::AlignCenter);

    _actionBar->setLayout(_actionBarLayout);
    _layout->addWidget(_actionBar, 0, 0, 1, 1, Qt::AlignLeft);

    _filebrowserWidget = new FileBrowserWidget(this);
    _filebrowserWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _layout->addWidget(_filebrowserWidget, 1, 0, 1, 1, Qt::AlignLeft);

    setLayout(_layout);
}

void FileBrowser::setupConnections()
{
    connect(_uploadFileButton, SIGNAL(clicked(bool)), this, SLOT(on_uploadFileButton_clicked(bool)));
    connect(_newFolderButton, SIGNAL(clicked(bool)), this, SLOT(on_newFolderButton_clicked(bool)));
    connect(_downloadFolderButton, SIGNAL(clicked(bool)), this, SLOT(on_downloadFolderButton_clicked(bool)));
    connect(_refreshButton, SIGNAL(clicked(bool)), this, SLOT(on_refreshButton_clicked(bool)));
}

void FileBrowser::setStyleSheet(QString styleSheet)
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    _actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
}

void FileBrowser::on_uploadFileButton_clicked(bool clicked)
{

}

void FileBrowser::on_newFolderButton_clicked(bool clicked)
{

}

void FileBrowser::on_downloadFolderButton_clicked(bool clicked)
{

}

void FileBrowser::on_refreshButton_clicked(bool clicked)
{

}
