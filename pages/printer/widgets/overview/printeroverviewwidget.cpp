#include "printeroverviewwidget.h"
#include "pages/printer/widgets/overview/printeroverviewheaterframe.h"
#include "ui_printeroverviewwidget.h"
#include <qstyle.h>

PrinterOverviewWidget::PrinterOverviewWidget(QKlipperPrinter *printer, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterOverviewWidget)
{
    ui->setupUi(this);
    m_printer = printer;

    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_printer->parent());

    if(instance)
    {
        connect(instance, SIGNAL(connected(QKlipperInstance*)), this, SLOT(onPrinterConnected(QKlipperInstance*)));
        connect(instance, SIGNAL(disconnected(QKlipperInstance*)), this, SLOT(onPrinterDisconnected(QKlipperInstance*)));
        connect(instance->printer(), SIGNAL(statusMessageChanged()), this, SLOT(onPrinterStatusChanged()));
    }

    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    ui->temperatureGraph->data()->setGridMainColor("#666666");
    ui->temperatureGraph->data()->setGridSubColor("#444444");
    ui->temperatureGraph->data()->setAxisYMainColor("#ccccff");
    ui->temperatureGraph->data()->setAxisYSubColor("#eeeeff");
    ui->temperatureGraph->data()->setAxisXMainColor("#ccccff");
    ui->temperatureGraph->data()->setAxisXSubColor("#eeeeff");
    ui->temperatureGraph->data()->setDateMinimum(QDateTime::currentDateTime().addSecs(0).addSecs(currentTime.offsetFromUtc()));
    ui->temperatureGraph->data()->setDateMaximum(QDateTime::currentDateTime().addSecs(10).addSecs(currentTime.offsetFromUtc()));

    ui->powerGraph->data()->setGridMainColor("#666666");
    ui->powerGraph->data()->setGridSubColor("#444444");
    ui->powerGraph->data()->setAxisYMainColor("#ccccff");
    ui->powerGraph->data()->setAxisYSubColor("#eeeeff");
    ui->powerGraph->data()->setAxisXMainColor("#ccccff");
    ui->powerGraph->data()->setAxisXSubColor("#eeeeff");
    ui->powerGraph->data()->setDateMinimum(QDateTime::currentDateTime().addSecs(0).addSecs(currentTime.offsetFromUtc()));
    ui->powerGraph->data()->setDateMaximum(QDateTime::currentDateTime().addSecs(10).addSecs(currentTime.offsetFromUtc()));

    ui->heatersPanel->setTitle("Heaters");
    ui->heatersPanel->setCentralWidget(ui->heaterPanelContentWidget);
    ui->heatersPanel->setContentsMargins(0,0,0,0);

    ui->powerGraphCard->setTitle("Power");
    ui->powerGraphCard->setCentralWidget(ui->powerGraphContentWidget);
    ui->powerGraphCard->setContentsMargins(0,0,0,0);

    ui->statusCard->setCentralWidget(ui->statusContentsWidget);

    ui->temperatureGraphCard->setTitle("Thermals");
    ui->temperatureGraphCard->setCentralWidget(ui->temperatureGraphContentWidget);
    ui->temperatureGraphCard->setContentsMargins(0,0,0,0);
    //ui->temperatureGraphCard->setProperty("class", property("class").toStringList() += "Widget");
    ui->powerGraphCard->setProperty("class", property("class").toStringList() += "Widget");
    ui->overviewPanel->setProperty("class", property("class").toStringList() += "Widget");
    ui->heatersPanel->setProperty("class", property("class").toStringList() += "Widget");
    setProperty("class", property("class").toStringList() += "SubWidget");

    setIcons();

    style()->polish(this);
}

PrinterOverviewWidget::~PrinterOverviewWidget()
{
    delete ui;
}

void PrinterOverviewWidget::onPrinterStatusChanged()
{
    if(m_printer->status() == QKlipperPrinter::Error)
        ui->restartFirmwareButton->show();
    else
        ui->restartFirmwareButton->hide();

    QStringList splitMessage = m_printer->statusMessage().split('\n', Qt::SkipEmptyParts);

    if(splitMessage.count() == 1)
    {
        ui->statusMessageLabel->setText(splitMessage.at(0));
        ui->statusCard->setTitle(QString("Printer Status"));
    }
    else if(splitMessage.count() == 2)
    {
        QString status = splitMessage.takeFirst();
        QString message = splitMessage.join(' ');
        message = QString("<h4>%1</h4>\n\n<p>%2</p>").arg(status, message);

        ui->statusCard->setTitle(QString("Printer Status"));
        ui->statusMessageLabel->setText(message);
    }
    else if(splitMessage.count() >= 3)
    {
        QString title = splitMessage.takeLast();
        QString status = splitMessage.takeFirst();
        QString message = splitMessage.join(' ');
        message = QString("<h4>%1</h4>\n\n<p>%2</p>").arg(status, message);

        ui->statusCard->setTitle(QString("Printer Status (%1)").arg(title));
        ui->statusMessageLabel->setText(message);
    }
}

