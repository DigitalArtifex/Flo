#ifndef PRINTERTERMINAL_H
#define PRINTERTERMINAL_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include "printerterminalwidget.h"
#include "../../../types/printer.h"

class PrinterTerminal : public QFrame
{
    Q_OBJECT
public:
    PrinterTerminal(Printer *printer, QWidget *parent = nullptr);
    ~PrinterTerminal();

protected:
    virtual void setupUi();

private:
    QGridLayout *_layout = nullptr;
    PrinterTerminalWidget *_terminal = nullptr;

    Printer *_printer = nullptr;
};

#endif // PRINTERTERMINAL_H
