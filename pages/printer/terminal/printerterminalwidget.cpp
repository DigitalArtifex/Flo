#include "printerterminalwidget.h"

PrinterTerminalWidget::PrinterTerminalWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{
    m_scrollAreaContents->layout()->setContentsMargins(0,0,0,0);
    m_scrollAreaContents->layout()->setSpacing(9);
    m_scrollAreaContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));
}

void PrinterTerminalWidget::addMessage(QKlipperMessage *message)
{
    if(message->origin() == QKlipperMessage::User)
    {
        m_scrollAreaContents->layout()->setContentsMargins(9,9,9,9);
        PrinterTerminalItem *item = new PrinterTerminalItem(this);
        item->setMessage(message);
        item->setOpacityIn(1);
        item->setOpacityOut(0);
        item->setDuration(100);

        m_itemMap[message->id()] = item;

        addItem(item);
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

void PrinterTerminalWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
}