void PrinterOverviewWidget::onUpdateTimerTimeout()
{
    if(m_printer)
    {
        // Power
        QDateTime currentTime = QDateTime::currentDateTime();
        currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

        qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
        qreal timeDiff = ui->powerGraph->dateMinimum().toSecsSinceEpoch() - timeNow;

        ui->powerGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-120).addSecs(currentTime.offsetFromUtc()));
        ui->temperatureGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-120).addSecs(currentTime.offsetFromUtc()));

        for(QKlipperExtruder *extruder : m_printer->toolhead()->extruderMap())
        {
            ui->temperatureGraph->data()->append(extruder->name(), QPointF(currentTime.toMSecsSinceEpoch(), extruder->temperature()));
            ui->powerGraph->data()->append(extruder->name(), QPointF(currentTime.toMSecsSinceEpoch(), extruder->watts()));
        }

        ui->temperatureGraph->data()->append("bed", QPointF(currentTime.toMSecsSinceEpoch(), m_printer->bed()->temperature()));
        ui->powerGraph->data()->append("bed", QPointF(currentTime.toMSecsSinceEpoch(), m_printer->bed()->watts()));

        for(QKlipperHeater *heater : m_printer->heaters())
        {
            ui->temperatureGraph->data()->append(heater->name(), QPointF(currentTime.toMSecsSinceEpoch(), heater->temperature()));
            ui->powerGraph->data()->append(heater->name(), QPointF(currentTime.toMSecsSinceEpoch(), heater->watts()));
        }

        ui->powerGraph->data()->append("power", QPointF(currentTime.toMSecsSinceEpoch(), m_printer->watts()));
        ui->currentPowerGauge->setMaximum(m_printer->maximumWatts());
        ui->currentPowerGauge->setValue(m_printer->watts());
        ui->currentWattsLabel->setText(QString("<h3>%1w</h3>").arg(QString::number(m_printer->watts(), 'f', 2)));

        calculateTotalWatts();
    }
}

void PrinterOverviewWidget::onPrinterConnected(QKlipperInstance *instance)
{
    Q_UNUSED(instance)

    if(!m_updateTimer)
    {
        m_updateTimer = new QTimer(this);
        m_updateTimer->setInterval(500);
        m_updateTimer->start();

        connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateTimerTimeout()));
    }

    clearHeaterLabels();

    for(QKlipperExtruder *extruder : m_printer->toolhead()->extruderMap())
    {
        PrinterOverviewHeaterFrame *extruderFrame = new PrinterOverviewHeaterFrame(extruder, this);
        extruderFrame->setProperty("class", property("class").toStringList() += "SubWidget");
        ui->heaterDisplayWidget->layout()->addWidget(extruderFrame);
    }

    PrinterOverviewHeaterFrame *bedFrame = new PrinterOverviewHeaterFrame(m_printer->bed(), this);
    bedFrame->setProperty("class", property("class").toStringList() += "SubWidget");
    ui->heaterDisplayWidget->layout()->addWidget(bedFrame);

    for(QKlipperHeater *heater : m_printer->heaters())
    {
        PrinterOverviewHeaterFrame *heaterFrame = new PrinterOverviewHeaterFrame(heater, this);
        heaterFrame->setProperty("class", property("class").toStringList() += "SubWidget");
        ui->heaterDisplayWidget->layout()->addWidget(heaterFrame);
    }
}

void PrinterOverviewWidget::onPrinterDisconnected(QKlipperInstance *instance)
{
    Q_UNUSED(instance)

    if(m_updateTimer)
    {
        delete m_updateTimer;
        m_updateTimer = nullptr;
    }
}

