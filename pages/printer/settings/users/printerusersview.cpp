#include "printerusersview.h"

#include "flo/settings.h"

PrinterUsersView::PrinterUsersView(QKlipperInstance *instance, QWidget *parent)
    : CardWidget{CardType::Widget, parent}
{
    setTitle("User Management");
    setIcon(Settings::getThemeIcon("users"));

    m_instnace = instance;

    setupUi();
    setIcons();
}

PrinterUsersView::~PrinterUsersView()
{
    // if(m_centralLayout)
    //     m_centralLayout->deleteLater();
    if(m_centralWidget)
        m_centralWidget->deleteLater();
}

void PrinterUsersView::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_centralLayout = new QHBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_addUserButton = new QToolButton(m_centralWidget);
    m_addUserButton->setFixedWidth(50);
    m_addUserButton->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    m_addUserButton->setIcon(Settings::getThemeIcon("add"));
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
        delete card;
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
    Q_UNUSED(checked)

    m_editor = new PrinterUserEditor(this);
    dialogRequested(m_editor);

    connect(m_editor, SIGNAL(finished(int)), this, SLOT(onUserEditorFinished(int)));
}

void PrinterUsersView::on_userDeleteRequest(QKlipperUser user)
{
    m_instnace->console()->accessDeleteUser(user.username());
}

void PrinterUsersView::onUserEditorFinished(int returnCode)
{
    if(returnCode == QDialog::Accepted)
    {
        QString username = m_editor->username();
        QString password = m_editor->password();

        m_instnace->console()->accessCreateUser(username, password);
    }

    delete m_editor;
}

void PrinterUsersView::setIcons()
{
    setIcon(Settings::getThemeIcon("users"));
    m_addUserButton->setIcon(Settings::getThemeIcon("add"));
}

void PrinterUsersView::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}
