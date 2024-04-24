#include "issuelistitem.h"

#include "../../../../../system/settings.h"

IssueListItem::IssueListItem(QString title, QString source, QString message, QWidget *parent)
{
    setupUi();

    setBaseSize(100,75);

    setFixedHeight(120);

    _titleLabel->setText(title);
    _sourceLabel->setText(source);

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
        QPixmap icon = Settings::getThemeIcon(QString("issue-config-icon")).pixmap(32,32);
        _iconLabel->setPixmap(icon);
        _iconLabel->setAlignment(Qt::AlignCenter);
    }
    else
    {
        QPixmap icon = Settings::getThemeIcon(QString("issue-default-icon")).pixmap(32,32);
        _iconLabel->setPixmap(icon);
        _iconLabel->setAlignment(Qt::AlignCenter);
    }

    _messageLabel->setText(messageText);
    _messageLabel->setWordWrap(true);

    if(parent)
        setStyleSheet(parent->styleSheet());
}

IssueListItem::~IssueListItem()
{
    delete _iconLabel;
    delete _iconContainer;
    delete _titleLabel;
    delete _sourceLabel;
    delete _messageLabel;
}

void IssueListItem::setupUi()
{
    QGridLayout *layout = new QGridLayout();

    _iconContainer = new QWidget(this);
    _iconContainer->setLayout(new QVBoxLayout(_iconContainer));
    _iconContainer->setBaseSize(75,75);
    _iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    layout->addWidget(_iconContainer,0,0,4,1);

    _iconLabel = new QLabel(this);
    _iconLabel->setBaseSize(50,50);
    _iconLabel->setAlignment(Qt::AlignCenter);
    _iconLabel->setText(QString("Icon"));
    _iconContainer->layout()->addWidget(_iconLabel);

    _titleLabel = new QLabel(this);
    layout->addWidget(_titleLabel,0,1,1,1);

    _sourceLabel = new QLabel(this);
    layout->addWidget(_sourceLabel,0,2,1,1);

    _buttonSpacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(_buttonSpacer,0,3,1,1);

    _closeButton = new QToolButton(this);
    _closeButton->setIcon(Settings::getThemeIcon(QString("close-icon")));
    layout->addWidget(_closeButton,0,4,1,1);

    connect(_closeButton, SIGNAL(clicked(bool)), this, SLOT(on_closeButton_clicked()));

    _separator = new QFrame(this);
    _separator->setFrameShape(QFrame::HLine);
    _separator->setFrameShadow(QFrame::Sunken);
    layout->addWidget(_separator,1,1,1,4);

    _messageLabel = new QLabel(this);
    layout->addWidget(_messageLabel,2,1,1,4);

    _spacer = new QSpacerItem(20,20,QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addItem(_spacer, 3, 1, 1, 2);

    setLayout(layout);
}

void IssueListItem::on_closeButton_clicked()
{
    emit removeRequest(this);
}