// CalculateTotalWatts does 2 things:
// 1) buffers data points for 1 minute, then adds the average to the log
// 2) calculates the average peak and total Kwh for the log period
// -- log period is set to Month_Year, allowing a monthly average
void PrinterOverviewWidget::calculateTotalWatts()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal currentSecs = currentTime.toSecsSinceEpoch();
    qreal lastSaveSecs = m_lastSave.toSecsSinceEpoch();

    //If it hasn't been 1 minute since our last update, save the entry to the buffer
    if((currentSecs - lastSaveSecs) < 60)
    {
        m_saveBuffer += m_printer->watts();
        return;
    }
    //Wait until we have 10 minutes of data before adding it to the data log
    else if(m_lastSave == QDateTime::fromSecsSinceEpoch(0))
        m_saveBuffer += m_printer->watts();

    //Data is stored in AppDataLocation/<printer_id>/<month>_<year>.log
    QDir directory(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + m_printer->id());

    if(!directory.exists())
    {
        if(!directory.mkpath(directory.absolutePath()))
            qDebug() << "Could not create" << directory.absolutePath();
    }

    QString fileName = QString("%1%2%3_%4.log")
                        .arg(directory.absolutePath())
                        .arg(QDir::separator())
                        .arg(QDateTime::currentDateTime().date().month())
                        .arg(QDateTime::currentDateTime().date().year());

    QFile wattsFile(fileName);

    if(!wattsFile.open(QFile::ReadWrite | QFile::Append))
    {
        qDebug() << "Could not open file" << fileName;
        qDebug() << "-- Open Error: " << wattsFile.error();

        return;
    }

    //Wait until we have 1 minute of data before adding it to the data log
    if(m_lastSave != QDateTime::fromSecsSinceEpoch(0))
    {
        //save the average of the last 10 minutes
        qreal bufferedAverage = 0;
        qreal bufferedCount = m_saveBuffer.count();

        while(m_saveBuffer.count() > 0)
            bufferedAverage += m_saveBuffer.dequeue();

        bufferedAverage /= bufferedCount;

        QString latestEntry = QString("%1:%2\n").arg(currentTime.toMSecsSinceEpoch()).arg(bufferedAverage);
        wattsFile.write(latestEntry.toUtf8());
    }

    qreal entries = 0;
    qreal totalWatts = 0.0;
    qreal averageWatts = 0.0;

    QDateTime lastDateTime = QDateTime::fromMSecsSinceEpoch(0);
    qint8 lastHour = 0;
    qint64 hourlyEntries = 0;
    QList<qreal> hourlyAverages;

    wattsFile.seek(0);

    qreal wattHoursPerMinute = 1.0 / 60.0;

    while(wattsFile.bytesAvailable() > 0)
    {
        QString currentLine = wattsFile.readLine();
        QStringList splitLine = currentLine.split(':', Qt::SkipEmptyParts);

        if(splitLine.count() != 2)
            continue;

        qreal timestamp = 0;
        bool timeConverted = false;

        timestamp = splitLine[0].toDouble(&timeConverted);

        if(!timeConverted)
        {
            qDebug() << "Could not convert time";
            continue;
        }

        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(timestamp);

        //only estimate to an hourly average for now
        if(dateTime.time().hour() != lastHour)
        {
            lastHour = dateTime.time().hour();

            if(hourlyEntries > 0)
                hourlyAverages[hourlyAverages.count() - 1] /= hourlyEntries;

            hourlyEntries = 0;
            hourlyAverages.append(0.0);
        }

        qreal watts = 0;
        bool wattsConverted = false;

        watts = splitLine[1].toDouble(&wattsConverted);

        if(!wattsConverted)
        {
            qDebug() << "Could not convert watts";
            continue;
        }

        ++entries;
        averageWatts += watts;

        if(watts > 0.00)
            totalWatts += (watts * wattHoursPerMinute);
    }

    wattsFile.close();

    if(entries > 0)
    {
        averageWatts /= entries;
        totalWatts /= 1000;

        ui->averageWattsLabel->setText(QString("<h3>%1w</h3>").arg(QString::number(averageWatts, 'f', 2)));
        ui->totalWattsLabel->setText(QString("<h3>%1 Kwh</h3>").arg(QString::number(totalWatts, 'f', 2)));
    }

    m_lastSave = currentTime;
}

void PrinterOverviewWidget::clearHeaterLabels()
{
    QList<PrinterOverviewHeaterFrame*> frames = ui->heaterDisplayWidget->findChildren<PrinterOverviewHeaterFrame*>();

    while(frames.count() > 0)
    {
        PrinterOverviewHeaterFrame *frame = frames.takeAt(0);
        ui->heaterDisplayWidget->layout()->removeWidget(frame);

        delete frame;
    }
}

void PrinterOverviewWidget::setIcons()
{
    ui->heatersPanel->setIcon(
        Settings::getThemeIcon(
            "preheat",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );
    ui->powerGraphCard->setIcon(
        Settings::getThemeIcon(
            "voltage",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );
    ui->temperatureGraphCard->setIcon(
        Settings::getThemeIcon(
            "temperature",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );
    ui->statusCard->setIcon(
        Settings::getThemeIcon(
            "printer",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );
}

void PrinterOverviewWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();

    QFrame::changeEvent(event);
}

void PrinterOverviewWidget::on_restartFirmwareButton_clicked()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_printer->parent());

    if(instance)
        instance->system()->restart();
}
