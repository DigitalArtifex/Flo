#ifndef ADDPRINTERWIZARD_H
#define ADDPRINTERWIZARD_H

#include <QWizard>
#include <QPixmap>
#include <QRegularExpression>
#include <QMouseEvent>
#include <QFileDialog>

#include "addprinterpage.h"
#include "validateprinterpage.h"

namespace Ui {
class AddPrinterWizard;
}

class AddPrinterWizard : public QWizard
{
    Q_OBJECT

public:
    explicit AddPrinterWizard(QWidget *parent = nullptr);
    ~AddPrinterWizard();

    virtual bool validateCurrentPage();

    PrinterDefinition definition();

public slots:
    virtual void next();

private:
    Ui::AddPrinterWizard *ui;
    AddPrinterPage *_addPage = nullptr;
    ValidatePrinterPage *_validatePage = nullptr;
    PrinterDefinition _definition;
};

#endif // ADDPRINTERWIZARD_H
