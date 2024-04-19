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
    delete _responseMethodLabel;
    delete _responseTimestampLabel;

    if(_layout)
        delete _layout;
}

void PrinterTerminalItem::setupUi()
{
    _layout = new QGridLayout(this);

    _messageTimestampLabel = new QLabel();
    _messageMethodLabel = new QLabel();

    _responseTimestampLabel = new QLabel();
    _responseMethodLabel = new QLabel();

    _layout->addWidget(_messageMethodLabel,0,0,1,1);
    _layout->addWidget(_messageTimestampLabel,0,1,1,1);
    _layout->addWidget(_responseMethodLabel,1,0,1,1);
    _layout->addWidget(_responseTimestampLabel,1,1,1,1);

    setLayout(_layout);

    setFixedHeight(75);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessage"));
}

KlipperResponse PrinterTerminalItem::response() const
{
    return _response;
}

void PrinterTerminalItem::setResponse(const KlipperResponse &response)
{
    _response = response;

    _responseMethodLabel->setText(_response.timestamp.toString());

    if(response.status == KlipperResponse::OK)
    {
        _responseMethodLabel->setText(QString("OK"));
        setProperty("status", QVariant::fromValue<QString>("ok"));
    }
    else
    {
        QString error = response.rootObject["error"].toObject()["message"].toString();
        _responseMethodLabel->setText(QString("Error: ") + error);
        setProperty("status", QVariant::fromValue<QString>("error"));
    }

    _responseTimestampLabel->setText(response.timestamp.toString());

    style()->polish(this);
}

KlipperMessage PrinterTerminalItem::message() const
{
    return _message;
}

void PrinterTerminalItem::setMessage(const KlipperMessage &message)
{
    _message = message;

    _messageTimestampLabel->setText(_message.timestamp.toString());
    _messageMethodLabel->setText(_message.document()["method"].toString());
    _responseMethodLabel->setText(QString("Awaiting response.."));
}
