#ifndef PRINTERTERMINAL_H
#define PRINTERTERMINAL_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

#include "printerterminalwidget.h"
#include "../../../types/printer.h"
#include "../../../QSourceHighlite/qsourcehighliter.h"

class PrinterTerminal : public QFrame
{
    Q_OBJECT
public:
    PrinterTerminal(Printer *printer, QWidget *parent = nullptr);
    ~PrinterTerminal();

protected slots:
    void on_console_message(KlipperMessage *message);
    void on_console_response(KlipperResponse response);

    void on_commandEdit_returnPressed();
    void on_commandEdit_textChanged();
    void on_commandSendButton_clicked();

protected:
    virtual void setupUi();
    virtual void sendCommand();
    virtual void showEvent(QShowEvent *event);

private:
    QGridLayout *m_layout = nullptr;
    QTextEdit *m_commandEdit = nullptr;
    QPushButton *m_commandSendButton = nullptr;
    PrinterTerminalWidget *m_terminal = nullptr;

    Printer *m_printer = nullptr;

    QSourceHighlite::QSourceHighliter *m_highlighter = nullptr;
};

#endif // PRINTERTERMINAL_H
