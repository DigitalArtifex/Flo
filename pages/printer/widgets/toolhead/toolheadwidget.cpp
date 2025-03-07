#include "toolheadwidget.h"
#include "ui_toolheadwidget.h"
#include "flo/settings.h"

ToolheadWidget::ToolheadWidget(QKlipperInstance *instance, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ToolheadWidget)
{
    ui->setupUi(this);
    setIcons();

    m_instance = instance;
    m_printer = instance->printer();

    QRegularExpression distanceExpression("\\d+\\.\\d+\\s*", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionValidator *distanceValidator = new QRegularExpressionValidator(distanceExpression);
    ui->posIncrementSelect->setValidator(distanceValidator);

    m_toolheadControlFrame = new ToolHeadControlFrame(instance->printer()->toolhead(), ui->controlContents);
    ui->controlContents->layout()->addWidget(m_toolheadControlFrame);

    ui->toolheadWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" ));
    ui->currentPositionFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
    ui->toolheadControlFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));

    ui->positionTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->positionTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->controlTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->controlTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    connect(m_printer->toolhead(), SIGNAL(positionChanged()), this, SLOT(onToolheadPositionChanged()));
    connect(m_printer->toolhead(), SIGNAL(destinationChanged()), this, SLOT(onToolHeadDestinationChanged()));
    connect(m_printer->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolHeadIsHomedChanged()));

    onToolHeadIsHomedChanged();
}

ToolheadWidget::~ToolheadWidget()
{
    delete ui;
}

void ToolheadWidget::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon(QString("location")).pixmap(18,18);
    ui->positionIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("control")).pixmap(18,18);
    ui->controlIconLabel->setPixmap(pixmap);

    ui->inputShaperButton->setIcon(
        Settings::getThemeIcon(
            "input-shaper",
            QColor::fromString(Settings::get("theme/icon-color-alt").toString())
            )
        );

    ui->inputShaperButton->setIconSize(QSize(50,50));

    ui->zOffsetWizardButton->setIcon(
        Settings::getThemeIcon(
            "zoffset",
            QColor::fromString(Settings::get("theme/icon-color-alt1").toString())
            )
        );

    ui->zOffsetWizardButton->setIconSize(QSize(50,50));
}

void ToolheadWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();

    QFrame::changeEvent(event);
}

void ToolheadWidget::on_posIncrementSelect_currentTextChanged(const QString &arg1)
{
    QString number;

    if(arg1.contains(m_number_expression))
    {
        QRegularExpressionMatch match = m_number_expression.globalMatch(arg1).next();
        number = match.captured();
    }

    int pos = number.length();

    if(ui->posIncrementSelect->hasFocus())
    {
        ui->posIncrementSelect->setCurrentText(number + QString("mm"));
        ui->posIncrementSelect->lineEdit()->setCursorPosition(pos);
    }
    else
        ui->posIncrementSelect->setCurrentText(number + QString("mm"));

    bool ok = false;
    qreal increment = number.toDouble(&ok);

    if(ok)
        m_toolheadControlFrame->setIncrement(increment);
    else
        qDebug() << QString("Could not set toolhead increment: Invalid number format \"") + number + QString("\"");
}

void ToolheadWidget::on_xDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->xDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().x())
        xPosEditing = true;
}

void ToolheadWidget::on_yDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->yDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().y())
        yPosEditing = true;
}

void ToolheadWidget::on_zDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->zDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().z())
        zPosEditing = true;
}

void ToolheadWidget::on_positionResetButton_clicked()
{
    ui->xDestinationSpinBox->setValue((m_printer->toolhead()->destination().x()));
    ui->yDestinationSpinBox->setValue((m_printer->toolhead()->destination().y()));
    ui->zDestinationSpinBox->setValue((m_printer->toolhead()->destination().z()));
}

void ToolheadWidget::on_positionApplyButton_clicked()
{
    QKlipperPosition position;
    position["x"] = (ui->xDestinationSpinBox->value());
    position["y"] = (ui->yDestinationSpinBox->value());
    position["z"] = (ui->zDestinationSpinBox->value());

    switch(m_printer->status())
    {
    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        m_printer->toolhead()->setPosition(position);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void ToolheadWidget::onToolheadPositionChanged()
{
    ui->xDestinationSpinBox->setPrefix(QString("X: "));
    ui->yDestinationSpinBox->setPrefix(QString("Y: "));
    ui->zDestinationSpinBox->setPrefix(QString("Z: "));

    ui->xDestinationSpinBox->setSuffix(QString("mm <i>(%1)</i>").arg(m_printer->toolhead()->position().x(), 0, 'f', 2));
    ui->yDestinationSpinBox->setSuffix(QString("mm <i>(%1)</i>").arg(m_printer->toolhead()->position().y(), 0, 'f', 2));
    ui->zDestinationSpinBox->setSuffix(QString("mm <i>(%1)</i>").arg(m_printer->toolhead()->position().z(), 0, 'f', 2));
}

void ToolheadWidget::onToolHeadDestinationChanged()
{
    if(!xPosEditing && !ui->xDestinationSpinBox->hasFocus())
        ui->xDestinationSpinBox->setValue((m_printer->toolhead()->destination().x()));

    if(!yPosEditing && !ui->yDestinationSpinBox->hasFocus())
        ui->yDestinationSpinBox->setValue((m_printer->toolhead()->destination().y()));

    if(!zPosEditing && !ui->zDestinationSpinBox->hasFocus())
        ui->zDestinationSpinBox->setValue((m_printer->toolhead()->destination().z()));
}

void ToolheadWidget::onToolHeadIsHomedChanged()
{
    ui->xDestinationSpinBox->setEnabled(m_printer->toolhead()->isHomed());
    ui->yDestinationSpinBox->setEnabled(m_printer->toolhead()->isHomed());
    ui->zDestinationSpinBox->setEnabled(m_printer->toolhead()->isHomed());
    ui->positionApplyButton->setEnabled(m_printer->toolhead()->isHomed());
    ui->positionResetButton->setEnabled(m_printer->toolhead()->isHomed());
}

void ToolheadWidget::onZOffsetWizardFinished(int returnCode)
{
    Q_UNUSED(returnCode)

    delete m_zOffsetWizard;
    m_zOffsetWizard = nullptr;
}

void ToolheadWidget::onInputShaperWizardFinished(int returnCode)
{
    Q_UNUSED(returnCode)

    delete m_inputShaperWizard;
    m_inputShaperWizard = nullptr;
}

void ToolheadWidget::on_zOffsetWizardButton_clicked()
{
    if(!m_instance)
        return;

    if(m_zOffsetWizard)
        delete m_zOffsetWizard;

    m_zOffsetWizard = new ZOffsetWizard(m_instance, this);
    emit wizardRequested(m_zOffsetWizard);

    connect(m_zOffsetWizard, SIGNAL(finished(int)), this, SLOT(onZOffsetWizardFinished(int)));
}

void ToolheadWidget::on_inputShaperButton_clicked()
{
    if(m_instance)
    {
        if(m_inputShaperWizard)
            delete m_inputShaperWizard;

        m_inputShaperWizard = new InputShaperWizard(m_instance, this);
        emit wizardRequested(m_inputShaperWizard);

        connect(m_inputShaperWizard, SIGNAL(finished(int)), this, SLOT(onInputShaperWizardFinished(int)));
    }
}
