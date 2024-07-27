#include "newfolderdialog.h"

#include "system/settings.h"

NewFolderDialog::NewFolderDialog(QWidget *parent)
    : Dialog{parent}
{
    setupUi();
}

NewFolderDialog::~NewFolderDialog()
{
    if(m_lineEdit)
    {
        if(m_layout)
            m_layout->removeWidget(m_lineEdit);

        delete m_lineEdit;
    }

    if(m_acceptButton)
    {
        if(m_layout)
            m_layout->removeWidget(m_acceptButton);

        delete m_acceptButton;
    }

    if(m_cancelButton)
    {
        if(m_layout)
            m_layout->removeWidget(m_cancelButton);

        delete m_cancelButton;
    }

    if(m_layout)
        delete m_layout;
}

void NewFolderDialog::setupUi()
{
    m_layout = new QGridLayout(this);
    setLayout(m_layout);

    m_textLabel = new QLabel(this);
    m_textLabel->setText("New Folder\n");
    m_textLabel->setProperty("class", QString("DialogHeading"));
    m_layout->addWidget(m_textLabel, 0, 0, 1, 2);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setFixedSize(420, 35);
    m_layout->addWidget(m_lineEdit, 1, 0, 1, 2);

    QPixmap pixmap = Settings::getThemeIcon("cancel-icon").pixmap(22,22);

    m_cancelButton = new QIconButton(this);
    m_cancelButton->setPixmap(pixmap);
    m_cancelButton->setText(QString("Cancel"));
    m_cancelButton->setFixedHeight(50);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_layout->addWidget(m_cancelButton, 2, 0, 1, 1);

    pixmap = Settings::getThemeIcon("accept-icon").pixmap(22,22);

    m_acceptButton = new QIconButton(this);
    m_acceptButton->setPixmap(pixmap);
    m_acceptButton->setText(QString("Accept"));
    m_acceptButton->setFixedHeight(50);
    m_acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_layout->addWidget(m_acceptButton, 2, 1, 1, 1);

    connect(m_acceptButton, SIGNAL(clicked()), this, SLOT(acceptButtonClickEvent()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClickEvent()));

    style()->polish(this);
}

void NewFolderDialog::acceptButtonClickEvent()
{
    done(Accepted);
    emit accepted(m_lineEdit->text());
}

void NewFolderDialog::cancelButtonClickEvent()
{
    done(Rejected);
}
