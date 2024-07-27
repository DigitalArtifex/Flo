#include "printerupdatewidget.h"

PrinterUpdateWidget::PrinterUpdateWidget(QWidget *parent)
    : QAnimatedListWidget(parent)
{

}

PrinterUpdateWidget::~PrinterUpdateWidget()
{
    clear();
}

System::UpdateState PrinterUpdateWidget::updateState() const
{
    return m_updateState;
}

void PrinterUpdateWidget::setUpdateState(const System::UpdateState &newUpdateState)
{
    clear();

    m_updateState = newUpdateState;
    QStringList keys = m_updateState.packageStates.keys();
    keys.sort(Qt::CaseInsensitive);

    foreach(QString key, keys)
    {
        QList<System::UpdateState::PackageState> states = m_updateState.packageStates.values(key);

        foreach(System::UpdateState::PackageState state, states)
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
