#include "qnumberedit.h"
#include <QStyle>
#include <QStyleHintReturn>
#include <QStyleOption>
#include <QStylePainter>
#include "qpainter.h"
#include "ui_qnumberedit.h"

QNumberEdit::QNumberEdit(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::QNumberEdit)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QDoubleValidator(0.00, 230.00, 2, this));
    ui->lineEdit->setText(QString::number(m_value));
    setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit->installEventFilter(this);
    ui->spinUpButton->installEventFilter(this);
    ui->spinDownButton->installEventFilter(this);

    m_focusObjects.append(ui->lineEdit);
    m_focusObjects.append(ui->spinUpButton);
    m_focusObjects.append(ui->spinDownButton);

    ui->spinUpButton->setProperty("class", QStringList {"QNumberUpButton"} + ui->spinUpButton->property("class").toStringList());
    ui->spinDownButton->setProperty("class", QStringList {"QNumberDownButton"} + ui->spinDownButton->property("class").toStringList());
    ui->buttonBox->setProperty("class", QStringList {"QNumberButtonBox"} + ui->buttonBox->property("class").toStringList());
}

QNumberEdit::~QNumberEdit()
{
    delete ui;
}

void QNumberEdit::on_lineEdit_textChanged(const QString &arg1)
{
    QFontMetrics metrics = ui->lineEdit->fontMetrics();
    int width = metrics.boundingRect(arg1 + "_").width();

    if(width <= metrics.boundingRect("_").width())
    {
        ui->lineEdit->setText(QString::number(0));
        return;
    }

    if(arg1.length() > 1 && arg1.startsWith('0'))
    {
        QString value = arg1;
        value.remove(0,1);

        ui->lineEdit->setText(value);
        return;
    }

    bool okay = false;
    qreal value = arg1.toDouble(&okay);

    if(!okay)
    {
        ui->lineEdit->setText(QString::number(0));
        return;
    }

    if(value < m_minimum && !qFuzzyCompare(value, m_minimum))
    {
        ui->lineEdit->setText(QString::number(m_minimum));
        return;
    }

    if(value > m_maximum && !qFuzzyCompare(value, m_maximum))
    {
        ui->lineEdit->setText(QString::number(m_maximum));
        return;
    }

    ui->lineEdit->setFixedWidth(width);
    setValuePrivate(value);
}

void QNumberEdit::setValuePrivate(qreal value)
{
    if (qFuzzyCompare(m_value, value))
        return;
    m_value = value;
    emit valueChanged(m_value);
}

void QNumberEdit::paintEvent(QPaintEvent *event)
{
    QStyleOptionFrame option;
    option.initFrom(this);

    QStylePainter painter(this);

    if(m_childFocused)
        option.state |= QStyle::State_HasFocus;

    if(isEnabled())
    {
        QRect backgroundRect = option.rect;
        backgroundRect.adjust(frameWidth(), frameWidth(), frameWidth() * -1, frameWidth() * -1);
        painter.fillRect(backgroundRect, palette().color(QPalette::Base));
        option.state |= QStyle::State_Enabled;
    }

    painter.drawPrimitive(QStyle::PE_FrameLineEdit, option);
}

void QNumberEdit::focusInEvent(QFocusEvent *event)
{
    QFrame::focusInEvent(event);
    ui->lineEdit->setFocus();
}

void QNumberEdit::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::EnabledChange)
    {
        ui->prefixLabel->setEnabled(isEnabled());
        ui->suffixLabel->setEnabled(isEnabled());
        ui->spinDownButton->setEnabled(isEnabled());
        ui->spinUpButton->setEnabled(isEnabled());
        update();
    }
}

void QNumberEdit::createStepTimer()
{
    m_stepTimer = new QTimer(this);
    m_stepTimer->setInterval(150);

    connect(m_stepTimer, SIGNAL(timeout()), this, SLOT(onStepTimerTimeout()));

    m_buttonHoldTimer = new QTimer(this);
    m_buttonHoldTimer->setInterval(250);

    connect(m_buttonHoldTimer, SIGNAL(timeout()), this, SLOT(onButtonHoldTimerTimeout()));
    m_buttonHoldTimer->start();
}

void QNumberEdit::deleteStepTimer()
{
    if(m_buttonHoldTimer)
    {
        m_buttonHoldTimer->stop();
        delete m_buttonHoldTimer;
        m_buttonHoldTimer = nullptr;
    }
    if(m_stepTimer)
    {
        m_stepTimer->stop();
        delete m_stepTimer;
        m_stepTimer = nullptr;
    }
}

bool QNumberEdit::eventFilter(QObject *object, QEvent *event)
{
    if(m_focusObjects.contains(object) && event->type() == QEvent::FocusIn)
    {
        m_childFocused = true;
        update();
    }

    else if(m_focusObjects.contains(object) && event->type() == QEvent::FocusOut)
    {
        m_childFocused = false;
        update();
    }

    return false;
}

qreal QNumberEdit::step() const
{
    return m_step;
}

void QNumberEdit::setStep(qreal step)
{
    if (qFuzzyCompare(m_step, step))
        return;
    m_step = step;
    emit stepChanged();
}

QString QNumberEdit::suffix() const
{
    return m_suffix;
}

void QNumberEdit::setSuffix(const QString &suffix)
{
    if (m_suffix == suffix)
        return;
    m_suffix = suffix;
    ui->suffixLabel->setText(m_suffix);
    emit suffixChanged();
}

QString QNumberEdit::prefix() const
{
    return m_prefix;
}

void QNumberEdit::setPrefix(const QString &prefix)
{
    if (m_prefix == prefix)
        return;
    m_prefix = prefix;
    ui->prefixLabel->setText(m_prefix);
    emit prefixChanged();
}

qreal QNumberEdit::maximum() const
{
    return m_maximum;
}

void QNumberEdit::setMaximum(qreal maximum)
{
    if (qFuzzyCompare(m_maximum, maximum))
        return;
    m_maximum = maximum;
    emit maximumChanged();
}

qreal QNumberEdit::minimum() const
{
    return m_minimum;
}

void QNumberEdit::setMinimum(qreal minimum)
{
    if (qFuzzyCompare(m_minimum, minimum))
        return;
    m_minimum = minimum;
    emit minimumChanged();
}

qreal QNumberEdit::value() const
{
    return m_value;
}

void QNumberEdit::setValue(qreal value)
{
    if (qFuzzyCompare(m_value, value))
        return;

    ui->lineEdit->setText(QString::number(value));
}

void QNumberEdit::on_spinUpButton_pressed()
{
    setValue(m_value + m_step);
    m_stepIncrement = true;
    createStepTimer();
}

void QNumberEdit::onStepTimerTimeout()
{
    if(m_stepIncrement)
        setValue(m_value + m_step);
    else
        setValue(m_value - m_step);
}

void QNumberEdit::onButtonHoldTimerTimeout()
{
    if(!m_stepTimer)
        return;

    if(!m_stepTimer->isActive())
        m_stepTimer->start();
    else if(m_stepTimer->interval() > 10)
        m_stepTimer->setInterval(m_stepTimer->interval() - 10);
}

void QNumberEdit::on_spinDownButton_pressed()
{
    setValue(m_value - m_step);
    m_stepIncrement = false;
    createStepTimer();
}

void QNumberEdit::on_spinUpButton_released()
{
    deleteStepTimer();
}

void QNumberEdit::on_spinDownButton_released()
{
    deleteStepTimer();
}
