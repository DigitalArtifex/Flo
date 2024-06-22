#include "filebrowseritem.h"
#include "../../../system/settings.h"

FileBrowserItem::FileBrowserItem(KlipperFile file, QWidget *parent, DisplayMode mode) :
    QAnimatedListItem(parent)
{
    m_displayMode = mode;
    setFile(file);
    setupUi();
}

FileBrowserItem::~FileBrowserItem()
{
    if(m_iconLabel)
        delete m_iconLabel;

    if(m_iconContainer)
        delete m_iconContainer;

    if(m_titleLabel)
        delete m_titleLabel;

    if(m_sizeLabel)
        delete m_sizeLabel;

    if(m_modifiedLabel)
        delete m_modifiedLabel;

    if(m_spacer)
        delete m_spacer;

    if(m_layout)
        delete m_layout;
}

KlipperFile FileBrowserItem::file() const
{
    return m_file;
}

void FileBrowserItem::setFile(const KlipperFile &file)
{
    m_file = file;

    if(m_file.type == KlipperFile::Directory)
        m_directory = true;
}

bool FileBrowserItem::isDirectory() const
{
    return (m_file.type == KlipperFile::Directory);
}

void FileBrowserItem::setupUi()
{
    m_layout = new QGridLayout();

    m_iconContainer = new QWidget(this);
    m_iconContainer->setLayout(new QVBoxLayout(m_iconContainer));
    m_iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    m_iconContainer->layout()->setContentsMargins(0,0,0,0);
    m_layout->addWidget(m_iconContainer,0,0,2,1);

    m_iconLabel = new QLabel(this);
    m_iconContainer->layout()->addWidget(m_iconLabel);

    if(m_displayMode == Page)
    {
        setFixedHeight(75);
        m_iconContainer->setFixedWidth(50);
        m_iconLabel->setFixedSize(30,30);
    }

    else
    {
        setFixedHeight(50);
        m_iconContainer->setFixedWidth(45);
        m_iconLabel->setFixedSize(30,30);
    }

    if(m_directory)
    {
        QPixmap icon = Settings::getThemeIcon(QString("folder-icon")).pixmap(30,30);
        m_iconLabel->setPixmap(icon);

        m_titleLabel = new QLabel(this);
        m_titleLabel->setText(m_file.name);
        m_layout->addWidget(m_titleLabel,0,1,1,1);
    }
    else
    {
        QPixmap icon = Settings::getThemeIcon(QString("file-icon")).pixmap(30,30);
        m_iconLabel->setPixmap(icon);

        m_titleLabel = new QLabel(this);
        m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_titleLabel->setWordWrap(true);
        m_titleLabel->setText(m_file.name);

        QString sizeFormat = " Bytes";
        qreal size = m_file.fileSize;

        if(size > 1024)
        {
            size /= 1024;
            sizeFormat = " KB";

            if(size > 1024)
            {
                size /= 1024;
                sizeFormat = " MB";
            }
        }

        m_sizeLabel = new QLabel(this);
        m_sizeLabel->setText(QString::number(size) + sizeFormat);

        //_spacer = new QSpacerItem(10,10, QSizePolicy::Ignored, QSizePolicy::Expanding);

        m_modifiedLabel = new QLabel(this);

        if(m_displayMode == Page)
        {
            m_layout->addWidget(m_titleLabel,0,1,1,3);
            m_layout->addWidget(m_sizeLabel,1,1,1,1);
            //_layout->addItem(m_spacer, 1, 2, 1, 1);
            m_layout->addWidget(m_modifiedLabel,1,2,1,1);
            m_modifiedLabel->setText(QDateTime::fromSecsSinceEpoch(m_file.dateModified).toString());
            m_sizeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }

        else
        {
            m_layout->addWidget(m_titleLabel,0,1,1,1);
            m_layout->addWidget(m_sizeLabel,0,2,1,1);
            //_layout->addItem(m_spacer, 0, 3, 1, 1);
            m_layout->addWidget(m_modifiedLabel,0,3,1,1);
            m_modifiedLabel->setText(QDateTime::fromSecsSinceEpoch(m_file.dateModified).toString("MM/dd/yy"));
            m_sizeLabel->setFixedWidth(120);
        }
    }

    setLayout(m_layout);
}
