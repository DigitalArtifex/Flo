#include "emptyprinterwebcamframe.h"

EmptyPrinterWebcamFrame::EmptyPrinterWebcamFrame(QWidget *parent) :
    QFrame(parent)
{
    setupUi();
    setupIcons();
}

void EmptyPrinterWebcamFrame::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    setupIcons();
}

void EmptyPrinterWebcamFrame::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    setLayout(m_layout);

    m_topSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addItem(m_topSpacer,0,0);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(32,32);
    m_layout->addWidget(m_iconLabel, 1, 0, Qt::AlignCenter);

    m_label = new QLabel(this);
    m_label->setText(QString("No connection"));
    m_label->setAlignment(Qt::AlignHCenter);
    m_layout->addWidget(m_label, 2, 0, Qt::AlignCenter);

    m_bottomSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addItem(m_bottomSpacer,3,0);
}

void EmptyPrinterWebcamFrame::setupIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("no-video").pixmap(28,28);
    m_iconLabel->setPixmap(pixmap);
}
