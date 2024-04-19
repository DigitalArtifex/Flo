#include "printerterminalitem.h"

PrinterTerminalItem::PrinterTerminalItem(QWidget *parent)
    : QAnimatedListItem(parent)
{
    setupUi();
}

PrinterTerminalItem::~PrinterTerminalItem()
{
    delete _messageMethodLabel;
    delete _messageTimestampLabel;
    delete _responseMessageLabel;

    if(_layout)
        delete _layout;
}

void PrinterTerminalItem::setupUi()
{
    _layout = new QGridLayout(this);
    _layout->setSpacing(12);

    _messageTimestampLabel = new QLabel();
    _messageTimestampLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    _messageTimestampLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    _messageTimestampLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTimestamp"));

    _messageMethodLabel = new QLabel();
    _messageMethodLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    _messageMethodLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTitle"));

    _responseMessageLabel = new QLabel();
    _responseMessageLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    _responseMessageLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageText"));

    _layout->addWidget(_messageMethodLabel,0,0,1,2);
    _layout->addWidget(_messageTimestampLabel,1,1,1,1);
    _layout->addWidget(_responseMessageLabel,1,0,1,1);

    setLayout(_layout);

    //setFixedHeight(75);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessage"));
}

KlipperResponse PrinterTerminalItem::response() const
{
    return _response;
}

void PrinterTerminalItem::setResponse(const KlipperResponse &response)
{
    _response = response;

    if(response.status == KlipperResponse::OK)
    {
        _responseMessageLabel->setText(QString("OK"));
        setProperty("status", QVariant::fromValue<QString>("ok"));
    }
    else
    {
        QString error = response.rootObject["error"].toObject()["message"].toString();
        _responseMessageLabel->setText(QString("Error: ") + error);
        setProperty("status", QVariant::fromValue<QString>("error"));
    }

    qint64 span = _message.timestamp.secsTo(response.timestamp);

    _messageTimestampLabel->setText(_message.timestamp.toString(QString("hh:mm:ss - ")) + QString::number(span) + QString("s"));

    style()->polish(this);
}

KlipperMessage PrinterTerminalItem::message() const
{
    return _message;
}

void PrinterTerminalItem::setMessage(const KlipperMessage &message)
{
    _message = message;

    _messageTimestampLabel->setText(_message.timestamp.toString(QString("hh:mm:ss")));
    _messageMethodLabel->setText(_message.document()["method"].toString());
    _responseMessageLabel->setText(QString("Awaiting response.."));
}
