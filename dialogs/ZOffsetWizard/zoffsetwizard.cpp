#include "zoffsetwizard.h"
#include "ui_zoffsetwizard.h"
#include "flo/settings.h"
#include "dialogs/MessageDialog/messagedialog.h"

ZOffsetWizard::ZOffsetWizard(QKlipperInstance *instance, QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::ZOffsetWizard)
{
    ui->setupUi(this);

    m_instance = instance;

    connect(m_instance->printer()->toolhead(), SIGNAL(homing()), this, SLOT(onHomingStarted()));
    connect(m_instance->printer()->toolhead(), SIGNAL(homingFinished()), this, SLOT(onHomingFinished()));
}

ZOffsetWizard::~ZOffsetWizard()
{
    delete ui;
}

bool ZOffsetWizard::validateCurrentPage()
{
    switch(currentId())
    {
    case 0:
        return true;
        break;

    case 1:
        return (m_homingStarted && m_homingFinished);
        break;
    }

    return false;
}

void ZOffsetWizard::on_ZOffsetWizard_currentIdChanged(int id)
{
    if(id == 1)
    {
        if(m_instance->printer()->status() != QKlipperPrinter::Ready)
        {
            showErrorMessage("Could not start wizard. Printer must be on and in the \"Ready\" state to continue.");

            done(Rejected);
        }

        else if(!m_homingStarted && !m_homingFinished)
        {
            qDebug() << "Printer Ready. Homing Toolhead";

            goToHome();
        }
    }
}

void ZOffsetWizard::showErrorMessage(QString message)
{
    MessageDialog *dialog = new MessageDialog(this);
    dialog->setIcon(Settings::getThemeIcon("error"));
    dialog->setText(message);
    dialog->exec();

    delete dialog;
}

void ZOffsetWizard::goToHome()
{
    m_instance->printer()->toolhead()->home();
}

void ZOffsetWizard::onHomingStarted()
{
    m_homingStarted = true;
    m_homingFinished = false;
}

void ZOffsetWizard::onHomingFinished()
{
    m_homingFinished = true;

    QKlipperError error;
    QString command = QString("PROBE_CALIBRATE");

    m_instance->console()->printerGcodeScript(command, &error);

    if(error.type() != QKlipperError::NoError)
    {
        m_homingStarted = false;
        m_homingFinished = false;
        back();
        showErrorMessage("Could not start calibration");
        return;
    }

    m_wizardStarted = true;
    next();
}

bool ZOffsetWizard::moveToolhead(qreal amount)
{
    if(m_instance->printer()->status() != QKlipperPrinter::Ready)
    {
        showErrorMessage("Could not move toolhead. Printer must be on and in the \"Ready\" state to continue.");
        return false;
    }

    QKlipperError error;
    QString command = QString("TESTZ=%1").arg(QString::number(amount));

    m_instance->console()->printerGcodeScript(command, &error);

    if(error.type() != QKlipperError::NoError)
        return false;

    return true;
}

bool ZOffsetWizard::acceptOffset()
{
    QKlipperError error;
    m_instance->console()->printerGcodeScript("ACCEPT", &error);

    if(error.type() != QKlipperError::NoError)
        return false;

    return true;
}

bool ZOffsetWizard::rejectOffset()
{
    QKlipperError error;
    m_instance->console()->printerGcodeScript("ABORT", &error);

    if(error.type() != QKlipperError::NoError)
        return false;

    return true;
}

bool ZOffsetWizard::saveOffset()
{
    QKlipperError error;
    m_instance->console()->printerGcodeScript("SAVE_CONFIG", &error);

    if(error.type() != QKlipperError::NoError)
        return false;

    return true;
}

void ZOffsetWizard::on_up0025Button_clicked()
{
    moveToolhead(0.025);
}

void ZOffsetWizard::on_up005Button_clicked()
{
    moveToolhead(0.05);
}

void ZOffsetWizard::on_up010Button_clicked()
{
    moveToolhead(0.1);
}

void ZOffsetWizard::on_up050Button_clicked()
{
    moveToolhead(0.5);
}

void ZOffsetWizard::on_up10Button_clicked()
{
    moveToolhead(1.0);
}

void ZOffsetWizard::on_down0025Button_clicked()
{
    moveToolhead(-0.025);
}

void ZOffsetWizard::on_down005Button_clicked()
{
    moveToolhead(-0.05);
}

void ZOffsetWizard::on_down010Button_clicked()
{
    moveToolhead(-0.1);
}

void ZOffsetWizard::on_down050Button_clicked()
{
    moveToolhead(-0.5);
}

void ZOffsetWizard::on_down10Button_clicked()
{
    moveToolhead(-1);
}

void ZOffsetWizard::on_ZOffsetWizard_finished(int result)
{
    if(result == Accepted)
    {
        MessageDialog *dialog = new MessageDialog(this);
        dialog->setRejectEnabled(true);
        dialog->setIcon(Settings::getThemeIcon("question"));
        dialog->setText("Would you like to save the result?");

        int ret = dialog->exec();

        switch(QDialog::DialogCode(ret))
        {
        case QDialog::Rejected:
            rejectOffset();
            break;
        case QDialog::Accepted:
            if(!acceptOffset())
                showErrorMessage("Could not send command to accept probe calibration");

            if(!saveOffset())
                showErrorMessage("Could not send command to save probe calibration");
            break;
        }

        delete dialog;
    }
    else if(m_wizardStarted && !rejectOffset())
    {
        showErrorMessage("Could not send command to abort probe calibration");
    }
}
