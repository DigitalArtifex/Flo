#include "printerterminal.h"
#include "flo/settings.h"

using namespace QSourceHighlite;

PrinterTerminal::PrinterTerminal(QKlipperInstance *instance, QWidget *parent) :
    Page(parent)
{
    m_gcodeExpression = QRegularExpression("^\\s*[g|G|m|M]\\d+", QRegularExpression::MultilineOption);
    m_instance = instance;

    setupUi();

    setWindowTitle(QString("%1 Terminal").arg(instance->name()));

    //connect(m_instance->console(), SIGNAL(messageSent(QKlipperMessage*)), this, SLOT(on_console_message(QKlipperMessage*)));
    connect(m_instance->console(), SIGNAL(gcodeResponse(QString&)), this, SLOT(onConsoleGcodeResponse(QString&)));

    connect(m_instance->server(), SIGNAL(gcodeMacrosChanged()), this, SLOT(updateAutocomplete()));
}

PrinterTerminal::~PrinterTerminal()
{
    //m_layout->deleteLater();
}

void PrinterTerminal::onConsoleGcodeResponse(QString &message)
{
    QString formattedMessage;
    QString messageColor;

    if(message.startsWith("//"))
        messageColor = Settings::get("theme/highlight-comment").toString();

    else if(message.startsWith("!!"))
        messageColor = Settings::get("theme/highlight-string").toString();

    message.remove(0,2);

    while(message.startsWith(" "))
        message.removeAt(0);

    formattedMessage =
        QString("<font color=%1><i>%2</i></font>").arg
        (
            messageColor,
            message
        );

    m_terminal->addMessage(message);
}

void PrinterTerminal::onKlipperSocketMessageReceived(QString message)
{
    QJsonParseError documentError;
    QJsonDocument document = QJsonDocument::fromJson(message.toLatin1(), &documentError);

    if(documentError.error != QJsonParseError::NoError)
    {
        m_terminal->addMessage(message);
        return;
    }

    QJsonObject rootObject = document.object();
    if(rootObject.contains("error"))
    {
        QJsonObject errorObject = rootObject["error"].toObject();
        QString error =
            QString("<font color=%1><b>%2:</b> <i>%3</i></font>").arg
            (
                Settings::get("theme/highlight-string").toString(),
                errorObject["error"].toString(),
                errorObject["message"].toString()
            );

        m_terminal->addMessage(error);
    }
    else
    {
        //m_terminal->addMessage(message.toLatin1());
    }
}

void PrinterTerminal::onKlipperSocketDisconnected()
{
    delete m_klipperSocket;
    m_klipperSocket = nullptr;
}

void PrinterTerminal::onKlipperSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << "Klipper Socket Error" << error;
    delete m_klipperSocket;
    m_klipperSocket = nullptr;
}

void PrinterTerminal::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    m_viewer = new QQuickView();
    m_viewerWidget = QWidget::createWindowContainer(m_viewer, this);
    m_viewerWidget->setFixedSize(0,0);
    m_layout->addWidget(m_viewerWidget,0,0);
    m_viewer->show();

    //Action bar
    m_actionBar = new QWidget();
    m_actionBarLayout = new QGridLayout(m_actionBar);
    m_actionBarLayout->setContentsMargins(4,4,4,4);
    m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    m_actionBarLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Ignored), 0, 0);

    m_closeButton = new QIconButton(m_actionBar);
    m_closeButton->setIcon(Settings::getThemeIcon(QString("multiply")));
    m_closeButton->setFixedSize(50,50);
    m_closeButton->setTextMargins(QMargins(34,0,0,0));
    m_closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_actionBarLayout->addWidget(m_closeButton, 0, 1, 1, 1);
    m_layout->addWidget(m_actionBar, 1,0,1,1);

    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));

    m_terminal = new PrinterTerminalEdit(this);
    m_terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(m_terminal, SIGNAL(commandEntered(QString)), this, SLOT(sendCommand(QString)));
    m_layout->addWidget(m_terminal, 2,0,1,1);

    setLayout(m_layout);
}

