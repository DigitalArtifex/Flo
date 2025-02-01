#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent)
    : Dialog{parent}
{
    setupUi();
}

void ProgressDialog::addInfoText(const QString &text)
{
    m_infoEdit->append(text);
}

void ProgressDialog::setValueText(const QString &text)
{
    m_progressBar->setFormat(text + " %p%");
}

void ProgressDialog::setValueValue(const qreal &progress)
{
    m_progressBar->setValue(progress);
}

void ProgressDialog::setValueMinimum(const qreal &value)
{
    m_progressBar->setMinimum(value);
}

void ProgressDialog::setValueMaximum(const qreal &value)
{
    m_progressBar->setMaximum(value);
}

void ProgressDialog::setupUi()
{
    m_centralLayout = new QGridLayout(this);
    setLayout(m_centralLayout);

    m_infoEdit = new QTextEdit(this);
    m_infoEdit->setTextInteractionFlags(Qt::NoTextInteraction);
    m_centralLayout->addWidget(m_infoEdit);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setFixedHeight(35);
    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(100);
    m_progressBar->setValue(0);
    m_centralLayout->addWidget(m_progressBar);
}
