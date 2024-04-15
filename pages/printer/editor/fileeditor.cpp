#include "fileeditor.h"
#include "ui_fileeditor.h"

using namespace QSourceHighlite;

FileEditor::FileEditor(Printer *printer, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FileEditor)
{
    ui->setupUi(this);

    _highlighter = new QSourceHighliter(ui->textEdit->document());
    _highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
    _highlighter->setTheme(QSourceHighliter::System);

    _printer = printer;
    showMaximized();
}

FileEditor::~FileEditor()
{
    delete ui;
}

KlipperFile FileEditor::file() const
{
    return _file;
}

void FileEditor::setFile(const KlipperFile &file)
{
    _file = file;
    setWindowTitle(QString(file.name));

    if(_file.type == KlipperFile::GCode)
    {
        _highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
        ui->saveAndRestartButton->setHidden(true);
    }
    else if(_file.type == KlipperFile::Config)
    {
        _highlighter->setCurrentLanguage(QSourceHighliter::CodeINI);
        ui->saveAndRestartButton->setHidden(false);
    }

    QString fileContents = _printer->console()->downloadFile(_file);
    ui->textEdit->setText(fileContents);
}

void FileEditor::on_resetButton_clicked()
{
    QString fileContents = _printer->console()->downloadFile(_file);
    ui->textEdit->setText(fileContents);
}

void FileEditor::on_saveAndRestartButton_clicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();

    if(_printer->console()->uploadFile(_file.root, _file.path, _file.name, fileContents))
    {
        _printer->console()->restartKlipper();
        close();
    }
}

void FileEditor::on_saveAndCloseButton_clicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();

    if(_printer->console()->uploadFile(_file.root, _file.path, _file.name, fileContents))
    {
        close();
    }
}
