#ifndef PROBEDMESHEMPTYFRAME_H
#define PROBEDMESHEMPTYFRAME_H

#include <QFrame>
#include <QKlipper/qklipper.h>

namespace Ui {
class ProbedMeshEmptyFrame;
}

class ProbedMeshEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ProbedMeshEmptyFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~ProbedMeshEmptyFrame();

    void setupIcons();

public slots:
    void setStyleSheet(const QString &styleSheet);

protected slots:
    void onToolheadHomingChanged();

private slots:
    void on_homeButton_clicked();

    void on_calibrateButton_clicked();

private:
    Ui::ProbedMeshEmptyFrame *ui;
    QKlipperPrintBed *m_printerBed = nullptr;
};

#endif // PROBEDMESHEMPTYFRAME_H
