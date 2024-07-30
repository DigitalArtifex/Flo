#include "fileeditor.h"
#include "ui_fileeditor.h"

#include "system/settings.h"

using namespace QSourceHighlite;

FileEditor::FileEditor(Printer *printer, QWidget *parent)
    : Dialog(parent)
    , ui(new Ui::FileEditor)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::Popup);

    m_highlighter = new QSourceHighliter(ui->textEdit->document());
    m_highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
    m_highlighter->setTheme(QSourceHighliter::System);

    m_printer = printer;

    QPixmap pixmap = Settings::getThemeIcon("add-icon").pixmap(28,28);
    m_resetButton = new QIconButton(this);
    m_resetButton->setFixedSize(250,50);
    m_resetButton->setText("Reset");
    m_resetButton->setPixmap(pixmap);
    ui->buttonLayout->addWidget(m_resetButton);

    pixmap = Settings::getThemeIcon("save-icon").pixmap(28,28);
    m_saveButton = new QIconButton(this);
    m_saveButton->setFixedSize(250,50);
    m_saveButton->setText("Save");
    m_saveButton->setPixmap(pixmap);
    ui->buttonLayout->addWidget(m_saveButton);

    pixmap = Settings::getThemeIcon("multiply-icon").pixmap(28,28);
    m_saveAndRestartButton = new QIconButton(this);
    m_saveAndRestartButton->setFixedSize(250,50);
    m_saveAndRestartButton->setText("Save and Restart");
    m_saveAndRestartButton->setPixmap(pixmap);
    ui->buttonLayout->addWidget(m_saveAndRestartButton);

    ui->buttonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));

    pixmap = Settings::getThemeIcon("multiply-icon").pixmap(28,28);
    m_closeButton = new QIconButton(this);
    m_closeButton->setFixedSize(250,50);
    m_closeButton->setText("Close");
    m_closeButton->setPixmap(pixmap);
    ui->buttonLayout->addWidget(m_closeButton);

    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    connect(m_resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
    connect(m_saveAndRestartButton, SIGNAL(clicked()), this, SLOT(saveAndRestartButtonClicked()));
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(saveAndCloseButtonClicked()));

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
        m_saveAndRestartButton->setHidden(true);
    }
    else if(m_file.type == KlipperFile::Config)
    {
        m_highlighter->setCurrentLanguage(QSourceHighliter::CodeINI);
        m_saveAndRestartButton->setHidden(false);
    }

    QString fileContents = m_printer->console()->downloadFile(m_file);
    ui->textEdit->setText(fileContents);
}

void FileEditor::resetButtonClicked()
{
    showLoadingScreen();

    QString fileContents = m_printer->console()->downloadFile(m_file);
    ui->textEdit->setText(fileContents);

    hideLoadingScreen();
}

void FileEditor::saveAndRestartButtonClicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();

    if(m_printer->console()->uploadFile(m_file.root, m_file.path, m_file.name, fileContents))
    {
        done(SaveAndRestart);
    }
}

void FileEditor::saveAndCloseButtonClicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();

    if(m_printer->console()->uploadFile(m_file.root, m_file.path, m_file.name, fileContents))
    {
        done(Save);
    }
}

void FileEditor::closeButtonClicked()
{
    done(Rejected);
}
