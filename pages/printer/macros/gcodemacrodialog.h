#ifndef GCODEMACRODIALOG_H
#define GCODEMACRODIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QResizeEvent>

#include <common/dialog/dialog.h>
#include <QKlipper/qklipper.h>

class GCodeMacroDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit GCodeMacroDialog(QKlipperServer *server, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onServerGcodeMacrosChanged();

    protected:
        void setupUi();
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QGridLayout *m_layout = nullptr;
        QTableWidget *m_macroTable = nullptr;
        QKlipperServer *m_server = nullptr;
};

#endif // GCODEMACRODIALOG_H
