#ifndef EDITPRINTERWIZARD_H
#define EDITPRINTERWIZARD_H

#include <QWizard>

namespace Ui {
class EditPrinterWizard;
}

class EditPrinterWizard : public QWizard
{
    Q_OBJECT

public:
    explicit EditPrinterWizard(QWidget *parent = nullptr);
    ~EditPrinterWizard();

private:
    Ui::EditPrinterWizard *ui;
};

#endif // EDITPRINTERWIZARD_H
