#include "editprinterdialog.h"
#include "ui_editprinterdialog.h"

EditPrinterDialog::EditPrinterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditPrinterDialog)
{
    ui->setupUi(this);
}

EditPrinterDialog::~EditPrinterDialog()
{
    delete ui;
}

Printer *EditPrinterDialog::printer() const
{
    return _printer;
}

void EditPrinterDialog::setPrinter(Printer *printer)
{
    _printer = printer;
    setWindowTitle(_printer->name());

    ui->printerNameEdit->setText(_printer->name());
    ui->printerInstanceLocationEdit->setText(_printer->instanceLocation());

    for(int i = 0; i < _printer->toolhead()->extruderCount(); i++)
    {
        EditPrinterExtruderPage *page = new EditPrinterExtruderPage();
        page->setExtruder(_printer->toolhead()->extruder(i));

        ui->toolBox->addItem(page, QString("Extruder") + ((i > 0) ? QString(" ") + QString::number(i) : QString("")));
    }
}
