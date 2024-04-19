#include "printerterminal.h"

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
    if(_commandEdit->text().isEmpty() && _commandSendButton->isEnabled())
        _commandSendButton->setEnabled(false);
    else if(!_commandEdit->text().isEmpty() && !_commandSendButton->isEnabled())
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

    _commandEdit = new QLineEdit();
    _commandEdit->setFixedHeight(32);

    _layout->addWidget(_commandEdit, 1,0,1,1);
    connect(_commandEdit, SIGNAL(returnPressed()), this, SLOT(on_commandEdit_returnPressed()));

    _commandSendButton = new QPushButton();
    _commandSendButton->setText(QString("Send"));
    _commandSendButton->setEnabled(false);
    _commandSendButton->setFixedHeight(32);
    _layout->addWidget(_commandSendButton, 1,1,1,1);
    connect(_commandSendButton, SIGNAL(clicked(bool)), this, SLOT(on_commandSendButton_clicked()));
    //_terminal->setSelectionMode(PrinterTerminalWidget::NoSelect);

    setLayout(_layout);
}

void PrinterTerminal::sendCommand()
{
    QString command = _commandEdit->text();
    _commandEdit->clear();

    if(command.startsWith("g", Qt::CaseInsensitive) || command.startsWith("m", Qt::CaseInsensitive))
        _printer->console()->sendGcode(command);
    else
        _printer->console()->sendCommand(command);
}
