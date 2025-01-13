#include "qmoonrakervalidator.h"

QMoonrakerValidator::QMoonrakerValidator(QObject *parent)
    : QValidator{parent}
{

}

QMoonrakerValidator::~QMoonrakerValidator()
{

}

/*!
 * \brief QMoonrakerValidator::validate
 * \param text
 * \param pos
 * \return Valid/Invalid state
 */
QValidator::State QMoonrakerValidator::validate(QString &text, int &pos) const
{
    Q_UNUSED(pos)

    if(text.contains(m_httpExpression))
        return QValidator::Acceptable;

    QDir instanceDirectory(text);

    if(instanceDirectory.exists())
    {
        bool valid = true;
        //ui->textEdit->append(QString("Scanning directory"));
        QStringList subDirs = instanceDirectory.entryList(QDir::Dirs);

        if(!subDirs.contains(QString("comms")))
            valid = false;
        else
        {
            QString location = text;
            location += QDir::separator() + QString("comms") + QDir::separator();

            if(!QFile::exists(location + QString("klippy.sock")))
                valid = false;

            if(!QFile::exists(location + QString("moonraker.sock")))
                valid = false;
        }

        if(!subDirs.contains(QString("gcodes")))
            valid = false;

        if(!subDirs.contains(QString("logs")))
            valid = false;

        if(!subDirs.contains(QString("config")))
            valid = false;

        if(valid)
            return QValidator::Acceptable;
        else
            return QValidator::Invalid;
    }

    return QValidator::Intermediate;
}
