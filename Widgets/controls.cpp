#include "controls.h"

Controls::Controls(QMediaPlayer *mp, QWidget *parent) : QWidget(parent)
// Bottom widget. Playback/volume controls and Settings and About buttons.
{
#ifdef DEBUG_OUTPUT
        qDebug() << ">>> Controls init";
#endif

    player = mp;

    timeSlider = new TimeSlider;

    posLabel = new QLabel("00:00");
    durLabel = new QLabel("00:00");

    topLayout = new QHBoxLayout;
    topLayout->addWidget(posLabel, 0);
    topLayout->addWidget(timeSlider, 1);
    topLayout->addWidget(durLabel, 0);

    prevButton = new QPushButton;
    prevButton->setToolTip(tr("Previous track") + " [B]");
    prevButton->setIcon(QIcon(":/img/previous"));

    playButton = new QPushButton;
    playButton->setToolTip(tr("Play") + " [P]");
    playButton->setIcon(QIcon(":/img/play"));

    stopButton = new QPushButton;
    stopButton->setToolTip(tr("Stop") + " [S]");
    stopButton->setIcon(QIcon(":/img/stop"));

    nextButton = new QPushButton;
    nextButton->setToolTip(tr("Next track") + " [N]");
    nextButton->setIcon(QIcon(":/img/next"));

    fullScreenButton = new QPushButton;
    fullScreenButton->setToolTip(tr("Toggle fullscreen (video only)") + " [F]");
    fullScreenButton->setIcon(QPixmap(":/img/fullscreen"));

    muteButton = new QPushButton;
    muteButton->setToolTip(tr("Mute") + " [Ctrl+M]");
    muteButton->setIcon(QPixmap(":/img/volume"));

    volumeSlider = new QSlider;
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setMinimumWidth(200);
    volumeSlider->setOrientation(Qt::Horizontal);
    player->setVolume(volumeSlider->value());

    botLayout = new QHBoxLayout;
    botLayout->addStretch(1);
    botLayout->addSpacing(15);
    botLayout->addWidget(prevButton, 0);
    botLayout->addSpacing(5);
    botLayout->addWidget(playButton, 0);
    botLayout->addSpacing(5);
    botLayout->addWidget(stopButton, 0);
    botLayout->addWidget(nextButton, 0);
    botLayout->addSpacing(15);
    botLayout->addStretch(1);
    botLayout->addWidget(fullScreenButton, 0);
    botLayout->addStretch(1);
    botLayout->addSpacing(15);
    botLayout->addWidget(muteButton, 0);
    botLayout->addWidget(volumeSlider, 0);

    l = new QVBoxLayout;
    l->addLayout(topLayout);
    l->addLayout(botLayout);
    setLayout(l);

    connect(mp, &QMediaPlayer::stateChanged, this, &Controls::mediaState);
    connect(mp, &QMediaPlayer::mutedChanged, this, &Controls::mutedState);

    connect(mp, &QMediaPlayer::volumeChanged, volumeSlider, &QSlider::setValue);
    connect(volumeSlider, &QSlider::valueChanged, mp, &QMediaPlayer::setVolume);

    connect(mp, &QMediaPlayer::durationChanged, this, &Controls::setDur);
    connect(mp, &QMediaPlayer::positionChanged, this, &Controls::setPos);
    connect(timeSlider, &TimeSlider::clicked, mp, &QMediaPlayer::setPosition);

    connect(prevButton, &QPushButton::clicked, this, &Controls::prev);
    connect(playButton, &QPushButton::clicked, this, &Controls::playPause);
    connect(stopButton, &QPushButton::clicked, this, &Controls::stop);
    connect(nextButton, &QPushButton::clicked, this, &Controls::next);
    connect(muteButton, &QPushButton::clicked, this, &Controls::mute);

    connect(fullScreenButton, &QPushButton::clicked, this, &Controls::fullScreen);
    connect(player, &QMediaPlayer::videoAvailableChanged, this, &Controls::videoAvailable);
}

void Controls::setSizes(int v)
{
    if (v < 16)
        return;

    QSize s(v, v);
    qreal vr = qreal(v) * 1.5;
    QSize ps((int(vr)), (int(vr)));
    prevButton->setIconSize(s);
    playButton->setIconSize(ps);
    stopButton->setIconSize(s);
    nextButton->setIconSize(s);
    muteButton->setIconSize(s);
    fullScreenButton->setIconSize(s);
}

void Controls::setVolume(int v)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "Controls::setVolume" << v;
#endif

    if (v >= 0 && v <= 100) {
        player->setVolume(v);
        volumeSlider->setValue(v);
    }
    else if (v < 0) {
        player->setVolume(0);
        volumeSlider->setValue(0);
    }
    else if (v > 100) {
        player->setVolume(100);
        volumeSlider->setValue(100);
    }
}

int Controls::getVolume()
{
    return player->volume();
}

/* private SLOT */ void Controls::videoAvailable(bool v)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::videoAvailable" << v;
#endif

    fullScreenButton->setEnabled(v);
}

/* private SLOT */ void Controls::mediaState(QMediaPlayer::State s)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::mediaState" << s;
#endif

    if (s == QMediaPlayer::State::PlayingState) {
        playButton->setIcon(QIcon(":/img/pause"));
        playButton->setToolTip(tr("Pause") + " [P]");
    }
    else {
        playButton->setIcon(QIcon(":/img/play"));
        playButton->setToolTip(tr("Play") + " [P]");
    }
}

/* private SLOT */ void Controls::mutedState(bool v)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::mutedState" << v;
#endif

    if (v) {
        muteButton->setIcon(QIcon(":/img/mute"));
        muteButton->setToolTip(tr("Unmute") + " [Ctrl+M]");
    }
    else {
        muteButton->setIcon(QIcon(":/img/volume"));
        muteButton->setToolTip(tr("Mute") + " [Ctrl+M]");
    }
}

/* private SLOT */ void Controls::setDur(qint64 v)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::setDur" << v;
#endif

    timeSlider->setDuration(v);
    durLabel->setText(msToStr(v));
}

/* private SLOT */ void Controls::setPos(qint64 v)
{
    timeSlider->setPosition(v);
    posLabel->setText(msToStr(v));
}

/* public SLOT */ void Controls::playPause()
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::playPause()";
#endif

    if (player->state() == QMediaPlayer::State::PlayingState) {
        player->pause();
    }
    else {
        player->play();
    }
}

/* public SLOT */ void Controls::mute()
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::mute()";
#endif

    if (player->isMuted()) {
        player->setMuted(false);
    }
    else {
        player->setMuted(true);
    }
}

/* public SLOT */ void Controls::stop()
// Not used QMediaPlayer::stop() because emits signal QMediaPlayer::mediaStatusChanged(QMediaPlayer::LoadedMedia)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::stop()";
#endif

    player->pause();
    player->setPosition(0);
}

/* public SLOT */ void Controls::plusVol()
// Hotkey
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::plusVol()";
#endif

    setVolume(player->volume() + 5);
}

/* public SLOT */ void Controls::minusVol()
// Hotkey
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT Controls::minusVol()";
#endif

    setVolume(player->volume() - 5);
}

QString Controls::msToStr(qint64 ms)
{
    QString ret;
    ms /= 1000;

    int s = ms % 60;
    ms /= 60;
    int m = ms % 60;
    int h = ms / 60;

    if (h != 0) {
        ret += QString::number(h) + ":";
    }

    if (m < 10) {
        ret += "0";
    }
    ret += QString::number(m) + ":";

    if (s < 10) {
        ret += "0";
    }
    ret += QString::number(s);

    return ret;
}
