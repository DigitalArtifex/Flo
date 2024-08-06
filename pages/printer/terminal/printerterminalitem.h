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

    KlipperMessage *message() const;
    void setMessage(const KlipperMessage &message);

    KlipperResponse response() const;
    void setResponse(const KlipperResponse &response);

    void setErrorMessage(QString title, QString message);

    bool isErrorMessage() const;
    void setIsErrorMessage(bool isErrorMessage);

protected:
    virtual void setupUi();

private:
    KlipperMessage *m_message;
    KlipperResponse m_response;

    //UI
    QGridLayout *m_layout = nullptr;

    QLabel *m_messageTimestampLabel = nullptr;
    QLabel *m_messageMethodLabel = nullptr;
    QLabel *m_responseMessageLabel = nullptr;

    QDateTime m_timestamp;

    bool m_isErrorMessage = false;
};

#endif // PRINTERTERMINALITEM_H
