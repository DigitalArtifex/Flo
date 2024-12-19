#include "printerterminalwidget.h"

PrinterTerminalWidget::PrinterTerminalWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{
    m_scrollAreaContents->layout()->setContentsMargins(0,0,0,0);
    m_scrollAreaContents->layout()->setSpacing(0);
    m_scrollAreaContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));
}

void PrinterTerminalWidget::addMessage(QKlipperMessage *message)
{
    if(message->origin() == QKlipperMessage::User)
    {
        m_scrollAreaContents->layout()->setContentsMargins(0,0,0,0);

        PrinterTerminalItem *item = new PrinterTerminalItem(this);
        item->setMessage(message);
        item->setOpacityIn(1);
        item->setOpacityOut(0);
        item->setDuration(500);
        item->setBaseSize(viewport()->width(), 35);

        m_itemMap[message->id()] = item;

        addItem(item);
    }
}

void PrinterTerminalWidget::addMessage(QString title, QString message)
{
    PrinterTerminalItem *item = new PrinterTerminalItem(this);
    item->setMessage(title, message);
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(500);
    item->setBaseSize(viewport()->width(), 35);

    addItem(item);
}

void PrinterTerminalWidget::addErrorMessage(QString title, QString message)
{
    PrinterTerminalItem *item = new PrinterTerminalItem(this);
    item->setErrorMessage(title, message);
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(500);
    item->setBaseSize(viewport()->width(), 35);

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
            addErrorMessage("", message);
        }
    }
    else
    {
        if(message.startsWith("!! "))
        {
            message.remove(s_gcodeErrorResponseCleanup);
            addErrorMessage("", message);
        }
        else
        {
            message.remove(s_gcodeResponseCleanup);
            addMessage("", message);
        }
    }
}
