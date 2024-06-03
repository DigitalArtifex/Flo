#include "printerterminalwidget.h"

PrinterTerminalWidget::PrinterTerminalWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{
    _scrollAreaContents->layout()->setContentsMargins(9,9,9,9);
    _scrollAreaContents->layout()->setSpacing(9);
}

void PrinterTerminalWidget::addMessage(KlipperMessage message)
{
    if(message.origin == KlipperMessage::User)
    {
        PrinterTerminalItem *item = new PrinterTerminalItem(this);
        item->setMessage(message);
        item->setOpacityIn(1);
        item->setOpacityOut(0);
        item->setDuration(100);

        _itemMap[message.id] = item;

        addItem(item);
    }
}

void PrinterTerminalWidget::addResponse(KlipperResponse response)
{
    if(_itemMap.contains(response.id()))
    {
        _itemMap[response.id()]->setResponse(response);
    }
}

void PrinterTerminalWidget::addErrorMessage(QString title, QString message)
{
    PrinterTerminalItem *item = new PrinterTerminalItem(this);
    item->setErrorMessage(title, message);
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(100);

    addItem(item);
}
