#include "qwebcamsource.h"

QWebcamSource::QWebcamSource(int timeout, QObject *parent)
    : QObject{parent}
{
    m_signalTimer = new QTimer(this);
    m_signalTimer->setInterval(timeout);
    connect(m_signalTimer, SIGNAL(timeout()), this, SLOT(onSignalTimeout()));
}

QWebcamSource::~QWebcamSource()
{
    if(m_signalTimer)
    {
        m_signalTimer->stop();
        m_signalTimer->deleteLater();
    }

    if(m_player)
    {
        m_player->stop();
        m_player->setVideoSink(nullptr);
        m_player->deleteLater();
    }

    if(m_webcamSink)
    {
        m_webcamSink->deleteLater();
    }
}

void QWebcamSource::play()
{
    createSink();

    if(m_player && !m_player->isPlaying() && !m_source.isEmpty())
    {
        m_player->setSource(m_source);

        setState(Connecting);
        m_player->play();
    }
}

void QWebcamSource::pause()
{
    createSink();

    if(m_player && m_player->isPlaying())
    {
        m_player->stop();

        setState(Paused);
    }
}

void QWebcamSource::stop()
{
    createSink();

    if(m_player && m_player->isPlaying())
    {
        m_player->stop();

        setState(NoConnection);
    }
}

void QWebcamSource::onSignalTimeout()
{
    setState(NoConnection);
    stop();
    play();
}

void QWebcamSource::createSink()
{
    if(!m_player)
    {
        m_player = new QMediaPlayer();
        m_webcamSink = new QVideoSink();
        m_player->setVideoSink(m_webcamSink);

        connect(m_webcamSink, SIGNAL(videoFrameChanged(QVideoFrame)), this, SLOT(videoFrameChangeEvent(QVideoFrame)));
    }
}

void QWebcamSource::stopSignalTimer()
{
    if(m_signalTimer && m_signalTimer->isActive())
        m_signalTimer->stop();
}

void QWebcamSource::startSignalTimer()
{
    if(m_signalTimer && !m_signalTimer->isActive())
        m_signalTimer->start();
}

void QWebcamSource::resetSignalTimer()
{
    stopSignalTimer();
    startSignalTimer();
}

QUrl QWebcamSource::source() const
{
    return m_source;
}

void QWebcamSource::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    createSink();

    if(m_player)
    {
        if(m_player->isPlaying())
        {
            m_player->stop();
            m_player->setSource(source);
            m_player->play();
        }
        else
            m_player->setSource(source);
    }

    m_source = source;
    emit sourceChanged();
}

void QWebcamSource::videoFrameChangeEvent(QVideoFrame frame)
{
    frame.setSubtitleText(QDateTime::currentDateTime().toString());

    if(frame.isValid())
    {
        resetSignalTimer();

        setFrame(frame);

        if(m_state == Connecting || m_state == InvalidFrame)
            setState(Connected);
    }
    else
    {
        if(m_state == Connected)
        {
            QImage lastImage = m_frame.toImage().convertToFormat(QImage::Format_Grayscale16);

            QVideoFrame lastFrame(lastImage);
            setFrame(lastFrame);

            setState(InvalidFrame);
        }
    }
}

QWebcamSource::State QWebcamSource::state() const
{
    return m_state;
}

void QWebcamSource::setState(State state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged();
}

QVideoFrame QWebcamSource::frame() const
{
    return m_frame;
}

void QWebcamSource::setFrame(const QVideoFrame &frame)
{
    if (m_frame == frame)
        return;

    m_frame = frame;
    emit frameChanged(m_frame);
}
