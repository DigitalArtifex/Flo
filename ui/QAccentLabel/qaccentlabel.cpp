#include "qaccentlabel.h"
#include "ui_qaccentlabel.h"

QAccentLabel::QAccentLabel(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::QAccentLabel)
{
    ui->setupUi(this);
}

QAccentLabel::~QAccentLabel()
{
    delete ui;
}

QColor QAccentLabel::accentColor() const
{
    return m_accentColor;
}

void QAccentLabel::setAccentColor(const QColor &accentColor)
{
    if (m_accentColor == accentColor)
        return;

    m_accentColor = accentColor;

    QString style = QString("background-color: %1;").arg(m_accentColor.name());
    ui->accentLabel->setStyleSheet(style);

    emit accentColorChanged();
}

QString QAccentLabel::text() const
{
    return ui->textLabel->text();
}

void QAccentLabel::setText(const QString &text)
{
    if (ui->textLabel->text() == text)
        return;

    ui->textLabel->setText(text);

    emit textChanged();
}

qint8 QAccentLabel::accentWidth() const
{
    return m_accentWidth;
}

void QAccentLabel::setAccentWidth(qint8 accentWidth)
{
    if (m_accentWidth == accentWidth)
        return;
    m_accentWidth = accentWidth;

    ui->accentLabel->setFixedWidth(m_accentWidth);

    emit accentWidthChanged();
}
