#ifndef EDITPRINTERDIALOG_H
#define EDITPRINTERDIALOG_H

#include <QDialog>

#include "../../../types/printer.h"
#include "editprinterextruderpage.h"


namespace Ui {
class EditPrinterDialog;
}

class EditPrinterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPrinterDialog(QWidget *parent = nullptr);
    ~EditPrinterDialog();

    Printer *printer() const;
    void setPrinter(Printer *printer);

private:
    Ui::EditPrinterDialog *ui;

    Printer *_printer = nullptr;
    QList<EditPrinterExtruderPage*> _extruderPages;
};

#endif // EDITPRINTERDIALOG_H
