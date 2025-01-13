#include "printerusercard.h"

#include "system/settings.h"

PrinterUserCard::PrinterUserCard(QKlipperUser user, QWidget *parent)
    : CardWidget{CardType::SubWidget, parent}
{
    setIcon(Settings::getThemeIcon("user"));
    m_user = user;

    setupUi();
}

PrinterUserCard::~PrinterUserCard()
{
    //m_centralLayout->deleteLater();
    m_centralWidget->deleteLater();
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
    m_iconLabel->setPixmap(Settings::getThemeIcon("user-card").pixmap(100,100));
    m_centralLayout->addWidget(m_iconLabel);
    setTitle(m_user.username());

    QDateTime time = QDateTime::fromSecsSinceEpoch(m_user.createdOn());

    m_userCreatedLabel = new QLabel(m_centralWidget);
    m_userCreatedLabel->setText(QString("Created: %1").arg(time.toString("MM/dd/yy")));
    m_centralLayout->addWidget(m_userCreatedLabel);

    //setup footer
    m_editButton = new QToolButton(this);
    m_editButton->setIcon(Settings::getThemeIcon("edit"));
    m_editButton->setFixedSize(32,32);

    m_deleteButton = new QToolButton(this);
    m_deleteButton->setIcon(Settings::getThemeIcon("remove"));
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
    Q_UNUSED(checked)

}

void PrinterUserCard::removeButtonClickEvent(bool checked)
{
    Q_UNUSED(checked)

    emit userDeleteRequest(m_user);
}

QKlipperUser PrinterUserCard::user() const
{
    return m_user;
}

void PrinterUserCard::setStyleSheet(const QString &styleSheet)
{
    setIcon(Settings::getThemeIcon("user"));

    CardWidget::setStyleSheet(styleSheet);
}

void PrinterUserCard::setUser(const QKlipperUser &user)
{
    m_user = user;

    QDateTime time = QDateTime::fromSecsSinceEpoch(m_user.createdOn());
    m_userCreatedLabel->setText(QString("Created: %1").arg(time.toString("MM/dd/yy")));
    setTitle(m_user.username());
}
