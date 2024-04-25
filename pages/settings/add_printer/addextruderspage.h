#ifndef ADDEXTRUDERSPAGE_H
#define ADDEXTRUDERSPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>

#include "../../../types/printer.h"

namespace Ui {
class AddExtrudersPage;
}

class AddExtrudersPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit AddExtrudersPage(QWidget *parent = nullptr);
    ~AddExtrudersPage();

    void reset();
    void apply();

    PrinterDefinition definition() const;
    void setDefinition(PrinterDefinition definition);

    virtual bool validate() const;

private slots:
    void on_extruderCountSpinBox_valueChanged(int arg1);

private:
    Ui::AddExtrudersPage *ui;

    int _extruderCount = 0;

    Printer *_printer = nullptr;
    PrinterDefinition _definition;
};

#endif // ADDEXTRUDERSPAGE_H
