#ifndef ADDPRINTERPAGE_H
#define ADDPRINTERPAGE_H

#include <QWizardPage>
#include <QRegularExpression>
#include <QFileDialog>
#include <QUuid>
#include <QColorDialog>

#include "../../../types/printer.h"

namespace Ui {
class AddPrinterPage;
}

class AddPrinterPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit AddPrinterPage(QWidget *parent = nullptr);
    ~AddPrinterPage();

    bool validatePage();

    PrinterDefinition definition();

private slots:
    void on_instanceEdit_textChanged(const QString &arg1);

    void on_browseFilesButton_clicked();

    void on_colorPickerButton_clicked();

    void on_colorEdit_textChanged(const QString &arg1);

private:
    Ui::AddPrinterPage *ui;
    QString hexCodes = QString("0123456789ABCDEF");
};

#endif // ADDPRINTERPAGE_H
