#include "fileeditor.h"
#include "ui_fileeditor.h"

#include "flo/settings.h"

using namespace QSourceHighlite;

FileEditor::FileEditor(QKlipperInstance *instance, QWidget *parent)
    : Dialog(parent)
    , ui(new Ui::FileEditor)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::Popup);

    ui->textEdit->setFontPointSize(11);

    m_highlighter = new QSourceHighliter(ui->textEdit->document());
    m_highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
    m_highlighter->setTheme(QSourceHighliter::System);

    m_instance = instance;

    m_resetButton = new QIconButton(this);
    m_resetButton->setFixedSize(250,50);
    m_resetButton->setText("Reset");
    m_resetButton->setIcon(Settings::getThemeIcon("add"));
    ui->buttonLayout->addWidget(m_resetButton);

    m_saveButton = new QIconButton(this);
    m_saveButton->setFixedSize(250,50);
    m_saveButton->setText("Save");
    m_saveButton->setIcon(Settings::getThemeIcon("save"));
    ui->buttonLayout->addWidget(m_saveButton);

    m_saveAndRestartButton = new QIconButton(this);
    m_saveAndRestartButton->setFixedSize(250,50);
    m_saveAndRestartButton->setText("Save and Restart");
    m_saveAndRestartButton->setIcon(Settings::getThemeIcon("multiply"));
    ui->buttonLayout->addWidget(m_saveAndRestartButton);

    ui->buttonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));

    m_closeButton = new QIconButton(this);
    m_closeButton->setFixedSize(250,50);
    m_closeButton->setText("Close");
    m_closeButton->setIcon(Settings::getThemeIcon("multiply"));
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

QKlipperFile *FileEditor::file() const
{
    return m_file;
}

void FileEditor::setFile(QKlipperFile *file)
{
    m_file = file;
    setWindowTitle(m_file->filename());

    if(m_file->fileType() == QKlipperFile::GCode)
    {
        m_highlighter->setCurrentLanguage(QSourceHighliter::CodeGCode);
        m_saveAndRestartButton->setHidden(true);
    }
    else if(m_file->fileType() == QKlipperFile::Config)
    {
        m_highlighter->setCurrentLanguage(QSourceHighliter::CodeINI);
        m_saveAndRestartButton->setHidden(false);
    }

    QString fileContents = m_instance->console()->serverFileDownload(m_file);
    ui->textEdit->setText(fileContents);
}

void FileEditor::resetButtonClicked()
{
    showLoadingScreen();

    QString fileContents = m_instance->console()->serverFileDownload(m_file);
    ui->textEdit->setText(fileContents);

    hideLoadingScreen();
}

void FileEditor::saveAndRestartButtonClicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();
    QKlipperError error;
    m_instance->console()->serverFileUpload(m_file->root(), m_file->path(), m_file->filename(), fileContents, &error);

    if(error.type() == QKlipperError::NoError)
    {
        done(SaveAndRestart);
    }
}

void FileEditor::saveAndCloseButtonClicked()
{
    QByteArray fileContents = ui->textEdit->toPlainText().toUtf8();

    QKlipperError error;
    m_instance->console()->serverFileUpload(m_file->root(), m_file->path(), m_file->filename(), fileContents, &error);

    if(error.type() == QKlipperError::NoError)
    {
        done(Save);
    }
}

void FileEditor::closeButtonClicked()
{
    done(Rejected);
}
