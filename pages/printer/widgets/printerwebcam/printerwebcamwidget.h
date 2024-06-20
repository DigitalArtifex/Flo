#ifndef PRINTERWEBCAMWIDGET_H
#define PRINTERWEBCAMWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QPushButton>
#include <QUrl>
#include <QStyle>
#include <QTimer>

#include <QResizeEvent>

#include "empty/emptyprinterwebcamframe.h"

#include "../../../../types/printer.h"
#include "../../../../types/system.h"
#include "../../../../ui/QWebcamWidget/qwebcamwidget.h"

class PrinterWebcamWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(bool isAnimating READ animating WRITE setAnimating NOTIFY animatingChanged FINAL)
public:
    PrinterWebcamWidget(Printer *printer, QWidget *parent = nullptr);
    ~PrinterWebcamWidget();

    virtual void setStyleSheet(QString &styleSheet);

    bool animating() const;
    void setAnimating(bool animating);

signals:
    void animatingChanged(bool);

protected:
    void setupUi();
    void setupUiClasses();
    void setIcons();

    void setupWebcam0();
    void setupWebcam1();
    void setupWebcam2();
    void setupWebcam3();

protected slots:
    void on_printer_update(Printer *printer);

    virtual void resizeEvent(QResizeEvent *event);

private:
    Printer *_printer = nullptr;

    QWebcamWidget *_webcamFrame = nullptr;
    QWebcamWidget *_webcamFrame_1 = nullptr;
    QWebcamWidget *_webcamFrame_2 = nullptr;
    QWebcamWidget *_webcamFrame_3 = nullptr;

    qint32 _webcamIndex = -1;

    EmptyPrinterWebcamFrame *_emptyFrame = nullptr;

    QGridLayout *_layout = nullptr;

    QTimer *_delayTimer = nullptr;
    bool _animating = false;

    QString _webcamUrl;
    QString _webcamUrl_1;
    QString _webcamUrl_2;
    QString _webcamUrl_3;
};

#endif // PRINTERWEBCAMWIDGET_H
