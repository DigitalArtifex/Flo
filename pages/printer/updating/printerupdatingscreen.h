#ifndef PRINTERUPDATINGSCREEN_H
#define PRINTERUPDATINGSCREEN_H

#include <QFrame>
#include <QKlipper/QKlipperSystem/qklipperupdatemanager.h>

namespace Ui {
class PrinterUpdatingScreen;
}

class PrinterUpdatingScreen : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterUpdatingScreen(QKlipperUpdateManager *manager, QWidget *parent = nullptr);
    ~PrinterUpdatingScreen();

private slots:
    void onUpdateSystemStateTextChanged();

private:
    Ui::PrinterUpdatingScreen *ui;

    QKlipperUpdateManager *m_manager = nullptr;
};

#endif // PRINTERUPDATINGSCREEN_H