void PrinterTerminal::sendCommand(QString commandString)
{
    QRegularExpressionMatchIterator match = m_gcodeExpression.globalMatch(commandString);

    QStringList segmentedCommand = commandString.split(QString(" "), Qt::SkipEmptyParts);

    if(segmentedCommand.isEmpty())
        return;

    QStringList macros;
    for(auto macro : m_instance->server()->gcodeMacros())
        macros.append(macro.macro.toUpper());

    //Check if its a gcode

    if(segmentedCommand[0].toLower() == "help")
    {
        segmentedCommand.remove(0);
        displayHelp(segmentedCommand.join(" "));
        return;
    }
    else if(match.hasNext() || macros.contains(commandString.toUpper()))
        m_instance->console()->printerGcodeScript(commandString, nullptr, QKlipperMessage::User);

    //Check if its a klipper command instead
    else if(QKlipperCommand::isKlipperCommand(segmentedCommand[0]))
    {
        QKlipperCommand *command = new QKlipperCommand(segmentedCommand[0]);

        //Check for command validity
        //Start with a valid state for commands with no parameters
        bool valid = true;
        QStringList missingParameters;

        //Iterate through required parameters
        for(QString parameter : command->parameters())
        {
            bool found = false;

            for(int i = 1; i < segmentedCommand.count(); i++)
            {
                QStringList segmentedParameter = parameter.split(QString("="), Qt::SkipEmptyParts);

                if(segmentedParameter[0].toUpper() == parameter.toUpper())
                {
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                valid = false;
                missingParameters += parameter;
            }
        }

        if(valid)
        {
            QKlipperMessage *message = new QKlipperMessage(this);
            message->setMethod("gcode/script");
            message->setOrigin(QKlipperMessage::User);
            message->setParam("script", commandString);

            segmentedCommand.removeAt(0);

            if(connectToKlipper())
            {
                m_klipperSocket->sendTextMessage(message->toRpc());
            }
        }
        else
        {
            QString message = QString("Missing parameters: ") + missingParameters.join(QString(", "));
            message += QString("\n\n") + QString("Help: ") + command->help() + QString("\n");

            m_terminal->addMessage(message);
        }
    }
    else
    {
        QKlipperMessage *message = new QKlipperMessage(this);
        message->setMethod(segmentedCommand[0]);
        message->setOrigin(QKlipperMessage::User);

        segmentedCommand.removeAt(0);

        for(QString param : segmentedCommand)
        {
            if(param.contains("="))
            {
                QString key = param.left('=');
                QString value = param.right('=');

                message->setParam(key, value);
            }
            else
                message->setParam(param, QVariant());
        }

        if(connectToKlipper())
            m_klipperSocket->sendTextMessage(message->toRpc());
    }
}

void PrinterTerminal::displayHelp(QString command)
{
    if(command.length() > 0)
    {
        QStringList segmentedCommand = command.split(' ');

        for(QString segment : segmentedCommand)
        {
            if(QKlipperCommand::isKlipperCommand(segment.toUpper()))
                m_terminal->addMessage(QKlipperCommand::command(segment.toUpper()).help());
        }
    }
    else if(command.toUpper() == "MACROS")
    {
        int cols = 3;
        int col = 0;
        QString buffer = "<table>";

        for(auto macro : m_instance->server()->gcodeMacros())
        {
            if(col == 0)
            {
                buffer += "<tr>";
            }

            if(col < cols)
            {
                if(!m_macros.contains(command))
                {
                    buffer += QString("<td>%1</td>").arg(macro.macro);
                    col++;
                }
            }
            else
            {
                col = 0;
                buffer += "</tr>";
            }
        }

        buffer += "</table>";
        m_terminal->addMessage(buffer);
    }
    else
    {
        int cols = 3;
        int col = 0;
        QString buffer = "<table>";

        for(QString klipperCommand : QKlipperCommand::commands())
        {
            if(col == 0)
            {
                buffer += "<tr>";
            }

            if(col < cols)
            {
                if(!m_macros.contains(command))
                {
                    buffer += QString("<td>%1</td>").arg(klipperCommand);
                    col++;
                }
            }
            else
            {
                col = 0;
                buffer += "</tr>";
            }
        }

        buffer += "</table>";
        m_terminal->addMessage(buffer);
    }
}

void PrinterTerminal::updateAutocomplete()
{
    QStringList dictionary;
    QMultiMap<QString,QString> parameterDictionary;

    m_macros.clear();

    for(QKlipperCommand command : QKlipperCommand::commands())
    {
        if(command.command().isEmpty())
            continue;

        if(!dictionary.contains(command.command()))
        {
            dictionary.append(command.command());
            parameterDictionary.insert("HELP", command.command());
        }

        for(QString parameter : command.parameters())
            parameterDictionary.insert(command.command(), parameter.toUpper());

    }

    for(QKlipperGCodeMacro macro : m_instance->server()->gcodeMacros())
    {
        if(!dictionary.contains(macro.macro))
            dictionary.append(macro.macro);

        if(!m_macros.contains(macro.macro))
            m_macros.append(macro.macro);
    }

    m_terminal->setCommandDictionary(dictionary);
    m_terminal->setParameterDictionary(parameterDictionary);
}

void PrinterTerminal::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    m_terminal->setHost(m_instance->server()->address());

    if(m_instance->server()->accessDetails().isLoggedIn())
        m_terminal->setUser(m_instance->server()->accessDetails().user().username());
}

