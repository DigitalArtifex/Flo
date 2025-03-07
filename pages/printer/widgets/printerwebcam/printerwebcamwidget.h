#ifndef PRINTERWEBCAMWIDGET_H
#define PRINTERWEBCAMWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include <QUrl>
#include <QStyle>
#include <QTimer>

#include <QResizeEvent>

#include "empty/emptyprinterwebcamframe.h"

#include <QKlipper/qklipper.h>
#include "ui/QWebcamWidget/qwebcamwidget.h"

class PrinterWebcamWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(bool isAnimating READ animating WRITE setAnimating NOTIFY animatingChanged FINAL)
public:
    PrinterWebcamWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterWebcamWidget();

    bool animating() const;

public slots:
    void setupIcons();
    void setAnimating(bool animating);

    void setStyleSheet(const QString &styleSheet);
    void play();
    void stop();

signals:
    void animatingChanged(bool);

protected:
    void setupUi();
    void setupUiClasses();

    void setupWebcam0();
    void setupWebcam1();
    void setupWebcam2();
    void setupWebcam3();

    virtual void resizeEvent(QResizeEvent *event);

protected slots:
    void onSystemWebcamsChanged();
    void onInstanceOnline(QKlipperInstance *instance);
    void onInstanceOffline(QKlipperInstance *instance);
    void onWebcamThumbnailUpdate();

private:
    QKlipperInstance *m_instance = nullptr;

    QWebcamWidget *m_webcamFrame = nullptr;
    QWebcamWidget *m_webcamFrame_1 = nullptr;
    QWebcamWidget *m_webcamFrame_2 = nullptr;
    QWebcamWidget *m_webcamFrame_3 = nullptr;

    qint32 m_webcamIndex = -1;

    EmptyPrinterWebcamFrame *m_emptyFrame = nullptr;

    QGridLayout *m_layout = nullptr;

    QTimer *m_thumbnailTimer = nullptr;
    bool m_animating = false;

    QString m_webcamUrl;
    QString m_webcamUrl_1;
    QString m_webcamUrl_2;
    QString m_webcamUrl_3;
};

#endif // PRINTERWEBCAMWIDGET_H
