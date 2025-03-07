#ifndef EDITPRINTERDIALOG_H
#define EDITPRINTERDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QFileDialog>
#include <QColorDialog>

#include <QKlipper/qklipper.h>
#include <flo/settings.h>

#include "qmoonrakervalidator.h"
#include "ui/QIconButton/qiconbutton.h"

namespace Ui {
class EditPrinterDialog;
}

class EditPrinterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPrinterDialog(QWidget *parent = nullptr);
    ~EditPrinterDialog();

    QKlipperInstance *printer() const;
    void setPrinter(QKlipperInstance *printer, bool newPrinter = false);

    void reset();
    void clear();
    void apply();

private slots:
    void on_extruderCountSpinBox_valueChanged(int arg1);
    void on_printerInstanceLocationEdit_textChanged(QString text);
    void on_printerBrowseFilesButton_clicked();
    void on_printerKeyEdit_textChanged(const QString &arg1);
    void on_colorEdit_textChanged(const QString &arg1);

    void on_colorPickerButton_clicked();

    void on_printerNameEdit_textChanged(const QString &arg1);

    void onResetButtonClicked();
    void onApplyButtonClicked();
    void onCancelButtonClicked();

    void on_addressLineEdit_textChanged(const QString &arg1);

    void on_heatedBedCheckbox_toggled(bool checked);

    void on_heatedChamberCheckBox_toggled(bool checked);

    void on_EditPrinterDialog_windowTitleChanged(const QString &title);

private:
    Ui::EditPrinterDialog *ui;

    bool m_newPrinter = true;
    bool m_remoteConnection = false;

    int m_extruderCount = 0;

    QKlipperInstance *m_instance = nullptr;

    QIconButton *m_resetButton = nullptr;
    QIconButton *m_applyButton = nullptr;
    QIconButton *m_cancelButton = nullptr;
    QSpacerItem *m_buttonBoxSpacer = nullptr;

    QRegularExpression m_httpExpression = QRegularExpression("^\\s*(http|https)\\:\\/\\/");
};

#endif // EDITPRINTERDIALOG_H
