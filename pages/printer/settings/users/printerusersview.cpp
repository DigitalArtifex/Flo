#include "printerusersview.h"

#include "system/settings.h"

PrinterUsersView::PrinterUsersView(QKlipperInstance *instance, QWidget *parent)
    : CardWidget{CardWidget::Widget, parent}
{
    setTitle("User Management");
    setIcon(Settings::getThemeIcon("users-icon"));

    m_instnace = instance;

    setupUi();
}

PrinterUsersView::~PrinterUsersView()
{
    // if(m_centralLayout)
    //     m_centralLayout->deleteLater();
    if(m_centralWidget)
        m_centralWidget->deleteLater();
}

void PrinterUsersView::setStyleSheet(const QString &styleSheet)
{
    setIcon(Settings::getThemeIcon("users-icon"));

    CardWidget::setStyleSheet(styleSheet);
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

    connect(m_instnace->server(), SIGNAL(userListChanged()), this, SLOT(userListChangedEvent()));
    connect(m_addUserButton, SIGNAL(clicked(bool)), this, SLOT(addUserButtonClickedEvent(bool)));
}

void PrinterUsersView::userListChangedEvent()
{
    QList<QKlipperUser> users = m_instnace->server()->userList();

    m_centralLayout->removeWidget(m_addUserButton);
    m_centralLayout->removeItem(m_spacer);

    foreach(PrinterUserCard *card, m_userCards)
    {
        m_centralLayout->removeWidget(card);
        m_userCards.remove(card->user().username());
        card->deleteLater();
    }

    foreach(QKlipperUser user, users)
    {
        PrinterUserCard *userCard = new PrinterUserCard(user, m_centralWidget);
        m_centralLayout->addWidget(userCard);

        m_userCards[user.username()] = userCard;

        connect(userCard, SIGNAL(userDeleteRequest(QKlipperUser)), this, SLOT(on_userDeleteRequest(QKlipperUser)));
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

        m_instnace->console()->accessCreateUser(username, password);
    }

    editor->deleteLater();
}

void PrinterUsersView::on_userDeleteRequest(QKlipperUser user)
{
    m_instnace->console()->accessDeleteUser(user.username());
}
