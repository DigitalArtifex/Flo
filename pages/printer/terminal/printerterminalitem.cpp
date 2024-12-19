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

QKlipperMessage *PrinterTerminalItem::message() const
{
    return m_message;
}

void PrinterTerminalItem::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(9);

    m_messageTimestampLabel = new QLabel();
    m_messageTimestampLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_messageTimestampLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    m_messageTimestampLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTimestamp"));

    m_messageMethodLabel = new QLabel();
    m_messageMethodLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_messageMethodLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTitle"));

    m_responseMessageLabel = new QLabel();
    m_responseMessageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_messageTimestampLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    m_responseMessageLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageText"));

    m_layout->addWidget(m_messageMethodLabel,0,0,1,2);
    m_layout->addWidget(m_responseMessageLabel,1,0,1,1);
    m_layout->addWidget(m_messageTimestampLabel,1,1,1,1);

    setLayout(m_layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessage"));
    style()->polish(this);
}

void PrinterTerminalItem::onMessageResponseChanged()
{
    QString message = m_responseMessageLabel->text();

    if(m_message->response().toString().isEmpty() && message.startsWith("Awaiting"))
    {
        if(m_message->error().type() == QKlipperError::NoError)
            message = "OK";
    }
    else
        message += m_message->response().toString();

    m_responseMessageLabel->setText(message);

    if(m_message->error().type() == QKlipperError::NoError)
        setProperty("status", QVariant::fromValue<QString>("ok"));

    if(message.startsWith("// Unknown Command:", Qt::CaseInsensitive))
        setProperty("status", QVariant::fromValue<QString>("error"));

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
    if(m_message)
    {
        disconnect(m_message, SIGNAL(responseChanged()), this, SLOT(onMessageResponseChanged()));
        disconnect(m_message, SIGNAL(errorChanged()), this, SLOT(onMessageErrorChanged()));
    }

    if(title.isEmpty())
        m_messageMethodLabel->setMaximumHeight(0);
    else
        m_messageMethodLabel->setText(title);

    m_responseMessageLabel->setText(message);
    m_responseMessageLabel->setWordWrap(true);

    m_messageTimestampLabel->setText(QDateTime::currentDateTime().toString(QString("hh:mm:ss")));

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
        m_messageMethodLabel->setText(QString("GCode: %1").arg(message->param("script").toString().toUpper()));
    }
    else
        m_messageMethodLabel->setText(method);

    m_responseMessageLabel->setText(QString("Awaiting response.."));

    style()->polish(this);
}

void PrinterTerminalItem::setMessage(QString title, QString message)
{
    if(m_message)
    {
        disconnect(m_message, SIGNAL(responseChanged()), this, SLOT(onMessageResponseChanged()));
        disconnect(m_message, SIGNAL(errorChanged()), this, SLOT(onMessageErrorChanged()));
    }

    if(title.isEmpty())
    {
        m_messageMethodLabel->setVisible(false);
        m_messageMethodLabel->setMaximumHeight(0);

        m_layout->removeWidget(m_messageMethodLabel);
        m_layout->removeWidget(m_responseMessageLabel);
        m_layout->removeWidget(m_messageTimestampLabel);

        //m_layout->addWidget(m_messageMethodLabel,0,0,1,2);
        m_layout->addWidget(m_responseMessageLabel,0,0,1,1, Qt::AlignTop);
        m_layout->addWidget(m_messageTimestampLabel,0,1,1,1, Qt::AlignTop);
    }
    else
        m_messageMethodLabel->setText(title);

    m_responseMessageLabel->setText(message);
    m_responseMessageLabel->setWordWrap(true);

    m_messageTimestampLabel->setText(QDateTime::currentDateTime().toString(QString("hh:mm:ss")));

    style()->polish(this);
}
