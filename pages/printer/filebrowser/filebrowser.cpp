#include "filebrowser.h"

#include "../../../system/settings.h"

FileBrowser::FileBrowser(Printer *printer, QString root, QWidget *parent, Mode mode) :
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
    delete m_upDirectoryButton;
    delete m_currentDirectoryLabel;
    delete m_refreshButton;
    delete m_newFolderButton;
    delete m_uploadFileButton;
    delete m_downloadFolderButton;

    delete m_actionBarLayout;
    delete m_actionBar;

    delete m_thumbnailLabel;
    delete m_printFileButton;
    delete m_editFileButton;
    delete m_deleteFileButton;

    delete m_sideBarLayout;
    delete m_sideBar;

    delete m_layout;

    delete m_overlay;
    delete m_editor;
}

Printer *FileBrowser::printer() const
{
    return m_printer;
}

void FileBrowser::setPrinter(Printer *printer)
{
    m_startup = true;
    m_printer = printer;

    connect(m_printer, SIGNAL(directoryListing(QString,QString,QList<KlipperFile>,Printer*)), this, SLOT(on_printer_fileListing(QString,QString,QList<KlipperFile>,Printer*)));
    connect(m_printer, SIGNAL(startup(Printer*)), this, SLOT(on_printer_startup(Printer*)));
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

    if(m_mode == Page)
        m_filebrowserWidget = new FileBrowserWidget(this, FileBrowserWidget::Page);
    else
        m_filebrowserWidget = new FileBrowserWidget(this, FileBrowserWidget::Widget);

    m_filebrowserWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addWidget(m_filebrowserWidget, 1, 0, 1, 1);

    //Side bar
    if(m_mode == Page)
    {
        m_sideBar = new QWidget();
        m_sideBarLayout = new QGridLayout(m_sideBar);

        m_thumbnailLabel = new QLabel();
        m_thumbnailLabel->setFixedSize(200,200);
        m_sideBarLayout->addWidget(m_thumbnailLabel, 1, 0, 1, 1, Qt::AlignLeft);

        m_printFileButton = new QPushButton("Print File");
        m_printFileButton->setFixedHeight(35);
        m_printFileButton->setEnabled(false);
        m_printFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        m_sideBarLayout->addWidget(m_printFileButton, 2, 0, 1, 1);

        m_editFileButton = new QPushButton("Edit File");
        m_editFileButton->setFixedHeight(35);
        m_editFileButton->setEnabled(false);
        m_editFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        m_sideBarLayout->addWidget(m_editFileButton, 3, 0, 1, 1);

        QSpacerItem *spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
        m_sideBarLayout->addItem(spacer, 4, 0, 1, 1, Qt::AlignLeft);

        m_deleteFileButton = new QPushButton("Delete File");
        m_deleteFileButton->setFixedHeight(35);
        m_deleteFileButton->setEnabled(false);
        m_deleteFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        m_sideBarLayout->addWidget(m_deleteFileButton, 5, 0, 1, 1);
    }

    m_sideBar->setLayout(m_sideBarLayout);

    if(m_mode == Page)
        m_layout->addWidget(m_sideBar, 1, 1, 1, 1);
    else
    {
        m_upDirectoryButton->setFixedSize(32,32);
        m_newFolderButton->setFixedSize(32,32);
        m_uploadFileButton->setFixedSize(32,32);
        m_downloadFolderButton->setFixedSize(32,32);
        m_refreshButton->setFixedSize(32,32);

        m_actionBarLayout->setContentsMargins(4,4,4,4);
    }

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

        m_editor = new FileEditor(m_printer, this);
        m_editor->hide();

        m_overlay = new FileBrowserOverlay(this);
        m_overlay->setGeometry(0,0,width(),height());
        m_overlay->raise();
        m_overlay->setHidden(false);
    }
    else
    {
        setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
        m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    }
}

