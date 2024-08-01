#include "printerusercard.h"

#include "system/settings.h"

PrinterUserCard::PrinterUserCard(System::User user, QWidget *parent)
    : CardWidget{CardWidget::SubWidget, parent}
{
    m_user = user;

    setupUi();
}

PrinterUserCard::~PrinterUserCard()
{
    delete m_userNameLabel;
    delete m_iconLabel;
    delete m_userSourceLabel;
    delete m_editButton;
    delete m_deleteButton;
    delete m_centralLayout;
    delete m_centralWidget;
}

void PrinterUserCard::setupUi()
{
    setFixedWidth(200);
    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_iconLabel = new QLabel(m_centralWidget);
    m_iconLabel->setFixedSize(100,100);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setPixmap(Settings::getThemeIcon("user-icon").pixmap(100,100));
    m_centralLayout->addWidget(m_iconLabel);

/*    m_userNameLabel = new QLabel(m_centralWidget);
    m_userNameLabel->setText(QString("Username: %1").arg(m_user.username));
    m_centralLayout->addWidget(m_userNameLabel);

    m_userSourceLabel = new QLabel(m_centralWidget);
    m_userSourceLabel->setText(QString("Source: %1").arg(m_user.source));
    m_centralLayout->addWidget(m_userSourceLabel);
*/
    setTitle(m_user.username);

    QDateTime time = QDateTime::fromSecsSinceEpoch(m_user.createdOn);

    m_userCreatedLabel = new QLabel(m_centralWidget);
    m_userCreatedLabel->setText(QString("Created: %1").arg(time.toString("MM/dd/yy")));
    m_centralLayout->addWidget(m_userCreatedLabel);

    //setup footer
    m_editButton = new QToolButton(this);
    m_editButton->setIcon(Settings::getThemeIcon("edit-icon"));
    m_editButton->setFixedSize(32,32);

    m_deleteButton = new QToolButton(this);
    m_deleteButton->setIcon(Settings::getThemeIcon("remove-icon"));
    m_deleteButton->setFixedSize(32,32);

    connect(m_editButton, SIGNAL(clicked(bool)), this, SLOT(editButtonClickEvent(bool)));
    connect(m_deleteButton, SIGNAL(clicked(bool)), this, SLOT(removeButtonClickEvent(bool)));

    addFooterItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    addFooterWidget(m_editButton);
    addFooterWidget(m_deleteButton);
    addFooterItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    setCentralWidget(m_centralWidget);
}

void PrinterUserCard::editButtonClickEvent(bool checked)
{

}

void PrinterUserCard::removeButtonClickEvent(bool checked)
{

}
