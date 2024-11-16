#ifndef PRINTERTERMINALITEM_H
#define PRINTERTERMINALITEM_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>

#include <QKlipper/qklipper.h>
#include "../../../ui/list/qanimatedlistitem.h"

class PrinterTerminalItem : public QAnimatedListItem
{
    Q_OBJECT
public:
    PrinterTerminalItem(QWidget *parent = nullptr);
    ~PrinterTerminalItem();

    QKlipperMessage *message() const;
    void setMessage(QKlipperMessage *message);

    QJsonValue response() const;

    void setErrorMessage(QString title, QString message);

    bool isErrorMessage() const;
    void setIsErrorMessage(bool isErrorMessage);

protected slots:
    void setupUi();
    void onMessageResponseChanged();
    void onMessageErrorChanged();

private:
    QKlipperMessage *m_message = nullptr;

    //UI
    QGridLayout *m_layout = nullptr;

    QLabel *m_messageTimestampLabel = nullptr;
    QLabel *m_messageMethodLabel = nullptr;
    QLabel *m_responseMessageLabel = nullptr;

    QDateTime m_timestamp;

    bool m_isErrorMessage = false;
};

#endif // PRINTERTERMINALITEM_H
