#include "printerusersview.h"

#include "system/settings.h"

PrinterUsersView::PrinterUsersView(Printer *printer, QWidget *parent)
    : CardWidget{CardWidget::Widget, parent}
{
    setTitle("User Management");

    m_system = printer->system();

    setupUi();
}

PrinterUsersView::~PrinterUsersView()
{

}

void PrinterUsersView::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_centralLayout = new QHBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_addUserButton = new QToolButton(m_centralWidget);
    m_addUserButton->setFixedWidth(50);
    m_addUserButton->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    m_addUserButton->setIcon(Settings::getThemeIcon("add-icon"));
    m_centralLayout->addWidget(m_addUserButton);

    m_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralLayout->addSpacerItem(m_spacer);

    setCentralWidget(m_centralWidget);

    connect(m_system, SIGNAL(userListChanged()), this, SLOT(userListChangedEvent()));
    connect(m_addUserButton, SIGNAL(clicked(bool)), this, SLOT(addUserButtonClickedEvent(bool)));
}

void PrinterUsersView::userListChangedEvent()
{
    QList<System::User> users = m_system->userList();

    m_centralLayout->removeWidget(m_addUserButton);
    m_centralLayout->removeItem(m_spacer);

    foreach(System::User user, users)
    {
        if(!m_userCards.contains(user.username))
        {
            PrinterUserCard *userCard = new PrinterUserCard(user, m_centralWidget);
            m_centralLayout->addWidget(userCard);

            m_userCards[user.username] = userCard;
        }
    }

    m_centralLayout->addWidget(m_addUserButton);
    m_centralLayout->addSpacerItem(m_spacer);
}

void PrinterUsersView::addUserButtonClickedEvent(bool checked)
{
    PrinterUserEditor *editor = new PrinterUserEditor(this);

    int ret = editor->exec();

    if(ret == QDialog::Accepted)
    {
        QString username = editor->username();
        QString password = editor->password();

        m_system->createUser(username, password);
    }
}
