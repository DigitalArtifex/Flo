#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QMainWindow>
#include "../../../../QSourceHighlite/qsourcehighliter.h"
#include "../../../../types/klipperfile.h"
#include "../../../../types/printer.h"

namespace Ui {
class FileEditor;
}

class FileEditor : public QMainWindow
{
    Q_OBJECT

signals:
    void save();
    void saveAndRestart();
    void reset();

public:
    explicit FileEditor(Printer *printer, QWidget *parent = nullptr);
    ~FileEditor();

    KlipperFile file() const;
    void setFile(const KlipperFile &file);

private slots:
    void on_resetButton_clicked();

    void on_saveAndRestartButton_clicked();

    void on_saveAndCloseButton_clicked();

private:
    Ui::FileEditor *ui;

    QSourceHighlite::QSourceHighliter *_highlighter;
    KlipperFile _file;
    Printer *_printer = nullptr;
};

#endif // FILEEDITOR_H
