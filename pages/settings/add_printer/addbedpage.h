#ifndef ADDBEDPAGE_H
#define ADDBEDPAGE_H

#include <QWizardPage>

#include "../../../types/printerdefinition.h"

namespace Ui {
class AddBedPage;
}

class AddBedPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit AddBedPage(QWidget *parent = nullptr);
    ~AddBedPage();

    void reset();
    void apply();

    PrinterDefinition definition() const;
    void setDefinition(PrinterDefinition definition);

    virtual bool validate();

private slots:
    void on_heatedBedCheckbox_stateChanged(int arg1);

private:
    Ui::AddBedPage *ui;

    PrinterDefinition m_definition;
};

#endif // ADDBEDPAGE_H
