#include "editprinterextruderpage.h"
#include "ui_editprinterextruderpage.h"

EditPrinterExtruderPage::EditPrinterExtruderPage(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::EditPrinterExtruderPage)
{
    ui->setupUi(this);
}

EditPrinterExtruderPage::~EditPrinterExtruderPage()
{
    delete ui;
}

void EditPrinterExtruderPage::setExtruder(Extruder *extruder)
{
    _extruder = extruder;

    ui->xOffsetEdit->setText(QString::number(_extruder->offset().x()));
    ui->yOffsetEdit->setText(QString::number(_extruder->offset().y()));
    ui->zOffsetEdit->setText(QString::number(_extruder->offset().z()));

    ui->powerEdit->setText(QString::number(_extruder->watts()));
}

void EditPrinterExtruderPage::apply()
{
    Position position;
    position.setX(ui->xOffsetEdit->text().toFloat());
    position.setY(ui->yOffsetEdit->text().toFloat());
    position.setZ(ui->zOffsetEdit->text().toFloat());

    _extruder->setOffset(position);
    _extruder->setWatts(ui->powerEdit->text().toFloat());
}
