#ifndef EDITPRINTEREXTRUDERPAGE_H
#define EDITPRINTEREXTRUDERPAGE_H

#include <QFrame>

#include "../../../types/printer.h"

namespace Ui {
class EditPrinterExtruderPage;
}

class EditPrinterExtruderPage : public QFrame
{
    Q_OBJECT

public:
    explicit EditPrinterExtruderPage(QWidget *parent = nullptr);
    ~EditPrinterExtruderPage();

    Extruder *extruder() const;
    void setExtruder(Extruder *extruder);

    void apply();

private:
    Ui::EditPrinterExtruderPage *ui;

    Extruder *_extruder = nullptr;
};

#endif // EDITPRINTEREXTRUDERPAGE_H
