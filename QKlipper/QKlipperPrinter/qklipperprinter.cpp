#include "qklipperprinter.h"
#include "QKlipper/QKlipperConsole/qklipperconsole.h"

QKlipperPrinter::QKlipperPrinter(QObject *parent)
    : QObject{parent}
{
    m_mcu = new QKlipperMCU(this);
    m_chamber = new QKlipperChamber(this);
    m_toolhead = new QKlipperToolHead(this);
    m_printJob = new QKlipperPrintJob(this);
    m_gCodeStore = new QKlipperGCodeStore(this);
    m_bed = new QKlipperPrintBed(this);
}

QKlipperPrinter::~QKlipperPrinter()
{
    if(m_mcu)
        m_mcu->deleteLater();
    if(m_chamber)
        m_chamber->deleteLater();
    if(m_toolhead)
        m_toolhead->deleteLater();
    if(m_printJob)
        m_printJob->deleteLater();
    if(m_gCodeStore)
        m_gCodeStore->deleteLater();

    for(QKlipperFan *fan : m_fans)
        fan->deleteLater();

    for(QKlipperStepperMotor *motor : m_stepperMotors)
        motor->deleteLater();
}

QKlipperToolHead *QKlipperPrinter::toolhead() const
{
    return m_toolhead;
}

void QKlipperPrinter::setToolhead(QKlipperToolHead *toolhead)
{
    if (m_toolhead == toolhead)
        return;

    m_toolhead = toolhead;
    emit toolheadChanged();
}

QKlipperPrintBed *QKlipperPrinter::bed() const
{
    return m_bed;
}

void QKlipperPrinter::setBed(QKlipperPrintBed *bed)
{
    if (m_bed == bed)
        return;

    m_bed = bed;
    emit bedChanged();
}

QKlipperChamber *QKlipperPrinter::chamber() const
{
    return m_chamber;
}

void QKlipperPrinter::setChamber(QKlipperChamber *chamber)
{
    if (m_chamber == chamber)
        return;

    m_chamber = chamber;
    emit chamberChanged();
}

QMap<QString, qreal> QKlipperPrinter::powerProfile() const
{
    return m_powerProfile;
}

void QKlipperPrinter::setPowerProfile(const QMap<QString, qreal> &powerProfile)
{
    if (m_powerProfile == powerProfile)
        return;

    m_powerProfile = powerProfile;
    emit powerProfileChanged();
}

QString QKlipperPrinter::name() const
{
    return m_name;
}

void QKlipperPrinter::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

QString QKlipperPrinter::id() const
{
    return m_id;
}

void QKlipperPrinter::setId(const QString &id)
{
    if (m_id == id)
        return;
    m_id = id;
    emit idChanged();
}

QString QKlipperPrinter::firmwareVersion() const
{
    return m_firmwareVersion;
}

void QKlipperPrinter::setFirmwareVersion(const QString &firmwareVersion)
{
    if (m_firmwareVersion == firmwareVersion)
        return;
    m_firmwareVersion = firmwareVersion;
    emit firmwareVersionChanged();
}

QString QKlipperPrinter::statusMessage() const
{
    return m_statusMessage;
}

void QKlipperPrinter::setStatusMessage(const QString &statusMessage)
{
    if (m_statusMessage == statusMessage)
        return;
    m_statusMessage = statusMessage;
    emit statusMessageChanged();
}

QString QKlipperPrinter::configFile() const
{
    return m_configFile;
}

void QKlipperPrinter::setConfigFile(const QString &configFile)
{
    if (m_configFile == configFile)
        return;
    m_configFile = configFile;
    emit configFileChanged();
}

QString QKlipperPrinter::kinematics() const
{
    return m_kinematics;
}

void QKlipperPrinter::setKinematics(const QString &kinematics)
{
    if (m_kinematics == kinematics)
        return;
    m_kinematics = kinematics;
    emit kinematicsChanged();
}

QString QKlipperPrinter::color() const
{
    return m_color;
}

void QKlipperPrinter::setColor(const QString &color)
{
    if (m_color == color)
        return;
    m_color = color;
    emit colorChanged();
}

qreal QKlipperPrinter::maxAcceleration() const
{
    return m_maxAcceleration;
}

void QKlipperPrinter::setMaxAcceleration(qreal maxAcceleration)
{
    if (qFuzzyCompare(m_maxAcceleration, maxAcceleration))
        return;
    m_maxAcceleration = maxAcceleration;
    emit maxAccelerationChanged();
}

qreal QKlipperPrinter::maxVelocity() const
{
    return m_maxVelocity;
}

void QKlipperPrinter::setMaxVelocity(qreal maxVelocity)
{
    if (qFuzzyCompare(m_maxVelocity, maxVelocity))
        return;
    m_maxVelocity = maxVelocity;
    emit maxVelocityChanged();
}

qreal QKlipperPrinter::maxZAcceleration() const
{
    return m_maxZAcceleration;
}

