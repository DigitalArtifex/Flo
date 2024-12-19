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
}

void FileBrowserOverlay::setupUi()
{
    m_label = new QLabel(this);
    m_label->setText(QString("Loading"));
    m_label->setAlignment(Qt::AlignCenter);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setAlignment(Qt::AlignCenter);

    QPixmap pixmap = Settings::getThemeIcon(QString("empty")).pixmap(64,64);
    m_iconLabel->setPixmap(pixmap);

    m_topSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_bottomSpacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_middleSpacer = new QSpacerItem(20,20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    QGridLayout *layout = qobject_cast<QGridLayout*>(this->layout());

    layout->addItem(m_topSpacer,0,0);
    layout->addWidget(m_iconLabel,1,0);
    layout->addItem(m_middleSpacer,2,0);
    layout->addWidget(m_label,3,0);
    layout->addItem(m_bottomSpacer,4,0);
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
