#include "printerterminalwidget.h"

PrinterTerminalWidget::PrinterTerminalWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{
    setAutoScroll(true);
    setSelectionMode(NoSelect);

    scrollAreaContents()->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));
}

void PrinterTerminalWidget::addMessage(QKlipperMessage *message)
{
    if(message->origin() == QKlipperMessage::User)
    {
        PrinterTerminalItem *item = new PrinterTerminalItem(this);
        item->setMessage(message);
        item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_itemMap[message->id()] = item;
        addItem(item);
    }
}

void PrinterTerminalWidget::addMessage(QString title, QString message)
{
    PrinterTerminalItem *item = new PrinterTerminalItem(this);
    item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    item->setMessage(title, message);
    addItem(item);
}

void PrinterTerminalWidget::addErrorMessage(QString title, QString message)
{
    PrinterTerminalItem *item = new PrinterTerminalItem(this);
    item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    item->setErrorMessage(title, message);
    addItem(item);
}

void PrinterTerminalWidget::addGcodeResponse(QString &message)
{
    if(message.startsWith("// Unknown command:"))
    {
        message.remove("// ");

        QString command = message.mid(16);
        command.remove("\"");

        bool found = false;

        for(PrinterTerminalItem *item : m_itemMap)
        {
            if(item->message()->isGcode() &&
                item->message()->param("script").toString().toLower() == command.toLower())
            {
                item->setErrorMessage("GCode " + command, message);
                found = true;
                break;
            }
        }

        if(!found)
        {
            addErrorMessage("Error", message);
        }
    }
    else
    {
        if(message.startsWith("!! "))
        {
            message.remove(s_gcodeErrorResponseCleanup);
            addErrorMessage("Error", message);
        }
        else
        {
            message.remove(s_gcodeResponseCleanup);
            addMessage("", message);
        }
    }
}
