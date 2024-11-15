#include "printerusereditor.h"

#include "system/settings.h"

PrinterUserEditor::PrinterUserEditor(QWidget *parent)
    : Dialog{parent}
{
    setupUi();
}

PrinterUserEditor::~PrinterUserEditor()
{
    if(m_centralLayout)
        m_centralLayout->deleteLater();
}

QString PrinterUserEditor::password()
{
    if(m_userPasswordEdit->text() == m_userPasswordVerifyEdit->text())
        return m_userPasswordEdit->text();
    else
        return "";
}

QString PrinterUserEditor::username()
{
    return m_userNameEdit->text();
}

void PrinterUserEditor::setupUi()
{
    m_centralLayout = new QVBoxLayout(this);
    setLayout(m_centralLayout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(100,100);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setPixmap(Settings::getThemeIcon("user-icon").pixmap(100,100));
    m_centralLayout->addWidget(m_iconLabel);

    m_userNameEdit = new QLineEdit(this);
    m_userNameEdit->setPlaceholderText("Username");
    m_centralLayout->addWidget(m_userNameEdit);

    m_userPasswordEdit = new QLineEdit(this);
    m_userPasswordEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    //m_userPasswordEdit->setInputMask("*");
    m_userPasswordEdit->setPlaceholderText("Password");
    m_centralLayout->addWidget(m_userPasswordEdit);

    m_userPasswordVerifyEdit = new QLineEdit(this);
    //m_userPasswordVerifyEdit->setInputMask("*");
    m_userPasswordVerifyEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    m_userPasswordVerifyEdit->setPlaceholderText("Verify Password");
    m_centralLayout->addWidget(m_userPasswordVerifyEdit);

    m_centralLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_buttonLayout = new QHBoxLayout(this);
    m_centralLayout->addLayout(m_buttonLayout);

    m_cancelButton = new QIconButton(this);
    m_cancelButton->setText("Cancel");
    m_cancelButton->setIcon(Settings::getThemeIcon("cancel-icon"));
    m_cancelButton->setMinimumSize(200,50);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_buttonLayout->addWidget(m_cancelButton);

    m_buttonLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_acceptButton = new QIconButton(this);
    m_acceptButton->setText("Accept");
    m_acceptButton->setIcon(Settings::getThemeIcon("accept-icon"));
    m_acceptButton->setMinimumSize(200,50);
    m_acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_acceptButton->setEnabled(false);
    m_buttonLayout->addWidget(m_acceptButton);

    connect(m_acceptButton, SIGNAL(clicked()), this, SLOT(acceptButtonClicked()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(m_userPasswordEdit, SIGNAL(textChanged(QString)), this, SLOT(validatePasswords(QString)));
    connect(m_userPasswordVerifyEdit, SIGNAL(textChanged(QString)), this, SLOT(validatePasswords(QString)));
}

void PrinterUserEditor::acceptButtonClicked()
{
    done(QDialog::Accepted);
}

void PrinterUserEditor::cancelButtonClicked()
{
    done(QDialog::Rejected);
}

void PrinterUserEditor::validatePasswords(QString arg1)
{
    Q_UNUSED(arg1)

    if(m_userPasswordEdit->text() == m_userPasswordVerifyEdit->text())
        m_acceptButton->setEnabled(true);
    else
        m_acceptButton->setEnabled(false);
}
