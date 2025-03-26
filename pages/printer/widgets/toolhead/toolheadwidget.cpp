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
    m_extruder = m_printer->toolhead()->currentExtruder();

    QRegularExpression distanceExpression("\\d+\\.\\d+\\s*", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionValidator *distanceValidator = new QRegularExpressionValidator(distanceExpression);
    ui->posIncrementSelect->setValidator(distanceValidator);

    m_toolheadControlFrame = new ToolHeadControlFrame(instance->printer()->toolhead(), ui->controlContents);
    ui->controlContents->layout()->addWidget(m_toolheadControlFrame);

    //ui->currentPositionFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));

    connect(m_printer->toolhead(), SIGNAL(positionChanged()), this, SLOT(onToolheadPositionChanged()));
    connect(m_printer->toolhead(), SIGNAL(destinationChanged()), this, SLOT(onToolHeadDestinationChanged()));
    connect(m_printer->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolHeadIsHomedChanged()));
    connect(m_printer->toolhead(), SIGNAL(currentExtruderNameChanged()), this, SLOT(onToolHeadCurrentExtruderChanged()));

    onToolHeadIsHomedChanged();
    onToolHeadCurrentExtruderChanged();
    onExtruderCurrentTempChanged();

    ui->toolheadControlFrame->setCentralWidget(ui->toolheadContentWidget);
    ui->extruderFrame->setCentralWidget(ui->extruderContentFrame);
    ui->targetPositionFrame->setCentralWidget(ui->currentPositionContentWidget);

    ui->toolheadControlFrame->setTitle("Control");
    ui->targetPositionFrame->setTitle("Target Position");
    ui->extruderFrame->setTitle("Toolhead Status");

    ui->locationFrame->setProperty("class", QStringList {"SubWidget"});
}

ToolheadWidget::~ToolheadWidget()
{
    delete ui;
}

void ToolheadWidget::setIcons()
{
    ui->targetPositionFrame->setIcon(Settings::getThemeIcon(QString("location")));
    ui->toolheadControlFrame->setIcon(Settings::getThemeIcon(QString("control")));
    ui->extruderFrame->setIcon(Settings::getThemeIcon(QString("location")));
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
    {
        xPosEditing = true;
    }
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
    xPosEditing = false;
    yPosEditing = false;
    zPosEditing = false;
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

    on_positionResetButton_clicked();
}

void ToolheadWidget::onToolheadPositionChanged()
{
    ui->locationFrame->setX(m_printer->toolhead()->position().x());
    ui->locationFrame->setY(m_printer->toolhead()->position().y());
    ui->locationFrame->setXMaximum(m_printer->toolhead()->maxPosition().x());
    ui->locationFrame->setYMaximum(m_printer->toolhead()->maxPosition().y());

    if(!xPosEditing)
    {
        ui->xDestinationSpinBox->setValue((m_printer->toolhead()->destination().x()));
        xPosEditing = false;
    }

    if(!yPosEditing)
    {
        ui->yDestinationSpinBox->setValue((m_printer->toolhead()->destination().y()));
        yPosEditing = false;
    }

    if(!zPosEditing)
    {
        ui->zDestinationSpinBox->setValue((m_printer->toolhead()->destination().z()));
        zPosEditing = false;
    }

    ui->xPosLabel->setText(QString("<i>%1</i>").arg(m_printer->toolhead()->position().x(), 0, 'f', 2));
    ui->yPosLabel->setText(QString("<i>%1</i>").arg(m_printer->toolhead()->position().y(), 0, 'f', 2));
    ui->zPosLabel->setText(QString("<i>%1</i>").arg(m_printer->toolhead()->position().z(), 0, 'f', 2));
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

void ToolheadWidget::onToolHeadCurrentExtruderChanged()
{
    ui->currentExtruderLabel->setText(QString("<h3>Current Extruder</h3> %1").arg(m_printer->toolhead()->currentExtruderName()));
    ui->extruderCountLabel->setText(QString("<h3>Extruder Count</h3> %1").arg(m_printer->toolhead()->extruderMap().count()));
}

void ToolheadWidget::onExtruderCurrentTempChanged()
{
    if(!m_extruder)
        return;
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
