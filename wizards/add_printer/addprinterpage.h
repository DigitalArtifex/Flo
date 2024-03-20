#ifndef ADDPRINTERPAGE_H
#define ADDPRINTERPAGE_H

#include <QWizardPage>
#include <QRegularExpression>
#include <QFileDialog>
#include <QUuid>

#include "../../types/printer.h"

namespace Ui {
class AddPrinterPage;
}

class AddPrinterPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit AddPrinterPage(QWidget *parent = nullptr);
    ~AddPrinterPage();

    bool isComplete();
    bool validatePage();

    PrinterDefinition definition();

private slots:
    void on_instanceEdit_textChanged(const QString &arg1);

    void on_browseFilesButton_clicked();

private:
    Ui::AddPrinterPage *ui;
};

#endif // ADDPRINTERPAGE_H
