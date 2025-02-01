#include "inputshaperwizard.h"
#include "ui_inputshaperwizard.h"
#include "flo/settings.h"

InputShaperWizard::InputShaperWizard(QKlipperInstance *instance, QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::InputShaperWizard)
{
    ui->setupUi(this);

    m_instance = instance;

    connect(m_instance->server(), SIGNAL(fileListChanged(QString)), this, SLOT(onServerFileListChanged()));
}

InputShaperWizard::~InputShaperWizard()
{
    delete ui;
}

bool InputShaperWizard::validateCurrentPage()
{
    switch(currentId())
    {
    case 0:
        return true;
        break;

    case 1:
        return m_printerConfigured;
        break;

    case 2:
        return m_fileSelected;
        break;

    case 3:
        return (m_printingStarted && m_instance->printer()->status() != QKlipperPrinter::Printing);
        break;

    case 4:
        return true;
        break;

    case 5:
        return (m_secondPrintingStarted && m_instance->printer()->status() != QKlipperPrinter::Printing);
        break;

    case 6:
        return true;
        break;
    }

    return false;
}

void InputShaperWizard::savePrinterSettings()
{
    m_squareCornerVelocity = m_instance->printer()->squareCornerVelocity();
    m_minimumCruiseRatio = m_instance->printer()->minimumCruiseRatio();
    m_pressureAdvance = m_instance->printer()->toolhead()->currentExtruder()->pressureAdvance();
}

bool InputShaperWizard::saveConfig()
{
    QKlipperError error;

    m_instance->console()->printerGcodeScript(
        "SAVE_CONFIG",
        &error
    );

    if(error.type() != QKlipperError::NoError)
        return false;

    return true;
}

bool InputShaperWizard::configurePrinter()
{
    QKlipperError error;

    savePrinterSettings();

    disableSquareCornerVelocity(&error);
    if(error.type() != QKlipperError::NoError)
    {
        qDebug() << "Error sending square corner velocity setting";
        return false;
    }
    ui->configuringProgressBar->setValue(25);

    disableMinimumCruiseRatio(&error);
    if(error.type() != QKlipperError::NoError)
    {
        qDebug() << "Error sending minimum cruise ratio setting";
        return false;
    }
    ui->configuringProgressBar->setValue(50);

    disablePressureAdvance(&error);
    if(error.type() != QKlipperError::NoError)
    {
        qDebug() << "Error sending minimum cruise ratio setting";
        return false;
    }
    ui->configuringProgressBar->setValue(75);

    disableInputShaper(&error);

    m_printerConfigured = true;
    ui->configuringProgressBar->setValue(100);

    return true;
}

void InputShaperWizard::disableSquareCornerVelocity(QKlipperError *error)
{
    m_instance->console()->printerGcodeScript(
        "SET_VELOCITY_LIMIT SQUARE_CORNER_VELOCITY=5",
        error
    );
}

void InputShaperWizard::disableMinimumCruiseRatio(QKlipperError *error)
{
    m_instance->console()->printerGcodeScript(
        "SET_VELOCITY_LIMIT MINIMUM_CRUISE_RATIO=0",
        error
    );
}

void InputShaperWizard::disablePressureAdvance(QKlipperError *error)
{
    m_instance->console()->printerGcodeScript(
        "SET_PRESSURE_ADVANCE ADVANCE=0",
        error
    );
}

void InputShaperWizard::disableInputShaper(QKlipperError *error)
{
    m_instance->console()->printerGcodeScript(
        "SET_INPUT_SHAPER SHAPER_FREQ_X=0 SHAPER_FREQ_Y=0",
        error
    );
}

bool InputShaperWizard::resetPrinterSettings()
{
    QKlipperError error;

    resetSquareCornerVelocity(&error);
    if(error.type() != QKlipperError::NoError)
    {
        qDebug() << "Error sending square corner velocity setting";
        return false;
    }

    resetMinimumCruiseRatio(&error);
    if(error.type() != QKlipperError::NoError)
    {
        qDebug() << "Error sending minimum cruise ratio setting";
        return false;
    }

    resetPressureAdvance(&error);
    if(error.type() != QKlipperError::NoError)
    {
        qDebug() << "Error sending minimum cruise ratio setting";
        return false;
    }

    return true;
}

void InputShaperWizard::resetSquareCornerVelocity(QKlipperError *error)
{
    m_instance->console()->printerGcodeScript(
        "SET_VELOCITY_LIMIT SQUARE_CORNER_VELOCITY=" + QString::number(m_squareCornerVelocity),
        error
    );
}

void InputShaperWizard::resetMinimumCruiseRatio(QKlipperError *error)
{
    m_instance->console()->printerGcodeScript(
        "SET_VELOCITY_LIMIT MINIMUM_CRUISE_RATIO=" + QString::number(m_minimumCruiseRatio),
        error
    );
}

void InputShaperWizard::resetPressureAdvance(QKlipperError *error)
{
    m_instance->console()->printerGcodeScript(
        "SET_PRESSURE_ADVANCE ADVANCE=" + QString::number(m_pressureAdvance),
        error
    );
}

void InputShaperWizard::setInputShaper(QKlipperError *error)
{
    QString command = QString("SET_INPUT_SHAPER SHAPER_FREQ_X=%1 SHAPER_FREQ_Y=%2 SHAPER_TYPE=%3").arg(
        QString::number(getXResonance()),
        QString::number(getYResonance()),
        ui->shaperTypeComboBox->currentText()
    );

    m_instance->console()->printerGcodeScript(command, error);
}

