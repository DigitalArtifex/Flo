#include "issuelistitem.h"

#include "../../../../../system/settings.h"

IssueListItem::IssueListItem(QString title, QString source, QString message, QWidget *parent)
{
    setupUi();

    setBaseSize(100,75);

    setFixedHeight(120);

    m_titleLabel->setText(title);
    m_sourceLabel->setText(source);

    QString messageText = message;

    if(message.contains(QString("\n")))
    {
        //Format the klipper message
        QStringList splitMessage = message.split(QString("\n"), Qt::SkipEmptyParts);

        messageText = splitMessage.first() + QString("\n\n");
        splitMessage.removeFirst();

        if(splitMessage.count() > 1)
            splitMessage.removeLast();

        messageText += splitMessage.join(QString(". "));
    }

    if(title == QString("Error configuring printer"))
    {
        QPixmap icon = Settings::getThemeIcon(QString("issue-config")).pixmap(32,32);
        m_iconLabel->setPixmap(icon);
        m_iconLabel->setAlignment(Qt::AlignCenter);
    }
    else
    {
        QPixmap icon = Settings::getThemeIcon(QString("issue-default")).pixmap(32,32);
        m_iconLabel->setPixmap(icon);
        m_iconLabel->setAlignment(Qt::AlignCenter);
    }

    m_messageLabel->setText(messageText);
    m_messageLabel->setWordWrap(true);

    if(parent)
        setStyleSheet(parent->styleSheet());
}

IssueListItem::~IssueListItem()
{
    m_iconLabel->deleteLater();
    m_iconContainer->deleteLater();
    m_titleLabel->deleteLater();
    m_sourceLabel->deleteLater();
    m_messageLabel->deleteLater();
}

void IssueListItem::setupUi()
{
    QGridLayout *layout = new QGridLayout();

    m_iconContainer = new QWidget(this);
    m_iconContainer->setLayout(new QVBoxLayout(m_iconContainer));
    m_iconContainer->setBaseSize(75,75);
    m_iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    layout->addWidget(m_iconContainer,0,0,4,1);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setBaseSize(50,50);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setText(QString("Icon"));
    m_iconContainer->layout()->addWidget(m_iconLabel);

    m_titleLabel = new QLabel(this);
    layout->addWidget(m_titleLabel,0,1,1,1);

    m_sourceLabel = new QLabel(this);
    layout->addWidget(m_sourceLabel,0,2,1,1);

    m_buttonSpacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(m_buttonSpacer,0,3,1,1);

    m_closeButton = new QToolButton(this);
    m_closeButton->setIcon(Settings::getThemeIcon(QString("close")));
    layout->addWidget(m_closeButton,0,4,1,1);

    connect(m_closeButton, SIGNAL(clicked(bool)), this, SLOT(on_closeButton_clicked()));

    m_separator = new QFrame(this);
    m_separator->setFrameShape(QFrame::HLine);
    m_separator->setFrameShadow(QFrame::Sunken);
    layout->addWidget(m_separator,1,1,1,4);

    m_messageLabel = new QLabel(this);
    layout->addWidget(m_messageLabel,2,1,1,4);

    m_spacer = new QSpacerItem(20,20,QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addItem(m_spacer, 3, 1, 1, 2);

    setLayout(layout);
}

void IssueListItem::on_closeButton_clicked()
{
    emit removeRequest(this);
}

