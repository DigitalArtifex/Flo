#include "gcodemacrodialog.h"

GCodeMacroDialog::GCodeMacroDialog(QKlipperServer *server, QWidget *parent)
    : Dialog{parent}
{
    m_server = server;
    setupUi();

    onServerGcodeMacrosChanged();

    connect(m_server, SIGNAL(gcodeMacrosChanged()), this, SLOT(onServerGcodeMacrosChanged()));
}

void GCodeMacroDialog::onServerGcodeMacrosChanged()
{
    m_macroTable->clear();

    auto macros = m_server->gcodeMacros();

    for(const QKlipperGCodeMacro &macro : macros)
    {
        int row = m_macroTable->rowCount();

        m_macroTable->insertRow(row);
        m_macroTable->setRowHeight(row, 32);

        QTableWidgetItem *nameItem = new QTableWidgetItem();
        nameItem->setText(macro.macro);
        m_macroTable->setItem(row, 0, nameItem);

        QTableWidgetItem *descriptionItem = new QTableWidgetItem();
        descriptionItem->setText(macro.description);
        m_macroTable->setItem(row, 1, descriptionItem);
    }
}

void GCodeMacroDialog::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);

    m_macroTable = new QTableWidget(this);
    m_macroTable->setColumnCount(2);
    m_layout->addWidget(m_macroTable);
}

void GCodeMacroDialog::resizeEvent(QResizeEvent *event)
{
    Dialog::resizeEvent(event);
    m_macroTable->setColumnWidth(0, 200);
    m_macroTable->setColumnWidth(1, event->size().width() - 200);
}