void InputShaperWizard::onServerFileListChanged()
{
    QKlipperFileList fileEntries = m_instance->server()->fileList(m_currentDirectory + "/");
    QKlipperFileList directories;
    QKlipperFileList files;

    ui->fileListWidget->clear();

    for(QKlipperFile *file : fileEntries)
    {
        if(file->fileType() == QKlipperFile::Directory)
            directories += file;
        else
            files += file;
    }

    if(m_currentDirectory != "gcodes")
    {
        QListWidgetItem *item = new QListWidgetItem(ui->fileListWidget);
        item->setText("..");
        item->setIcon(Settings::getThemeIcon("folder"));
        item->setData(Qt::UserRole, QString("dir:.."));

        ui->fileListWidget->addItem(item);
    }

    for(QKlipperFile *file : directories)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->fileListWidget);
        item->setText(file->filename());
        item->setIcon(Settings::getThemeIcon("folder"));
        item->setData(Qt::UserRole, QString("dir:") + file->uri());

        ui->fileListWidget->addItem(item);
    }

    for(QKlipperFile *file : files)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->fileListWidget);
        item->setText(file->filename());
        item->setIcon(Settings::getThemeIcon("file"));
        item->setData(Qt::UserRole, QString("file:") + file->uri());

        ui->fileListWidget->addItem(item);
    }
}

void InputShaperWizard::showErrorMessage(QString message)
{
    MessageDialog *dialog = new MessageDialog(this);
    dialog->setIcon(Settings::getThemeIcon("error"));
    dialog->setText(message);
    dialog->exec();

    delete dialog;
}

bool InputShaperWizard::printCurrentFile()
{
    QKlipperError error;

    m_instance->console()->printerPrintStart(m_selectedFile, &error);

    if(error.type() != QKlipperError::NoError)
        return false;

    return true;
}

qreal InputShaperWizard::getXResonance()
{
    qreal distance = ui->xDistanceSpinBox->value();
    qreal rings = ui->xRingSpinBox->value();
    qreal velocity = ui->xVelocitySpinBox->value();

    qreal result = velocity * rings / distance;

    return result;
}

qreal InputShaperWizard::getYResonance()
{
    qreal distance = ui->yDistanceSpinBox->value();
    qreal rings = ui->yRingSpinBox->value();
    qreal velocity = ui->yVelocitySpinBox->value();

    qreal result = velocity * rings / distance;

    return result;
}

bool InputShaperWizard::setupTuningTower()
{
    QKlipperError error;

    m_instance->console()->printerGcodeScript(
        "TUNING_TOWER COMMAND=SET_VELOCITY_LIMIT PARAMETER=ACCEL START=1500 STEP_DELTA=500 STEP_HEIGHT=5",
        &error
    );

    if(error.type() != QKlipperError::NoError)
    {
        qDebug() << "Error sending tuning tower settings";
        return false;
    }

    return true;
}

void InputShaperWizard::on_InputShaperWizard_currentIdChanged(int id)
{

    if(id == 1)
    {
        if(m_instance->printer()->status() != QKlipperPrinter::Ready)
        {
            showErrorMessage("Could not start wizard. Printer must be on and in the \"Ready\" state to continue.");

            done(Rejected);
        }

        else if(!hasVisitedPage(id))
            configurePrinter();
    }

    if(id == 2)
    {
        m_instance->console()->serverFilesList(m_currentDirectory);
    }

    if(id == 3)
    {
        if(!m_printingStarted)
        {
            ui->throbberWidget->setIsPlaying(true);

            if(!setupTuningTower())
            {
                showErrorMessage("Could not setup tuning tower parameters");
                back();
            }

            else if(!printCurrentFile())
            {
                showErrorMessage("Could not print tuning tower");
                back();
            }
        }
    }

    if(id == 5)
    {
        if(!m_secondPrintingStarted)
        {
            ui->throbberWidget->setIsPlaying(true);

            if(!setupTuningTower())
            {
                showErrorMessage("Could not setup tuning tower parameters");
                back();
            }

            else if(!printCurrentFile())
            {
                showErrorMessage("Could not print tuning tower");
                back();
            }
        }
    }
}

void InputShaperWizard::on_InputShaperWizard_rejected()
{
    //resetPrinterSettings();
}

void InputShaperWizard::on_reRunButton_clicked()
{
    m_secondPrintingStarted = false;
    int steps = currentId() - 4;

    for(; steps > 0; --steps)
        back();
}

void InputShaperWizard::on_saveButton_clicked()
{
    if(!saveConfig())
    {
        MessageDialog *dialog = new MessageDialog(this);
        dialog->setText("Could not save printer settings");
        dialog->exec();

        delete dialog;
    }
}

void InputShaperWizard::on_fileListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString data = item->data(Qt::UserRole).toString();

    if(data.startsWith("dir:"))
    {
        data.remove("dir:");

        if(data == "..")
        {
            int index = m_currentDirectory.lastIndexOf("/");
            m_currentDirectory = m_currentDirectory.left(index);
        }
        else
            m_currentDirectory = data;

        onServerFileListChanged();
    }
}

void InputShaperWizard::on_fileListWidget_itemSelectionChanged()
{
    QListWidgetItem *item = ui->fileListWidget->currentItem();
    QString data = item->data(Qt::UserRole).toString();

    if(data.startsWith("file:"))
    {
        data.remove("file:");

        m_selectedFile = data;
        m_fileSelected = true;
    }
}
