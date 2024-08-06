#include "printerterminalitem.h"

PrinterTerminalItem::PrinterTerminalItem(QWidget *parent)
    : QAnimatedListItem(parent)
{
    setupUi();
}

PrinterTerminalItem::~PrinterTerminalItem()
{
    delete m_messageMethodLabel;
    delete m_messageTimestampLabel;
    delete m_responseMessageLabel;

    if(m_layout)
        delete m_layout;
}

void PrinterTerminalItem::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(12);

    m_messageTimestampLabel = new QLabel();
    m_messageTimestampLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_messageTimestampLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    m_messageTimestampLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTimestamp"));

    m_messageMethodLabel = new QLabel();
    m_messageMethodLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_messageMethodLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageTitle"));

    m_responseMessageLabel = new QLabel();
    m_responseMessageLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_responseMessageLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessageText"));

    m_layout->addWidget(m_messageMethodLabel,0,0,1,2);
    m_layout->addWidget(m_messageTimestampLabel,1,1,1,1);
    m_layout->addWidget(m_responseMessageLabel,1,0,1,1);

    setLayout(m_layout);

    //setFixedHeight(75);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleMessage"));
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

KlipperResponse PrinterTerminalItem::response() const
{
    return m_response;
}

void PrinterTerminalItem::setResponse(const KlipperResponse &response)
{
    if(response.status == KlipperResponse::OK)
    {
        m_responseMessageLabel->setText(QString("OK"));
        setProperty("status", QVariant::fromValue<QString>("ok"));
    }
    else
    {
        QString error = response.rootObject["error"].toObject()["message"].toString();
        m_responseMessageLabel->setText(QString("Error: ") + error);
        setProperty("status", QVariant::fromValue<QString>("error"));
    }

    qint64 span = m_timestamp.secsTo(response.timestamp);

    QString text = m_messageTimestampLabel->text();
    m_messageTimestampLabel->setText(QString("%1 - %2s").arg(text).arg(QString::number(span)));

    style()->polish(this);
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

void PrinterTerminalItem::setMessage(const KlipperMessage &message)
{
    m_timestamp = message.timestamp;

    QString method = message.document()["method"].toString();

    m_messageTimestampLabel->setText(message.timestamp.toString(QString("hh:mm:ss")));

    if(method == QString("printer.gcode.script"))
    {
        QJsonObject paramsObject = message.document()["params"].toObject();
        m_messageMethodLabel->setText(QString("GCode: %1").arg(paramsObject["script"].toString()));
    }
    else
        m_messageMethodLabel->setText(method);

    m_responseMessageLabel->setText(QString("Awaiting response.."));

    style()->polish(this);
}
