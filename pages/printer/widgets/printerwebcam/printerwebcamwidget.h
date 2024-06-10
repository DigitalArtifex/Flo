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

#include <QResizeEvent>

#include "empty/emptyprinterwebcamframe.h"

#include "../../../../types/printer.h"
#include "../../../../types/system.h"
#include "../../../../ui/qwebcamframe.h"

class PrinterWebcamWidget : public QFrame
{
    Q_OBJECT
public:
    PrinterWebcamWidget(Printer *printer, QWidget *parent = nullptr);

    virtual void setStyleSheet(QString &styleSheet);

protected:
    void setupUi();
    void setupUiClasses();
    void setIcons();

protected slots:
    void on_printer_update(Printer *printer);

    virtual void resizeEvent(QResizeEvent *event);

private:
    Printer *_printer = nullptr;

    QWebcamFrame *_webcamFrame = nullptr;
    QWebcamFrame *_webcamFrame_1 = nullptr;
    QWebcamFrame *_webcamFrame_2 = nullptr;
    QWebcamFrame *_webcamFrame_3 = nullptr;

    qint32 _webcamIndex = -1;

    EmptyPrinterWebcamFrame *_emptyFrame = nullptr;

    QGridLayout *_layout = nullptr;
};

#endif // PRINTERWEBCAMWIDGET_H
