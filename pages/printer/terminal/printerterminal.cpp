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

    connect(m_instance->console(), SIGNAL(messageSent(QKlipperMessage*)), this, SLOT(on_console_message(QKlipperMessage*)));
    connect(m_instance->console(), SIGNAL(gcodeResponse(QString&)), this, SLOT(onConsoleGcodeResponse(QString&)));
}

PrinterTerminal::~PrinterTerminal()
{
    //m_layout->deleteLater();
}

void PrinterTerminal::on_console_message(QKlipperMessage *message)
{
    if(m_terminal && message->origin() == QKlipperMessage::User)
        m_terminal->addMessage(message);
}

void PrinterTerminal::on_commandEdit_returnPressed()
{
    sendCommand();
}

void PrinterTerminal::on_commandEdit_textChanged()
{
    QString text = m_commandEdit->toPlainText();

    //emulate return pressed from line edit
    if(text.contains(QString("\n")))
    {
        text.remove("\n");
        text.remove("\r");

        m_commandEdit->setText(text);
        m_commandSendButton->setEnabled(false);

        sendCommand();
    }

    if(text.isEmpty() && m_commandSendButton->isEnabled())
        m_commandSendButton->setEnabled(false);
    else if(!text.isEmpty() && !m_commandSendButton->isEnabled())
        m_commandSendButton->setEnabled(true);
}

void PrinterTerminal::on_commandSendButton_clicked()
{
    sendCommand();
}

void PrinterTerminal::onConsoleGcodeResponse(QString &message)
{
    m_terminal->addGcodeResponse(message);
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

    m_terminal = new PrinterTerminalWidget(this);
    m_terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addWidget(m_terminal, 2,0,1,1);

    m_commandLayout = new QHBoxLayout(this);
    m_commandLayout->setContentsMargins(4,4,0,2);
    m_commandLayout->setSpacing(0);
    m_commandFrame = new QFrame(this);
    m_commandFrame->setLayout(m_commandLayout);
    m_commandFrame->setFixedHeight(45);
    m_commandFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_commandFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));
    m_layout->addWidget(m_commandFrame, 3,0,1,1);

    m_commandEdit = new QTextEdit();
    m_commandEdit->setFixedHeight(35);
    m_commandEdit->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleCommandEdit"));

    m_commandLayout->addWidget(m_commandEdit);
    connect(m_commandEdit, SIGNAL(textChanged()), this, SLOT(on_commandEdit_textChanged()));

    m_commandSendButton = new QPushButton(this);
    m_commandSendButton->setText(QString("Send"));
    m_commandSendButton->setEnabled(false);
    m_commandSendButton->setFixedHeight(30);
    m_commandSendButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleCommandButton"));
    m_commandLayout->addWidget(m_commandSendButton);
    connect(m_commandSendButton, SIGNAL(clicked(bool)), this, SLOT(on_commandSendButton_clicked()));

    m_highlighter = new QSourceHighliter(m_commandEdit->document());
    m_highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
    m_highlighter->setTheme(QSourceHighliter::System);

    setLayout(m_layout);
}

void PrinterTerminal::sendCommand()
{
    QString commandString = m_commandEdit->toPlainText();
    m_commandEdit->clear();

    QRegularExpressionMatchIterator match = m_gcodeExpression.globalMatch(commandString);

    QStringList segmentedCommand = commandString.split(QString(" "), Qt::SkipEmptyParts);

    if(segmentedCommand.isEmpty())
        return;

    QStringList macros;
    for(auto macro : m_instance->server()->gcodeMacros())
        macros.append(macro.macro);

    //Check if its a gcode
    if(match.hasNext())
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
            m_instance->console()->printerGcodeScript(commandString, nullptr, QKlipperMessage::User);
        else
        {
            QString message = QString("Missing parameters: ") + missingParameters.join(QString(", "));
            message += QString("\n\n") + QString("Help: ") + command->help() + QString("\n");

            m_terminal->addErrorMessage(command->command(), message);
        }
    }
    else if(segmentedCommand[0][0] == '$' || macros.contains(segmentedCommand[0].toUpper()))
    {
        QKlipperMessage *message = new QKlipperMessage(this);

        message->setMethod("printer.gcode.script");
        message->setParam("script", commandString.right(0));
        message->setOrigin(QKlipperMessage::User);

        segmentedCommand.removeAt(0);

        m_instance->console()->sendWebSocketMessage(message);
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

                message->params().insert(key, value);
            }
            else
                message->params().insert(param, QVariant());
        }

        m_instance->console()->sendWebSocketMessage(message);
    }
}

void PrinterTerminal::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    m_commandEdit->setFocus();
}
