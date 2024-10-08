#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QDialog>

#include "QSourceHighlite/qsourcehighliter.h"
#include "types/klipperfile.h"
#include "types/printer.h"

#include "ui/QIconButton/qiconbutton.h"
#include "ui/common/dialog/dialog.h"

namespace Ui {
class FileEditor;
}

class FileEditor : public Dialog
{
    Q_OBJECT

signals:
    void save();
    void saveAndRestart();
    void reset();

public:

    enum ReturnCodes
    {
        SaveAndRestart = 2,
        Save = 3
    };

    explicit FileEditor(Printer *printer, QWidget *parent = nullptr);
    ~FileEditor();

    KlipperFile file() const;
    void setFile(const KlipperFile &file);

private slots:
    void resetButtonClicked();
    void saveAndRestartButtonClicked();
    void saveAndCloseButtonClicked();
    void closeButtonClicked();

private:
    Ui::FileEditor *ui;

    QSourceHighlite::QSourceHighliter *m_highlighter;
    KlipperFile m_file;
    Printer *m_printer = nullptr;

    QIconButton *m_resetButton = nullptr;
    QIconButton *m_saveButton = nullptr;
    QIconButton *m_saveAndRestartButton = nullptr;
    QIconButton *m_closeButton = nullptr;
};

#endif // FILEEDITOR_H