void QKlipperPrinter::setMaxZAcceleration(qreal maxZAcceleration)
{
    if (qFuzzyCompare(m_maxZAcceleration, maxZAcceleration))
        return;
    m_maxZAcceleration = maxZAcceleration;
    emit maxZAccelerationChanged();
}

qreal QKlipperPrinter::maxZVelocity() const
{
    return m_maxZVelocity;
}

void QKlipperPrinter::setMaxZVelocity(qreal maxZVelocity)
{
    if (qFuzzyCompare(m_maxZVelocity, maxZVelocity))
        return;
    m_maxZVelocity = maxZVelocity;
    emit maxZVelocityChanged();
}

qreal QKlipperPrinter::squareCornerVelocity() const
{
    return m_squareCornerVelocity;
}

void QKlipperPrinter::setSquareCornerVelocity(qreal squareCornerVelocity)
{
    if (qFuzzyCompare(m_squareCornerVelocity, squareCornerVelocity))
        return;
    m_squareCornerVelocity = squareCornerVelocity;
    emit squareCornerVelocityChanged();
}

qreal QKlipperPrinter::printTime() const
{
    return m_printTime;
}

void QKlipperPrinter::setPrintTime(qreal printTime)
{
    if (qFuzzyCompare(m_printTime, printTime))
        return;
    m_printTime = printTime;
    emit printTimeChanged();
}

bool QKlipperPrinter::autoConnect() const
{
    return m_autoConnect;
}

void QKlipperPrinter::setAutoConnect(bool autoConnect)
{
    if (m_autoConnect == autoConnect)
        return;
    m_autoConnect = autoConnect;
    emit autoConnectChanged();
}

bool QKlipperPrinter::defaultPrinter() const
{
    return m_defaultPrinter;
}

void QKlipperPrinter::setDefaultPrinter(bool defaultPrinter)
{
    if (m_defaultPrinter == defaultPrinter)
        return;
    m_defaultPrinter = defaultPrinter;
    emit defaultPrinterChanged();
}

QDateTime QKlipperPrinter::printStarted() const
{
    return m_printStarted;
}

void QKlipperPrinter::setPrintStarted(const QDateTime &printStarted)
{
    if (m_printStarted == printStarted)
        return;
    m_printStarted = printStarted;
    emit printStartedChanged();
}

QDateTime QKlipperPrinter::printEnding() const
{
    return m_printEnding;
}

void QKlipperPrinter::setPrintEnding(const QDateTime &printEnding)
{
    if (m_printEnding == printEnding)
        return;
    m_printEnding = printEnding;
    emit printEndingChanged();
}

QKlipperPrinter::Status QKlipperPrinter::status() const
{
    return m_status;
}

void QKlipperPrinter::setStatus(Status status)
{
    if (m_status == status)
        return;
    m_status = status;
    emit statusChanged();
}

QKlipperConsole *QKlipperPrinter::console() const
{
    return m_console;
}

void QKlipperPrinter::setConsole(QKlipperConsole *console)
{
    if (m_console == console)
        return;

    m_bed->setConsole(console);
    m_toolhead->setConsole(console);

    QMapIterator<QString, QKlipperFan*> iterator(m_fans);

    while(iterator.hasNext())
    {
        iterator.next();
        iterator.value()->setConsole(console);
    }

    m_console = console;
    emit consoleChanged();
}

QKlipperPrintJob *QKlipperPrinter::printJob() const
{
    return m_printJob;
}

void QKlipperPrinter::setPrintJob(QKlipperPrintJob *printJob)
{
    if (m_printJob == printJob)
        return;

    m_printJob = printJob;
    emit printJobChanged();
}

QKlipperGCodeStore *QKlipperPrinter::gCodeStore() const
{
    return m_gCodeStore;
}

void QKlipperPrinter::setGCodeStore(QKlipperGCodeStore *gCodeStore)
{
    if (m_gCodeStore == gCodeStore)
        return;

    m_gCodeStore = gCodeStore;
    emit gCodeStoreChanged();
}

QKlipperMCU *QKlipperPrinter::mcu() const
{
    return m_mcu;
}

void QKlipperPrinter::setMcu(QKlipperMCU *mcu)
{
    if (m_mcu == mcu)
        return;

    m_mcu = mcu;
    emit mcuChanged();
}

QKlipperFile *QKlipperPrinter::currentFile() const
{
    return m_currentFile;
}

void QKlipperPrinter::setCurrentFile(QKlipperFile *currentFile)
{
    if (m_currentFile == currentFile)
        return;

    m_currentFile = currentFile;
    emit currentFileChanged();
}

QKlipperSafeZHome QKlipperPrinter::safeZHome() const
{
    return m_safeZHome;
}

void QKlipperPrinter::setSafeZHome(QKlipperSafeZHome safeZHome)
{
    if (m_safeZHome == safeZHome)
        return;

    m_safeZHome = safeZHome;
    emit safeZHomeChanged();
}

