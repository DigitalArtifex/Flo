#include "dialog.h"
#include "system/settings.h"

Dialog::Dialog(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    if(Settings::get("theme-frameless-dialogs").toBool())
        setWindowFlag(Qt::FramelessWindowHint);

    setWindowFlag(Qt::Popup);

    setProperty("class", QString("Dialog"));
}

Dialog::~Dialog()
{
    if(m_loadingFrameLayout)
        delete m_loadingFrameLayout;

    if(m_loadingFrame)
        delete m_loadingFrame;
}

void Dialog::showLoadingScreen()
{
    if(!m_loadingFrame)
    {
        //create the loading frame
        m_loadingFrame = new QFrame(this);
        m_loadingFrame->setGeometry(0,0,size().width(), size().height());

        //set the layout
        m_loadingFrameLayout = new QVBoxLayout(m_loadingFrame);
        m_loadingFrame->setLayout(m_loadingFrameLayout);

        //add top spacer
        m_loadingFrameTopSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_loadingFrameLayout->addSpacerItem(m_loadingFrameTopSpacer);

        //setup loading gif
        m_loadingFrameMovie = new QMovie(":/images/loading_widget.gif");

        //setup the label for the gif
        m_loadingFrameIcon = new QLabel(m_loadingFrame);
        m_loadingFrameIcon->setScaledContents(true);
        m_loadingFrameIcon->setAlignment(Qt::AlignCenter);
        m_loadingFrameIcon->setFixedSize(256, 256);
        m_loadingFrameIcon->setMovie(m_loadingFrameMovie);
        m_loadingFrameLayout->addWidget(m_loadingFrameIcon);

        //setup the label for text information
        m_loadingFrameText = new QLabel(m_loadingFrame);
        m_loadingFrameText->setAlignment(Qt::AlignHCenter);
        m_loadingFrameText->setText(QString("Loading metadata..."));
        m_loadingFrameLayout->addWidget(m_loadingFrameText);

        //add bottom spacer
        m_loadingFrameBottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_loadingFrameLayout->addSpacerItem(m_loadingFrameBottomSpacer);

        //start the movie
        m_loadingFrameMovie->start();

        //raise and show the frame
        m_loadingFrame->show();
        m_loadingFrame->raise();

        m_loadingFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "LoadingOverlayFrame"));
        m_loadingFrameText->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DialogHeading"));
        style()->polish(m_loadingFrame);
    }
}

void Dialog::hideLoadingScreen()
{
    if(m_loadingFrame)
    {
        if(m_loadingFrameLayout)
        {
            delete m_loadingFrameLayout;
            m_loadingFrameLayout = nullptr;
        }

        delete m_loadingFrame;
        m_loadingFrame = nullptr;
    }
}

bool Dialog::isLoadingScreenVisible()
{
    return m_loadingFrame ? m_loadingFrame->isVisible() : false;
}

void Dialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    if(m_loadingFrame)
        m_loadingFrame->resize(size());
}
