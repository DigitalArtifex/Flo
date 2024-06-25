#ifndef VALIDATEPRINTERPAGE_H
#define VALIDATEPRINTERPAGE_H

#include <QWizardPage>
#include <QDir>
#include <QFile>

#include "../../../types/printer.h"

namespace Ui {
class ValidatePrinterPage;
}

class ValidatePrinterPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ValidatePrinterPage(QWidget *parent = nullptr);
    ~ValidatePrinterPage();

    bool validatePage();
    void setDefinition(PrinterDefinition definition);
    PrinterDefinition definition();

private slots:
    void on_klipperConnected(Printer *printer);
    void on_printerOnline(Printer *printer);
    void on_moonrakerConnected(Printer *printer);

private:
    Ui::ValidatePrinterPage *ui;
    bool m_validated = false;
    bool m_printerOnline = false;
    Printer *m_printer = nullptr;
    PrinterDefinition m_definition;
};

#endif // VALIDATEPRINTERPAGE_H