bool PrinterTerminal::connectToKlipper()
{
    if(!m_klipperSocket)
    {
        m_klipperSocket = new QWebSocket(
            m_instance->server()->bridgeAddress(),
            QWebSocketProtocol::VersionLatest,
            this
            );
    }

    if(m_klipperSocket->state() == QAbstractSocket::ConnectedState)
        return true;

    QEventLoop loop;
    bool errorOccurred = false;
    QAbstractSocket::SocketError socketError;

    QMetaObject::Connection establishedConnection = QObject::connect(m_klipperSocket, SIGNAL(connected()), &loop, SLOT(quit()));

    QMetaObject::Connection disconnectConnection =  QObject::connect
        (
            m_klipperSocket,
            &QWebSocket::disconnected,
            this,
            [&errorOccurred, &loop]() {
                errorOccurred = true;
                loop.quit();
            }
            );

    QMetaObject::Connection errorConnection = QObject::connect
        (
            m_klipperSocket,
            &QWebSocket::errorOccurred,
            this,
            [&socketError, &errorOccurred, &loop](QAbstractSocket::SocketError error) {
                errorOccurred = true;
                socketError = error;
                loop.quit();
            }
            );

    //QObject::connect(m_klipperSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(rpcUpdateSocketDataReceived(QString)));

    //Timeout for websocket -_-
    QTimer *timeout = new QTimer(this);
    timeout->setInterval(10000);
    timeout->setSingleShot(true);

    auto timeoutLambda = [&socketError, &errorOccurred, &loop]() {
        errorOccurred = true;
        socketError = QAbstractSocket::SocketTimeoutError;
        loop.quit();
    };

    QObject::connect
        (
            timeout,
            &QTimer::timeout,
            this,
            timeoutLambda
            );

    qDebug() << "Connecting to " << m_instance->server()->bridgeAddress();
    m_klipperSocket->open(m_instance->server()->bridgeAddress());
    timeout->start();
    loop.exec();
    timeout->stop();

    timeout->deleteLater();

    m_klipperSocket->disconnect(establishedConnection);
    m_klipperSocket->disconnect(disconnectConnection);
    m_klipperSocket->disconnect(errorConnection);

    connect(m_klipperSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onKlipperSocketMessageReceived(QString)));
    connect(m_klipperSocket, SIGNAL(disconnected()), this, SLOT(onKlipperSocketDisconnected()));
    connect(m_klipperSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onKlipperSocketError(QAbstractSocket::SocketError)));

    if(errorOccurred)
        qDebug() << "Connection Failed";
    else
        qDebug() << "Connected";

    return !errorOccurred;
}

void PrinterTerminal::disconnectFromKlipper()
{
    m_klipperSocket->close();
    delete m_klipperSocket;
    m_klipperSocket = nullptr;
}
