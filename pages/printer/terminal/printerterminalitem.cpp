#include "printerterminalitem.h"

PrinterTerminalItem::PrinterTerminalItem(QWidget *parent)
    : QAnimatedListItem(parent)
{
    setupUi();
}

PrinterTerminalItem::~PrinterTerminalItem()
{
    // if(m_layout)
    //     m_layout->deleteLater();
}

void PrinterTerminalItem::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(12);

    m_messageTimestampLabel = new QLabel();
    m_messageTimestampLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_messageTimestampLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    m_messageTimestampLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTimestamp"));

    m_messageMethodLabel = new QLabel();
    m_messageMethodLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_messageMethodLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTitle"));

    m_responseMessageLabel = new QLabel();
    m_responseMessageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_responseMessageLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageText"));

    m_layout->addWidget(m_messageMethodLabel,0,0,1,1);
    m_layout->addWidget(m_responseMessageLabel,1,0,1,1);
    m_layout->addWidget(m_messageTimestampLabel,1,1,1,1);

    setLayout(m_layout);

    //setFixedHeight(75);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessage"));
    style()->polish(this);
}

void PrinterTerminalItem::onMessageResponseChanged()
{
    if(m_message->error().type() == QKlipperError::NoError)
    {
        m_responseMessageLabel->setText(QString("OK"));
        setProperty("status", QVariant::fromValue<QString>("ok"));
    }

    qint64 span = m_timestamp.secsTo(m_message->responseTimestamp());

    QString text = m_messageTimestampLabel->text();
    m_messageTimestampLabel->setText(QString("%1 - %2s").arg(text, QString::number(span)));

    style()->polish(this);
}

void PrinterTerminalItem::onMessageErrorChanged()
{
    QString error = m_message->error().errorString();
    m_responseMessageLabel->setText(QString("Error: ") + error);
    setProperty("status", QVariant::fromValue<QString>("error"));

    qint64 span = m_timestamp.secsTo(m_message->responseTimestamp());

    QString text = m_messageTimestampLabel->text();
    m_messageTimestampLabel->setText(QString("%1 - %2s").arg(text, QString::number(span)));

    style()->polish(this);
}

bool PrinterTerminalItem::isErrorMessage() const
{
    return m_isErrorMessage;
}

void PrinterTerminalItem::setIsErrorMessage(bool isErrorMessage)
{
    m_isErrorMessage = isErrorMessage;
}

QJsonValue PrinterTerminalItem::response() const
{
    return m_message->response();
}

void PrinterTerminalItem::setErrorMessage(QString title, QString message)
{
    m_messageMethodLabel->setText(title);

    m_responseMessageLabel->setText(message);
    m_responseMessageLabel->setWordWrap(true);

    m_isErrorMessage = true;

    setProperty("status", QVariant::fromValue<QString>("error"));

    style()->polish(this);
}

void PrinterTerminalItem::setMessage(QKlipperMessage *message)
{
    if(m_message)
    {
        disconnect(m_message, SIGNAL(responseChanged()), this, SLOT(onMessageResponseChanged()));
        disconnect(m_message, SIGNAL(errorChanged()), this, SLOT(onMessageErrorChanged()));
    }

    m_message = message;

    connect(m_message, SIGNAL(responseChanged()), this, SLOT(onMessageResponseChanged()));
    connect(m_message, SIGNAL(errorChanged()), this, SLOT(onMessageErrorChanged()));

    m_timestamp = message->timestamp();

    QString method = message->method();

    m_messageTimestampLabel->setText(message->timestamp().toString(QString("hh:mm:ss")));

    if(method == QString("printer.gcode.script"))
    {
        m_messageMethodLabel->setText(QString("GCode: %1").arg(message->param("script").toString()));
    }
    else
        m_messageMethodLabel->setText(method);

    m_responseMessageLabel->setText(QString("Awaiting response.."));

    style()->polish(this);
}
