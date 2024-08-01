#include "printerupdateitem.h"

#include "system/settings.h"

PrinterUpdateItem::PrinterUpdateItem(QString name, System::UpdateState::PackageState state, QWidget *parent)
    : QAnimatedListItem{parent}
{
    m_title = name;
    m_packageState = state;

    setupUi();
}

void PrinterUpdateItem::updateButtonClickEvent()
{
    emit updateRequested(this);
}

void PrinterUpdateItem::setupUi()
{
    m_layout = new QGridLayout();

    m_iconContainer = new QWidget(this);
    m_iconContainer->setLayout(new QVBoxLayout(m_iconContainer));
    m_iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    m_iconContainer->layout()->setContentsMargins(0,0,0,0);
    m_layout->addWidget(m_iconContainer,0,0,2,1);

    m_iconLabel = new QLabel(this);
    m_iconContainer->layout()->addWidget(m_iconLabel);

    setFixedHeight(50);
    m_iconContainer->setFixedWidth(45);
    m_iconLabel->setFixedSize(32,32);

    QPixmap icon = Settings::getThemeIcon(QString("file-icon")).pixmap(32,32);

    if(m_title.toLower() == QString("crowsnest"))
        icon = Settings::getThemeIcon(QString("crowsnest-icon")).pixmap(32,32);

    if(m_title.toLower() == QString("klipper"))
        icon = Settings::getThemeIcon(QString("klipper-icon")).pixmap(32,32);

    if(m_title.contains("mainsail", Qt::CaseInsensitive))
        icon = Settings::getThemeIcon(QString("mainsail-icon")).pixmap(32,32);

    m_iconLabel->setPixmap(icon);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setText(m_title);

    m_versionLabel = new QLabel(this);
    m_versionLabel->setText(m_packageState.fullVersionString);

    //_spacer = new QSpacerItem(10,10, QSizePolicy::Ignored, QSizePolicy::Expanding);

    m_branchLabel = new QLabel(this);
    m_branchLabel->setText(m_packageState.branch);
    m_branchLabel->setFixedWidth(64);
    m_branchLabel->setAlignment(Qt::AlignRight);

    m_updateButton = new QToolButton(this);
    m_updateButton->setIcon(Settings::getThemeIcon(QString("update-icon")));
    m_updateButton->setIconSize(QSize(16,16));
    m_updateButton->setFixedSize(35,35);

    connect(m_updateButton, SIGNAL(clicked(bool)), this, SLOT(updateActionTriggered(bool)));

    m_layout->addWidget(m_titleLabel,0,1,1,1);
    m_layout->addWidget(m_versionLabel,0,2,1,1);
    m_layout->addWidget(m_branchLabel,0,3,1,1);
    m_layout->addWidget(m_updateButton,0,4,1,1);

    m_branchLabel->setProperty("class", "FileWidgetItemDetails");
    m_versionLabel->setProperty("class", "FileWidgetItemDetails");
    m_titleLabel->setProperty("class", "FileWidgetItemTitle");

    QIcon actionIcon = Settings::getThemeIcon("print-icon");
    m_updateAction = new QAction(actionIcon, "Print", this);
    connect(m_updateAction, SIGNAL(triggered(bool)), this, SLOT(updateActionTriggered(bool)));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(m_updateAction);

    setContextMenu(contextMenu);

    setLayout(m_layout);
}

QString PrinterUpdateItem::title() const
{
    return m_title;
}

void PrinterUpdateItem::setTitle(const QString &newTitle)
{
    m_title = newTitle;
}

System::UpdateState::PackageState PrinterUpdateItem::packageState() const
{
    return m_packageState;
}

void PrinterUpdateItem::setPackageState(const System::UpdateState::PackageState &newPackageState)
{
    m_packageState = newPackageState;
}

void PrinterUpdateItem::updateActionTriggered(bool checked)
{
    Q_UNUSED(checked)

    emit updateRequested(this);
}