void FileBrowser::setupConnections()
{
    connect(m_uploadFileButton, SIGNAL(clicked(bool)), this, SLOT(on_uploadFileButton_clicked(bool)));
    connect(m_newFolderButton, SIGNAL(clicked(bool)), this, SLOT(on_newFolderButton_clicked(bool)));
    connect(m_downloadFolderButton, SIGNAL(clicked(bool)), this, SLOT(on_downloadFolderButton_clicked(bool)));
    connect(m_refreshButton, SIGNAL(clicked(bool)), this, SLOT(on_refreshButton_clicked(bool)));
    connect(m_upDirectoryButton, SIGNAL(clicked(bool)), this, SLOT(on_upDirectoryButton_clicked(bool)));
    connect(m_filebrowserWidget, SIGNAL(itemSelected(QAnimatedListItem*)), this, SLOT(on_fileBrowserWidget_fileSelected(QAnimatedListItem*)));

    if(m_mode == Page)
    {
        connect(m_editFileButton, SIGNAL(clicked(bool)), this, SLOT(on_editFileButton_clicked()));
        connect(m_printFileButton, SIGNAL(clicked(bool)), this, SLOT(on_printFileButton_clicked()));
        connect(m_deleteFileButton, SIGNAL(clicked(bool)), this, SLOT(on_deleteFileButton_clicked()));
        connect(m_overlay,SIGNAL(animatedOut()),this,SLOT(on_overlay_animatedOut()));
    }
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

void FileBrowser::on_uploadFileButton_clicked(bool clicked)
{
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
        m_overlay->setText(QString("Uploading Files"));
        m_overlay->setIcon(Settings::getThemeIcon(QString("file-upload-icon")));
        m_overlay->raise();
        m_overlay->setHidden(false);
        m_overlay->animateIn();
    foreach(QString fileLocation, files)
    {
        QFile file(fileLocation);
        QString fileName = file.fileName();
        fileName.remove(0, fileName.lastIndexOf(QDir::separator()) + 1);

        if(file.open(QFile::ReadOnly))
        {
            m_printer->console()->uploadFile(
                m_rootDirectory,
                m_currentDirectory,
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
    if(m_mode == Page)
    {
        m_overlay->setText(QString("Refreshing Directory"));
        m_overlay->setIcon(Settings::getThemeIcon(QString("refresh-icon")));
        m_overlay->raise();
        m_overlay->setHidden(false);
        m_overlay->animateIn();
    }

    m_refreshButton->setEnabled(false);
    m_uploadFileButton->setEnabled(false);
    m_newFolderButton->setEnabled(false);
    m_downloadFolderButton->setEnabled(false);
    m_upDirectoryButton->setEnabled(false);

    if(m_mode == Page)
    {
        m_printFileButton->setEnabled(false);
        m_editFileButton->setEnabled(false);
        m_deleteFileButton->setEnabled(false);
    }

    m_currentDirectoryLabel->setText(m_rootDirectory + QString("/") + m_currentDirectory);

    m_filebrowserWidget->clear();
    m_printer->getFiles(m_rootDirectory, m_currentDirectory);
}

void FileBrowser::on_upDirectoryButton_clicked(bool clicked)
{
    if(m_currentDirectory.contains(QString("/")))
        m_currentDirectory = m_currentDirectory.mid(0, m_currentDirectory.lastIndexOf(QString("/")));
    else
        m_currentDirectory.clear();

    on_refreshButton_clicked(clicked);
}

void FileBrowser::on_printFileButton_clicked()
{
    if(m_printer->status() == Printer::Ready)
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
    if(m_mode == Page)
    {
        if(m_filebrowserWidget->selectedItem())
        {
            m_editor->setFile(m_filebrowserWidget->selectedItem()->file());
            m_editor->show();
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
        m_printer->console()->deleteFile(m_filebrowserWidget->selectedItem()->file());
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
    if(root != m_rootDirectory)
        return;

    if(m_mode == Page)
        m_overlay->animateOut();

    m_currentDirectory = directory;

    if(m_currentDirectory.isEmpty())
        m_upDirectoryButton->setEnabled(false);
    else
        m_upDirectoryButton->setEnabled(true);

    m_currentDirectoryLabel->setText(root + QString("/") + directory);

    m_filebrowserWidget->clear();
    m_filebrowserWidget->setFiles(files);

    m_refreshButton->setEnabled(true);
    m_uploadFileButton->setEnabled(true);
    m_newFolderButton->setEnabled(true);
    m_downloadFolderButton->setEnabled(files.count() > 0);
}

void FileBrowser::on_printer_startup(Printer *printer)
{
    printer->getFiles(m_rootDirectory, m_currentDirectory);
}

void FileBrowser::on_fileBrowserWidget_fileSelected(QAnimatedListItem *item)
{
    if(item)
    {
        if(m_mode == Page)
        {
            if((m_printer->status() == Printer::Ready))
                m_printFileButton->setEnabled(true);
            else
                m_printFileButton->setEnabled(false);
        }

        if(((FileBrowserItem*)item)->isDirectory())
        {
            if(m_currentDirectory.isEmpty())
                m_currentDirectory = ((FileBrowserItem*)item)->file().name;
            else
                m_currentDirectory += QString("/") + ((FileBrowserItem*)item)->file().name;

            on_refreshButton_clicked(false);
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

void FileBrowser::on_overlay_animatedOut()
{
    if(m_overlay)
    {
        m_overlay->lower();
        m_overlay->setHidden(true);
    }
}
