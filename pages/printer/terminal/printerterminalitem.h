#ifndef PRINTERTERMINALITEM_H
#define PRINTERTERMINALITEM_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>

#include "../../../types/klippermessage.h"
#include "../../../types/klipperresponse.h"
#include "../../../ui/list/qanimatedlistitem.h"

class PrinterTerminalItem : public QAnimatedListItem
{
    Q_OBJECT
public:
    PrinterTerminalItem(QWidget *parent = nullptr);
    ~PrinterTerminalItem();

    KlipperMessage message() const;
    void setMessage(const KlipperMessage &message);

    KlipperResponse response() const;
    void setResponse(const KlipperResponse &response);

protected:
    virtual void setupUi();

private:
    KlipperMessage _message;
    KlipperResponse _response;

    //UI
    QGridLayout *_layout = nullptr;

    QLabel *_messageTimestampLabel = nullptr;
    QLabel *_messageMethodLabel = nullptr;
    QLabel *_responseMessageLabel = nullptr;
};

#endif // PRINTERTERMINALITEM_H
