#ifndef PRINTERTERMINALITEM_H
#define PRINTERTERMINALITEM_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>

#include "../../../types/klippermessage.h"
#include "../../../types/klipperresponse.h"
#include "../../../widgets/list/qanimatedlistitem.h"

class PrinterTerminalItem : public QAnimatedListItem
{
    Q_OBJECT
public:
    PrinterTerminalItem(QWidget *parent = nullptr);
    ~PrinterTerminalItem();

protected:
    virtual void setupUi();

private:
    KlipperMessage _message;
    KlipperResponse _response;

    //UI
    QGridLayout *_layout = nullptr;
};

#endif // PRINTERTERMINALITEM_H
