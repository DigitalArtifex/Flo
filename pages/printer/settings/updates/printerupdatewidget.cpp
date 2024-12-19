#include "printerupdatewidget.h"

PrinterUpdateWidget::PrinterUpdateWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{

}

PrinterUpdateWidget::~PrinterUpdateWidget()
{
}

QKlipperUpdateManager *PrinterUpdateWidget::updateState() const
{
    return m_updateState;
}

void PrinterUpdateWidget::setUpdateState(QKlipperUpdateManager *newUpdateState)
{
    clear();

    m_updateState = newUpdateState;
    QStringList keys = m_updateState->packages().keys();
    keys.sort(Qt::CaseInsensitive);

    for(QString &key : keys)
    {
        QKlipperUpdatePackage state = m_updateState->packages().value(key);

        PrinterUpdateItem *item = new PrinterUpdateItem(key, state, this);
        connect(item, SIGNAL(updateRequested(PrinterUpdateItem*)), this, SLOT(itemUpdateRequestedEvent(PrinterUpdateItem*)));

        setAnimationSlide(item);
        item->setDuration(150);

        addItem(item);
    }
}

void PrinterUpdateWidget::itemUpdateRequestedEvent(PrinterUpdateItem *item)
{
    emit itemUpdateRequested(item);
}
