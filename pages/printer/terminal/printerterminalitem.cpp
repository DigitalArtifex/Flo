#include "printerterminalitem.h"

PrinterTerminalItem::PrinterTerminalItem(QWidget *parent)
    : QAnimatedListItem(parent)
{

}

PrinterTerminalItem::~PrinterTerminalItem()
{
    if(_layout)
        delete _layout;
}

void PrinterTerminalItem::setupUi()
{
    _layout = new QGridLayout(this);

}
