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
    Printer *m_printer = nullptr;

    QWebcamWidget *m_webcamFrame = nullptr;
    QWebcamWidget *m_webcamFrame_1 = nullptr;
    QWebcamWidget *m_webcamFrame_2 = nullptr;
    QWebcamWidget *m_webcamFrame_3 = nullptr;

    qint32 m_webcamIndex = -1;

    EmptyPrinterWebcamFrame *m_emptyFrame = nullptr;

    QGridLayout *m_layout = nullptr;

    QTimer *m_delayTimer = nullptr;
    bool m_animating = false;

    QString m_webcamUrl;
    QString m_webcamUrl_1;
    QString m_webcamUrl_2;
    QString m_webcamUrl_3;
};

#endif // PRINTERWEBCAMWIDGET_H
