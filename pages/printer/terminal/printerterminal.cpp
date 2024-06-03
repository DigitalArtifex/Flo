#include "printerterminal.h"

using namespace QSourceHighlite;

PrinterTerminal::PrinterTerminal(Printer *printer, QWidget *parent)
{
    _printer = printer;

    setupUi();

    connect(_printer->console(), SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_console_response(KlipperResponse)));
    connect(_printer->console(), SIGNAL(commandSent(KlipperMessage)), this, SLOT(on_console_message(KlipperMessage)));
}

PrinterTerminal::~PrinterTerminal()
{
    delete _commandEdit;
    delete _commandSendButton;
    delete _layout;
}

void PrinterTerminal::on_console_message(KlipperMessage message)
{
    if(_terminal)
        _terminal->addMessage(message);
}

void PrinterTerminal::on_console_response(KlipperResponse response)
{
    if(_terminal)
        _terminal->addResponse(response);
}

void PrinterTerminal::on_commandEdit_returnPressed()
{
    sendCommand();
}

void PrinterTerminal::on_commandEdit_textChanged()
{
    QString text = _commandEdit->toPlainText();
    if(text.contains(QString("\n")))
    {
        text.remove("\n");
        text.remove("\r");

        _commandEdit->setText(text);
        _commandSendButton->setEnabled(false);

        sendCommand();
    }

    if(text.isEmpty() && _commandSendButton->isEnabled())
        _commandSendButton->setEnabled(false);
    else if(!text.isEmpty() && !_commandSendButton->isEnabled())
        _commandSendButton->setEnabled(true);
}

void PrinterTerminal::on_commandSendButton_clicked()
{
    sendCommand();
}

void PrinterTerminal::setupUi()
{
    _layout = new QGridLayout(this);
    _layout->setContentsMargins(0,0,0,6);

    _terminal = new PrinterTerminalWidget(this);
    _layout->addWidget(_terminal, 0,0,1,2);

    _commandEdit = new QTextEdit();
    _commandEdit->setFixedHeight(32);
    _commandEdit->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleCommandEdit"));

    _layout->addWidget(_commandEdit, 1,0,1,1);
    connect(_commandEdit, SIGNAL(textChanged()), this, SLOT(on_commandEdit_textChanged()));

    _commandSendButton = new QPushButton();
    _commandSendButton->setText(QString("Send"));
    _commandSendButton->setEnabled(false);
    _commandSendButton->setFixedHeight(32);
    _commandSendButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleCommandButton"));
    _layout->addWidget(_commandSendButton, 1,1,1,1);
    connect(_commandSendButton, SIGNAL(clicked(bool)), this, SLOT(on_commandSendButton_clicked()));

    _highlighter = new QSourceHighliter(_commandEdit->document());
    _highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
    _highlighter->setTheme(QSourceHighliter::System);

    setLayout(_layout);
}

void PrinterTerminal::sendCommand()
{
    QString commandString = _commandEdit->toPlainText();
    _commandEdit->clear();

    QRegularExpression gcodeExpression("^\\s*[g|G|m|M]\\d+", QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator match = gcodeExpression.globalMatch(commandString);

    QStringList segmentedCommand = commandString.split(QString(" "), Qt::SkipEmptyParts);

    //Check if its a gcode
    if(match.hasNext())
        _printer->console()->sendGcode(commandString, KlipperMessage::User);

    //Check if its a klipper command instead
    else if(!segmentedCommand.isEmpty() && _printer->console()->isKlipperCommand(segmentedCommand[0]))
    {
        QAbstractKlipperConsole::KlipperCommand command = _printer->console()->klipperCommand(segmentedCommand[0]);

        //Check for command validity
        //Start with a valid state for commands with no parameters
        bool valid = true;
        QStringList missingParameters;

        //Iterate through required parameters
        foreach(QString parameter, command.parameters)
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
            _printer->console()->sendGcode(commandString, KlipperMessage::User);
        else
        {
            QString message = QString("Missing parameters: ") + missingParameters.join(QString(", "));
            message += QString("\n\n") + QString("Help: ") + command.help + QString("\n");

            _terminal->addErrorMessage(command.command, message);
        }
    }
    else
        _printer->console()->sendCommand(commandString, KlipperMessage::User);
}
