#ifndef EDITPRINTERDIALOG_H
#define EDITPRINTERDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QFileDialog>

#include "../../../types/printer.h"

#include "qmoonrakervalidator.h"

namespace Ui {
class EditPrinterDialog;
}

class EditPrinterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPrinterDialog(QWidget *parent = nullptr);
    ~EditPrinterDialog();

    Printer *printer() const;
    void setPrinter(Printer *printer);

    void reset();
    void clear();
    void apply();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_extruderCountSpinBox_valueChanged(int arg1);
    void on_printerInstanceLocationEdit_textChanged(QString text);

    void on_printerBrowseFilesButton_clicked();

    void on_printerKeyEdit_textChanged(const QString &arg1);

private:
    Ui::EditPrinterDialog *ui;

    int _extruderCount = 0;

    Printer *_printer = nullptr;

    QRegularExpression _httpExpression = QRegularExpression("^\\s*(http|https)\\:\\/\\/");
};

#endif // EDITPRINTERDIALOG_H