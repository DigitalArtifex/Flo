#include "messagedialog.h"
#include "system/settings.h"

MessageDialog::MessageDialog(QWidget *parent)
    : Dialog{parent}
{
    setupUi();

    setStyleSheet(Settings::currentTheme());
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
    m_textLabel->setText(text);
}

void MessageDialog::setupUi()
{
    m_centralLayout = new QVBoxLayout(this);
    setLayout(m_centralLayout);

    m_informationLayout = new QHBoxLayout(this);
    m_centralLayout->addLayout(m_informationLayout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(50,50);
    m_iconLabel->setProperty("class", "MessageDialogIcon");
    m_informationLayout->addWidget(m_iconLabel);

    m_textLabel = new QLabel(this);
    m_iconLabel->setProperty("class", "MessageDialogText");
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_informationLayout->addWidget(m_textLabel);

    m_centralLayout->addItem(new QSpacerItem(0,20));

    m_acceptButton = new QIconButton(this);
    m_acceptButton->setText("Okay");
    m_acceptButton->setIcon(Settings::getThemeIcon("accept"));
    m_acceptButton->setMinimumSize(200,50);
    m_acceptButton->setFixedHeight(50);
    m_acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_centralLayout->addWidget(m_acceptButton);

    connect(m_acceptButton, SIGNAL(clicked()), this, SLOT(acceptButtonClicked()));
}

void MessageDialog::acceptButtonClicked()
{
    done(QDialog::Accepted);
}
