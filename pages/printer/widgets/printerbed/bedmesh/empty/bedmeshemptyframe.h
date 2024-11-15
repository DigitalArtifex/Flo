#ifndef BEDMESHEMPTYFRAME_H
#define BEDMESHEMPTYFRAME_H

#include <QFrame>
#include <QKlipper/qklipper.h>

namespace Ui {
class BedMeshEmptyFrame;
}

class BedMeshEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit BedMeshEmptyFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~BedMeshEmptyFrame();

    void setupIcons();

public slots:
    void setStyleSheet(const QString &styleSheet);

protected slots:
    void onToolheadHomingChanged();

private slots:
    void on_homeButton_clicked();

    void on_calibrateButton_clicked();

private:
    Ui::BedMeshEmptyFrame *ui;
    QKlipperPrintBed *m_printerBed = nullptr;
};

#endif // BEDMESHEMPTYFRAME_H
