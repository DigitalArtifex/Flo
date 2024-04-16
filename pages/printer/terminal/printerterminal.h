#ifndef PRINTERTERMINAL_H
#define PRINTERTERMINAL_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include "printerterminalwidget.h"
#include "../../../widgets/list/qanimatedlistwidget.h"
#include "../../../types/printer.h"

class PrinterTeminal : public QFrame
{
    Q_OBJECT
public:
    PrinterTeminal(QWidget *parent = nullptr);

private:
    QGridLayout *_layout = nullptr;
    PrinterTerminalWidget *_terminal = nullptr;

    Printer *_printer = nullptr;
};

#endif // PRINTERTERMINAL_H
