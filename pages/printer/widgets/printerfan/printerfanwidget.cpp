#include "printerfanwidget.h"
#include "flo/settings.h"

PrinterFanWidget::PrinterFanWidget(QKlipperPrinter *printer, QWidget *parent)
    : CardWidget(CardType::Widget, parent)
{
    m_printer = printer;

    setTitle("Fans");
    setupUi();
    setupIcons();
    onPrinterFansChanged();

    connect(m_printer, SIGNAL(fansChanged()), this, SLOT(onPrinterFansChanged()));
}

void PrinterFanWidget::onPrinterFansChanged()
{
    clearLayout();

    QMap<QString, QKlipperFan*> printerFans = m_printer->fans();
    QStringList printerFanNames = printerFans.keys();

    for(QString &name : printerFanNames)
    {
        PrinterFanItem *fanItem = new PrinterFanItem(printerFans[name], m_centralWidget);
        m_centralLayout->addWidget(fanItem);
    }
}

void PrinterFanWidget::setPrinter(QKlipperPrinter *printer)
{
    if(m_printer)
        disconnect(m_printer, SIGNAL(fansChanged()), this, SLOT(onPrinterFansChanged()));

    m_printer = printer;

    onPrinterFansChanged();
    connect(m_printer, SIGNAL(fansChanged()), this, SLOT(onPrinterFansChanged()));
}

void PrinterFanWidget::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);

    setCentralWidget(m_centralWidget);
}

void PrinterFanWidget::setupIcons()
{
    setIcon(Settings::getThemeIcon("fan-on"));
}

void PrinterFanWidget::clearLayout()
{
    QList<PrinterFanItem*> items = m_centralWidget->findChildren<PrinterFanItem*>();

    for(PrinterFanItem* item : items)
    {
        m_centralLayout->removeWidget(item);
        delete item;
    }
}

void PrinterFanWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        setupIcons();
    }

    CardWidget::changeEvent(event);
}
