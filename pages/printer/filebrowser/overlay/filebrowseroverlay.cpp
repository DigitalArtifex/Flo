#include "filebrowseroverlay.h"
#include "../../../../system/settings.h"

FileBrowserOverlay::FileBrowserOverlay(QWidget *parent) :
    QAnimatedWidget(parent)
{
    setupUi();
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));
    setOpacityIn(0.8);
    setOpacityOut(0);
    setDuration(100);

    setStyleSheet(Settings::currentTheme());
}

FileBrowserOverlay::~FileBrowserOverlay()
{
    if(m_label)
        delete m_label;

    if(m_layout)
        delete m_layout;
}

void FileBrowserOverlay::setupUi()
{
    m_label = new QLabel(this);
    m_label->setText(QString("Loading"));
    m_label->setAlignment(Qt::AlignCenter);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setText(QString(""));
    m_iconLabel->setAlignment(Qt::AlignCenter);

    QPixmap pixmap = Settings::getThemeIcon(QString("empty-icon")).pixmap(64,64);
    m_iconLabel->setPixmap(pixmap);

    m_topSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_bottomSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_layout = new QGridLayout(this);
    m_layout->addItem(m_topSpacer,0,0);
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_iconLabel);
    m_layout->addItem(m_bottomSpacer,3,0);

    setLayout(m_layout);
}

void FileBrowserOverlay::setText(const QString &text)
{
    m_label->setText(text);
}

void FileBrowserOverlay::setIcon(const QPixmap &pixmap)
{
    m_iconLabel->setPixmap(pixmap);
}

void FileBrowserOverlay::setIcon(const QIcon &icon)
{
    QPixmap pixmap = icon.pixmap(64,64);
    m_iconLabel->setPixmap(pixmap);
}
