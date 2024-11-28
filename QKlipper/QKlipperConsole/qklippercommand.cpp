#include "qklippercommand.h"

QMap<QString, QKlipperCommand*> QKlipperCommand::m_commands;
bool QKlipperCommand::m_isInitialized = false;
bool QKlipperCommand::m_isInitializing = false;

QKlipperCommand::QKlipperCommand(QString command)
    : QVariant{}
{
    initialize();
    m_command = command;

    if(m_commands.contains(m_command))
    {
        m_help = m_commands[m_command]->m_help;
        m_parameters = m_commands[m_command]->m_parameters;
    }
}

bool QKlipperCommand::isKlipperCommand(const QString &command)
{
    initialize();
    return m_commands.contains(command);
}

QString QKlipperCommand::command() const
{
    return m_command;
}

void QKlipperCommand::setCommand(const QString &command)
{
    m_command = command;
}

QString QKlipperCommand::help() const
{
    return m_help;
}

void QKlipperCommand::setHelp(const QString &help)
{
    m_help = help;
}

void QKlipperCommand::setParameter(const QString &key)
{
    m_parameters += key;
}

void QKlipperCommand::initialize()
{
    if(!m_isInitialized && !m_isInitializing)
    {
        m_isInitializing = true;

        QFile commandsFile(QString(":/data/klipper_commands.json"));

        if(!commandsFile.open(QFile::ReadOnly))
        {
            qDebug() << QString("Could not open resource");
            return;
        }

        //Read the data from the resource
        QByteArray data = commandsFile.readAll();

        //Construct the document object
        QJsonDocument document;
        QJsonParseError documentError;

        document = QJsonDocument::fromJson(data, &documentError);

        //Check for errors
        if(documentError.error != QJsonParseError::NoError)
        {
            qDebug() << QString("Could not parse resource");
            return;
        }

        //Get klipper commands object
        QJsonObject rootObject = document["klipper_commands"].toObject();
        QStringList rootKeys = rootObject.keys();

        foreach(QString key, rootKeys)
        {
            //Parse through the objects of the section
            QJsonArray array = rootObject[key].toArray();

            for(int i = 0; i < array.count(); i++)
            {
                if(array[i].isObject())
                {
                    QJsonObject commandObject = array[i].toObject();

                    QKlipperCommand *command = new QKlipperCommand();
                    command->setCommand(commandObject["command"].toString());
                    command->setHelp(commandObject["help"].toString());

                    QJsonArray parametersArray = commandObject["parameters"].toArray();

                    for(int p = 0; p < parametersArray.count(); p++)
                        command->m_parameters += parametersArray[p].toString();

                    m_commands.insert(command->command().toUpper(), command);
                }
            }
        }
    }
}

QStringList QKlipperCommand::parameters() const
{
    return m_parameters;
}
