#include "issuelistitem.h"

IssueListItem::IssueListItem(QString title, QString source, QString message, QWidget *parent)
{
    setupUi();

    _titleLabel->setText(title);
    _sourceLabel->setText(source);
    _messageLabel->setText(message);

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
    _iconContainer->setBaseSize(100,100);
    _iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    layout->addWidget(_iconContainer,0,0,3,1);

    _iconLabel = new QLabel(this);
    _iconLabel->setFixedSize(100,100);
    _iconLabel->setAlignment(Qt::AlignCenter);
    _iconLabel->setText(QString("Icon"));
    _iconContainer->layout()->addWidget(_iconLabel);

    _titleLabel = new QLabel(this);
    _titleLabel->setText(QString("Name"));
    layout->addWidget(_titleLabel,0,1,1,1);

    _sourceLabel = new QLabel(this);
    _sourceLabel->setText(QString("Printer"));
    layout->addWidget(_sourceLabel,1,1,1,1);

    _messageLabel = new QLabel(this);
    _messageLabel->setText(QString("Time Remaining"));
    layout->addWidget(_messageLabel,2,1,1,1);

    setLayout(layout);
}

