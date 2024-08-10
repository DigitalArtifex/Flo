#include "printerterminal.h"

using namespace QSourceHighlite;

PrinterTerminal::PrinterTerminal(Printer *printer, QWidget *parent)
{
    m_printer = printer;

    setupUi();

    connect(m_printer->console(), SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_console_response(KlipperResponse)));
    connect(m_printer->console(), SIGNAL(commandSent(KlipperMessage*)), this, SLOT(on_console_message(KlipperMessage*)));
}

PrinterTerminal::~PrinterTerminal()
{
    delete m_commandEdit;
    delete m_commandSendButton;
    delete m_layout;
}

void PrinterTerminal::on_console_message(KlipperMessage *message)
{
    if(m_terminal)
        m_terminal->addMessage(message);
}

void PrinterTerminal::on_console_response(KlipperResponse response)
{
    if(m_terminal)
        m_terminal->addResponse(response);
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

void PrinterTerminal::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,6);

    m_terminal = new PrinterTerminalWidget(this);
    m_layout->addWidget(m_terminal, 0,0,1,2);
    m_terminal->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));

    m_commandEdit = new QTextEdit();
    m_commandEdit->setFixedHeight(32);
    m_commandEdit->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleCommandEdit"));

    m_layout->addWidget(m_commandEdit, 1,0,1,1);
    connect(m_commandEdit, SIGNAL(textChanged()), this, SLOT(on_commandEdit_textChanged()));

    m_commandSendButton = new QPushButton();
    m_commandSendButton->setText(QString("Send"));
    m_commandSendButton->setEnabled(false);
    m_commandSendButton->setFixedHeight(32);
    m_commandSendButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ConsoleCommandButton"));
    m_layout->addWidget(m_commandSendButton, 1,1,1,1);
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

    QRegularExpression gcodeExpression("^\\s*[g|G|m|M]\\d+", QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator match = gcodeExpression.globalMatch(commandString);

    QStringList segmentedCommand = commandString.split(QString(" "), Qt::SkipEmptyParts);

    //Check if its a gcode
    if(match.hasNext())
        m_printer->console()->sendGcode(commandString, KlipperMessage::User);

    //Check if its a klipper command instead
    else if(!segmentedCommand.isEmpty() && m_printer->console()->isKlipperCommand(segmentedCommand[0]))
    {
        QAbstractKlipperConsole::KlipperCommand command = m_printer->console()->klipperCommand(segmentedCommand[0]);

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
            m_printer->console()->sendGcode(commandString, KlipperMessage::User);
        else
        {
            QString message = QString("Missing parameters: ") + missingParameters.join(QString(", "));
            message += QString("\n\n") + QString("Help: ") + command.help + QString("\n");

            m_terminal->addErrorMessage(command.command, message);
        }
    }
    else
        m_printer->console()->sendCommand(commandString, KlipperMessage::User);
}

void PrinterTerminal::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    m_commandEdit->setFocus();
}