QKlipperExtruder *QKlipperPrinter::extruder(const QString &name)
{
    return m_toolhead->extruder(name);
}

void QKlipperPrinter::setExtruder(QString name, QKlipperExtruder *extruder)
{
    m_toolhead->setExtruder(name, extruder);
}

QMap<QString, QKlipperFan *> QKlipperPrinter::fans() const
{
    return m_fans;
}

QKlipperFan *QKlipperPrinter::fan(const QString &name) const
{
    if(m_fans.contains(name))
        return m_fans[name];

    return nullptr;
}

void QKlipperPrinter::setFans(const QMap<QString, QKlipperFan *> &fans)
{
    if (m_fans == fans)
        return;

    m_fans = fans;
    emit fansChanged();
}

void QKlipperPrinter::setFan(const QString &name, QKlipperFan *fan)
{
    if(m_fans.contains(name))
    {
        if(fan == m_fans[name])
            return;

        QKlipperFan *current = m_fans[name];
        m_fans.remove(name);

        current->deleteLater();
    }

    m_fans[name] = fan;
    emit fansChanged();
}

QKlipperGCodeMove QKlipperPrinter::gcodeMove() const
{
    return m_gcodeMove;
}

void QKlipperPrinter::setGcodeMove(const QKlipperGCodeMove &gcodeMove)
{
    if (m_gcodeMove == gcodeMove)
        return;

    m_gcodeMove = gcodeMove;
    emit gcodeMoveChanged();
}

QMap<QString, QKlipperStepperMotor *> QKlipperPrinter::stepperMotors() const
{
    return m_stepperMotors;
}

QKlipperStepperMotor *QKlipperPrinter::stepperMotor(const QString &name)
{
    if(m_stepperMotors.contains(name))
        return m_stepperMotors[name];

    return nullptr;
}

void QKlipperPrinter::setStepperMotors(const QMap<QString, QKlipperStepperMotor *> &stepperMotors)
{
    if (m_stepperMotors == stepperMotors)
        return;
    m_stepperMotors = stepperMotors;
    emit stepperMotorsChanged();
}

void QKlipperPrinter::setStepperMotor(const QString &name, QKlipperStepperMotor *motor)
{
    if(m_stepperMotors.contains(name))
    {
        if(m_stepperMotors[name] == motor)
            return;

        QKlipperStepperMotor *current = m_stepperMotors[name];
        m_stepperMotors.remove(name);

        current->deleteLater();
    }

    m_stepperMotors[name] = motor;
    emit stepperMotorsChanged();
}

QKlipperProbeData QKlipperPrinter::probeData() const
{
    return m_probeData;
}

void QKlipperPrinter::setProbeData(const QKlipperProbeData &probeData)
{
    if (m_probeData == probeData)
        return;

    m_probeData = probeData;
    emit probeDataChanged();
}

QKlipperEndstopStatus QKlipperPrinter::endstopStatus() const
{
    return m_endstopStatus;
}

void QKlipperPrinter::pause()
{
    if(!m_console->isConnected())
    {
        qDebug() << "Console not connected";
        return;
    }

    QKlipperError error;
    m_console->printerPrintPause(&error);

    if(error.type() != QKlipperError::NoError)
        qDebug() << "Error pausing print." << error.type() << error.errorString();
}

void QKlipperPrinter::resume()
{
    if(!m_console->isConnected())
    {
        qDebug() << "Console not connected";
        return;
    }

    QKlipperError error;
    m_console->printerPrintResume(&error);

    if(error.type() != QKlipperError::NoError)
        qDebug() << "Error resuming print." << error.type() << error.errorString();
}

void QKlipperPrinter::cancel()
{
    if(!m_console->isConnected())
    {
        qDebug() << "Console not connected";
        return;
    }

    QKlipperError error;
    m_console->printerPrintCancel(&error);

    if(error.type() != QKlipperError::NoError)
        qDebug() << "Error cancelling print." << error.type() << error.errorString();
}

void QKlipperPrinter::start(QKlipperFile *file)
{
    if(!m_console->isConnected())
    {
        qDebug() << "Console not connected";
        return;
    }

    QKlipperError error;
    m_console->printerPrintStart(file, &error);

    if(error.type() != QKlipperError::NoError)
        qDebug() << "Error cancelling print." << error.type() << error.errorString();
}

qreal QKlipperPrinter::watts()
{
    return m_toolhead->watts();
}

void QKlipperPrinter::setEndstopStatus(const QKlipperEndstopStatus &endstopStatus)
{
    if (m_endstopStatus == endstopStatus)
        return;

    m_endstopStatus = endstopStatus;
    emit endstopStatusChanged();
}

bool QKlipperPrinter::hasChamber() const
{
    return m_hasChamber;
}

void QKlipperPrinter::setHasChamber(bool hasChamber)
{
    if (m_hasChamber == hasChamber)
        return;

    m_hasChamber = hasChamber;
    emit hasChamberChanged();
}
