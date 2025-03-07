#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QDialog>

#include "3rdparty/QSourceHighlite/qsourcehighliter.h"
#include <QKlipper/qklipper.h>

#include "ui/QIconButton/qiconbutton.h"
#include "common/dialog/dialog.h"

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
        Save = 3,
        Error = 4
    };

    explicit FileEditor(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~FileEditor();

    QKlipperFile *file() const;
    void setFile(QKlipperFile *file);

private slots:
    void resetButtonClicked();
    void saveAndRestartButtonClicked();
    void saveAndCloseButtonClicked();
    void closeButtonClicked();

private:
    Ui::FileEditor *ui;

    QSourceHighlite::QSourceHighliter *m_highlighter;
    QKlipperFile *m_file;
    QKlipperInstance *m_instance = nullptr;

    QIconButton *m_resetButton = nullptr;
    QIconButton *m_saveButton = nullptr;
    QIconButton *m_saveAndRestartButton = nullptr;
    QIconButton *m_closeButton = nullptr;
};

#endif // FILEEDITOR_H
