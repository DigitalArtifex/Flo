#ifndef ADDPRINTERWIZARD_H
#define ADDPRINTERWIZARD_H

#include <QWizard>
#include <QPixmap>
#include <QRegularExpression>
#include <QMouseEvent>
#include <QFileDialog>

#include "addprinterpage.h"
#include "addextruderspage.h"
#include "addbedpage.h"
#include "validateprinterpage.h"

#include "../../../types/printer.h"

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
    AddPrinterPage *m_addPage = nullptr;
    AddExtrudersPage *m_extruderPage = nullptr;
    AddBedPage *m_bedPage = nullptr;
    ValidatePrinterPage *m_validatePage = nullptr;
    PrinterDefinition m_definition;
    Printer *m_printer = nullptr;
};

#endif // ADDPRINTERWIZARD_H
