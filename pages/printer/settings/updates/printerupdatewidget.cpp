#include "printerupdatewidget.h"

PrinterUpdateWidget::PrinterUpdateWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{

}

PrinterUpdateWidget::~PrinterUpdateWidget()
{
}

QKlipperUpdateState *PrinterUpdateWidget::updateState() const
{
    return m_updateState;
}

void PrinterUpdateWidget::setUpdateState(QKlipperUpdateState *newUpdateState)
{
    clear();

    m_updateState = newUpdateState;
    QStringList keys = m_updateState->packages().keys();
    keys.sort(Qt::CaseInsensitive);

    foreach(QString key, keys)
    {
        QList<QKlipperUpdatePackage> states = m_updateState->packages().values(key);

        foreach(QKlipperUpdatePackage state, states)
        {
            PrinterUpdateItem *item = new PrinterUpdateItem(key, state, this);
            connect(item, SIGNAL(updateRequested(PrinterUpdateItem*)), this, SLOT(itemUpdateRequestedEvent(PrinterUpdateItem*)));

            setAnimationSlide(item);
            item->setDuration(150);

            addItem(item);
        }
    }
}

void PrinterUpdateWidget::itemUpdateRequestedEvent(PrinterUpdateItem *item)
{
    emit itemUpdateRequested(item);
}
