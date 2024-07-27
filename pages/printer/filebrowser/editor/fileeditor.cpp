#include "fileeditor.h"
#include "ui_fileeditor.h"

using namespace QSourceHighlite;

FileEditor::FileEditor(Printer *printer, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileEditor)
{
    ui->setupUi(this);

    m_highlighter = new QSourceHighliter(ui->textEdit->document());
    m_highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
    m_highlighter->setTheme(QSourceHighliter::System);

    m_printer = printer;
    showMaximized();
}

FileEditor::~FileEditor()
{
    delete ui;
}

KlipperFile FileEditor::file() const
{
    return m_file;
}

void FileEditor::setFile(const KlipperFile &file)
{
    m_file = file;
    setWindowTitle(QString(file.name));

    if(m_file.type == KlipperFile::GCode)
    {
        m_highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
        ui->saveAndRestartButton->setHidden(true);
    }
    else if(m_file.type == KlipperFile::Config)
    {
        m_highlighter->setCurrentLanguage(QSourceHighliter::CodeINI);
        ui->saveAndRestartButton->setHidden(false);
    }

    QString fileContents = m_printer->console()->downloadFile(m_file);
    ui->textEdit->setText(fileContents);
}

void FileEditor::setStyleSheet(QString &styleSheet)
{
    QDialog::setStyleSheet(styleSheet);
}

void FileEditor::on_resetButton_clicked()
{
    QString fileContents = m_printer->console()->downloadFile(m_file);
    ui->textEdit->setText(fileContents);
}

void FileEditor::on_saveAndRestartButton_clicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();

    if(m_printer->console()->uploadFile(m_file.root, m_file.path, m_file.name, fileContents))
    {
        m_printer->console()->restartKlipper();
        close();
    }
}

void FileEditor::on_saveAndCloseButton_clicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();

    if(m_printer->console()->uploadFile(m_file.root, m_file.path, m_file.name, fileContents))
    {
        close();
    }
}
