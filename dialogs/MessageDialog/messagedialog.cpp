#include "messagedialog.h"
#include "flo/settings.h"

MessageDialog::MessageDialog(QWidget *parent)
    : Dialog{parent}
{
    setupUi();

    setStyleSheet(Settings::currentTheme());
}

MessageDialog::~MessageDialog()
{
    if(m_acceptButton)
    {
        m_buttonLayout->removeWidget(m_acceptButton);
        delete m_acceptButton;
    }

    if(m_rejectButton)
    {
        m_buttonLayout->removeWidget(m_rejectButton);
        delete m_rejectButton;
    }
}

QIcon MessageDialog::icon() const
{
    return m_icon;
}

void MessageDialog::setIcon(const QIcon &icon)
{
    m_icon = icon;
    m_iconLabel->setPixmap(icon.pixmap(m_iconLabel->size()));
}

QString MessageDialog::text() const
{
    return m_text;
}

void MessageDialog::setText(const QString &text)
{
    m_text = text;
    m_textLabel->setText(QString("<h1>%1</h1>").arg(text));
}

void MessageDialog::setRejectEnabled(bool enabled)
{
    if(enabled)
    {
        if(m_acceptButton)
            m_buttonLayout->removeWidget(m_acceptButton);

        m_rejectButton = new QIconButton(this);
        m_rejectButton->setText("Cancel");
        m_rejectButton->setIcon(Settings::getThemeIcon("cancel"));
        m_rejectButton->setFixedHeight(50);
        m_rejectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_centralLayout->addWidget(m_rejectButton);

        connect(m_rejectButton, SIGNAL(clicked()), this, SLOT(reject()));

        if(m_acceptButton)
            m_buttonLayout->addWidget(m_acceptButton);
    }
    else if(m_rejectButton)
    {
        m_buttonLayout->removeWidget(m_rejectButton);
        delete m_rejectButton;
        m_rejectButton = nullptr;
    }
}

void MessageDialog::setupUi()
{
    m_centralLayout = new QVBoxLayout(this);
    setLayout(m_centralLayout);

    m_textLabel = new QLabel(this);
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_centralLayout->addWidget(m_textLabel);
    m_centralLayout->addItem(new QSpacerItem(0,20, QSizePolicy::Expanding, QSizePolicy::Fixed));

    m_informationLayout = new QHBoxLayout(this);
    m_centralLayout->addLayout(m_informationLayout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(50,50);
    m_iconLabel->setProperty("class", "MessageDialogIcon");
    m_informationLayout->addWidget(m_iconLabel);

    m_informativeTextLabel = new QLabel(this);
    m_informativeTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_informationLayout->addWidget(m_informativeTextLabel);

    m_centralLayout->addItem(new QSpacerItem(0,20, QSizePolicy::Expanding, QSizePolicy::Expanding));

    m_buttonLayout = new QHBoxLayout(this);
    m_centralLayout->addLayout(m_buttonLayout);

    m_acceptButton = new QIconButton(this);
    m_acceptButton->setText("Okay");
    m_acceptButton->setIcon(Settings::getThemeIcon("accept"));
    m_acceptButton->setFixedHeight(50);
    m_acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_buttonLayout->addWidget(m_acceptButton);

    connect(m_acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
}

QString MessageDialog::informativeText() const
{
    return m_informativeText;
}

void MessageDialog::setInformativeText(const QString &informativeText)
{
    m_informativeText = informativeText;
    m_informativeTextLabel->setText(m_informativeText);
}
