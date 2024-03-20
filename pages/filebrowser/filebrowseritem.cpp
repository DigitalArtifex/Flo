#include "filebrowseritem.h"
#include "ui_filebrowseritem.h"

#include "../../settings.h"

FileBrowserItem::FileBrowserItem(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FileBrowserItem)
{
    this->setProperty("pressed", false);
    ui->setupUi(this);
    ui->modified->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "FileBrowserItemDate"));
    ui->name->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "FileBrowserItemTitle"));
    ui->size->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "FileBrowserItemSize"));
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "FileBrowserItem"));
    this->setMinimumHeight(50);
    this->_id = QUuid::createUuid().toString();
}

FileBrowserItem::~FileBrowserItem()
{
    delete ui;
}

void FileBrowserItem::setName(QString name)
{
    this->_name = name;
    ui->name->setText(name);
}

void FileBrowserItem::setFileSize(qint64 size)
{
    this->_fileSize = size;
    QString sizeText(" Bytes");
    double sizeDisplayed = size;

    if(sizeDisplayed >= 1024)
    {
        sizeDisplayed /= 1024;
        sizeText = QString(" Kilobytes");

        if(sizeDisplayed >= 1024)
        {
            sizeDisplayed /= 1024;
            sizeText = QString(" Megabytes");
        }
    }

    ui->size->setText(QString::number(sizeDisplayed) + sizeText);
}

void FileBrowserItem::setDateModified(QDateTime time)
{
    this->_modified = time;
    ui->modified->setText(time.toString());
}

bool FileBrowserItem::isDirectory()
{
    return this->directory;
}

void FileBrowserItem::setIcons()
{
    if(!directory)
        ui->iconLabel->setPixmap(Settings::getThemeIcon("file-icon").pixmap(ui->iconLabel->height()));
    else
        ui->iconLabel->setPixmap(Settings::getThemeIcon("folder-icon").pixmap(ui->iconLabel->height()));

    this->style()->polish(this);
}

void FileBrowserItem::showButtons(bool show)
{

}

void FileBrowserItem::setDirectoryFlag(bool directory)
{
    this->directory = directory;

    if(directory)
    {
        ui->gridLayout->removeWidget(ui->name);
        ui->gridLayout->removeWidget(ui->size);
        ui->gridLayout->removeWidget(ui->sizeLabel);
        ui->size->setHidden(true);
        ui->sizeLabel->setHidden(true);

        if(ui->name->text() == QString(".."))
        {
            ui->modified->setHidden(true);
            ui->modifiedLabel->setHidden(true);
        }

        ui->gridLayout->addWidget(ui->name, 0, 1, 3, 1);
    }

    this->setIcons();
}

QString FileBrowserItem::id()
{
    return this->_id;
}

QString FileBrowserItem::name()
{
    return this->_name;
}

qint64 FileBrowserItem::fileSize()
{
    return this->_fileSize;
}

KlipperFile FileBrowserItem::file()
{
    return this->_file;
}

void FileBrowserItem::setFile(KlipperFile file)
{
    this->_file = file;
}

void FileBrowserItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->clickTimer = new QTimer(this);
        this->clickTimer->setInterval(500);
        this->clickTimer->setSingleShot(true);
        connect(this->clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
        this->clickTimer->start();
        this->setProperty("pressed", true);
        pressed = true;
        this->style()->polish(this);
        qDebug() << "Pressed";
    }
}

void FileBrowserItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->setProperty("pressed", false);
        this->style()->polish(this);
        qDebug() << "Released";

        if(this->clickTimer != NULL)
        {
            clickTimer->stop();
            disconnect(this->clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
            delete clickTimer;
            clickTimer = NULL;
        }

        if(pressed && !longPress)
        {
            pressed = false;
            longPress = false;
            emit(clicked(this));
        }
        else if(longPress)
        {
            pressed = false;
            longPress = false;
            emit(longPressed(this));
        }
    }
}

void FileBrowserItem::repaint()
{
    QFrame::repaint();
    setIcons();
}

void FileBrowserItem::clickTimeout()
{
    if(this->pressed)
        this->longPress = true;

    qDebug() << "Long Pressed";
}

