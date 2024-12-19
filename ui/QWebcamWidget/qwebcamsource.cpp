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
        delete m_signalTimer;
    }

    if(m_player)
    {
        m_player->stop();
        m_player->setVideoSink(nullptr);
        delete m_player;
    }

    if(m_webcamSink)
        delete m_webcamSink;
}

void QWebcamSource::play()
{
    createSink();

    if(m_player && !m_player->isPlaying() && !m_source.isEmpty())
    {
        m_player->setSource(m_source);

        if(m_state != Connecting)
        {
            setFirstFrameReceived(false);
            m_connectionRetryCount = 0;
        }

        startSignalTimer();

        setState(Connecting);
        m_player->play();
    }
}

void QWebcamSource::pause()
{
    createSink();

    if(m_player && m_player->isPlaying())
    {
        m_player->pause();

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
    if(m_firstFrameReceived)
        m_firstFrameReceived = false;
    else if(m_state == Connecting)
    {
        if(++m_connectionRetryCount > m_connectionRetries)
        {
            setState(Timeout);
            stop();
            m_signalTimer->stop();

            return;
        }
    }

    stop();
    setState(Connecting);
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
        setFirstFrameReceived(true);

        setFrame(frame);
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

bool QWebcamSource::firstFrameReceived() const
{
    return m_firstFrameReceived;
}

void QWebcamSource::setFirstFrameReceived(bool firstFrameReceived)
{
    if(m_firstFrameReceived == firstFrameReceived)
        return;

    m_firstFrameReceived = firstFrameReceived;

    if(m_state == Connecting || m_state == InvalidFrame)
    {
        m_connectionRetryCount = 0;
        setState(Connected);
    }
}

quint64 QWebcamSource::connectionRetries() const
{
    return m_connectionRetries;
}

void QWebcamSource::setConnectionRetries(quint64 connectionRetries)
{
    if (m_connectionRetries == connectionRetries)
        return;
    m_connectionRetries = connectionRetries;
    emit connectionRetriesChanged();
}
