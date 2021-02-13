#include "controls.h"

Controls::Controls(QMediaPlayer *mp, QWidget *parent) : QWidget(parent)
// Bottom widget. Playback/volume controls and Settings and About buttons.
{
    player = mp;

    timeSlider = new TimeSlider;

    posLabel = new QLabel("00:00");
    durLabel = new QLabel("00:00");

    topLayout = new QHBoxLayout;
    topLayout->addWidget(posLabel, 0);
    topLayout->addWidget(timeSlider, 1);
    topLayout->addWidget(durLabel, 0);

    settingsButton = new QPushButton;
    settingsButton->setToolTip(tr("Settings"));
    settingsButton->setIcon(QPixmap(":/img/settings24"));

    aboutButton = new QPushButton;
    aboutButton->setToolTip(tr("About"));
    aboutButton->setIcon(QPixmap(":/img/info"));

    QMenu *abMenu = new QMenu;
    abMenu->addAction(QPixmap(":/img/help"), tr("Help"), this, &Controls::help);
    abMenu->addAction(QPixmap(":/img/info"), tr("About"), this, &Controls::about);
    abMenu->addAction(QPixmap(":/img/qt"), tr("About Qt"), qApp, &QApplication::aboutQt);
    aboutButton->setMenu(abMenu);

    prevButton = new QPushButton;
    prevButton->setToolTip(tr("Previous track"));
    prevButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    playButton = new QPushButton;
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    stopButton = new QPushButton;
    stopButton->setToolTip(tr("Stop"));
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    nextButton = new QPushButton;
    nextButton->setToolTip(tr("Next track"));
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    fullScreenButton = new QPushButton;
    fullScreenButton->setToolTip(tr("Toggle fullscreen (video only)") + " [F]");
    fullScreenButton->setIcon(QPixmap(":/img/fullScreen24"));

    muteButton = new QPushButton;
    muteButton->setToolTip(tr("Mute"));
    muteButton->setIcon(QPixmap(":/img/volume"));

    volumeSlider = new QSlider;
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setMinimumWidth(200);
    volumeSlider->setOrientation(Qt::Horizontal);
    player->setVolume(volumeSlider->value());

    botLayout = new QHBoxLayout;
    botLayout->addWidget(settingsButton, 0);
    botLayout->addWidget(aboutButton, 0);
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

    connect(settingsButton, &QPushButton::clicked, this, &Controls::settings);
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
    settingsButton->setIconSize(s);
    aboutButton->setIconSize(s);
    prevButton->setIconSize(s);
    playButton->setIconSize(ps);
    stopButton->setIconSize(s);
    nextButton->setIconSize(s);
    muteButton->setIconSize(s);
    fullScreenButton->setIconSize(s);
}

void Controls::setVolume(int v)
{
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
    fullScreenButton->setEnabled(v);
}

/* private SLOT */ void Controls::mediaState(QMediaPlayer::State s)
{
    if (s == QMediaPlayer::State::PlayingState) {
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        playButton->setToolTip(tr("Pause"));
    }
    else {
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playButton->setToolTip(tr("Play"));
    }
}

/* private SLOT */ void Controls::mutedState(bool v)
{
    if (v) {
        muteButton->setIcon(QPixmap(":/img/mute"));
        muteButton->setToolTip(tr("Unmute"));
    }
    else {
        muteButton->setIcon(QPixmap(":/img/volume"));
        muteButton->setToolTip(tr("Mute"));
    }
}

/* private SLOT */ void Controls::setDur(qint64 v)
{
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
    if (player->state() == QMediaPlayer::State::PlayingState) {
        player->pause();
    }
    else {
        player->play();
    }
}

/* public SLOT */ void Controls::mute()
{
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
    player->pause();
    player->setPosition(0);
}

/* public SLOT */ void Controls::plusVol()
// Hotkey
{
    setVolume(player->volume() + 5);
}

/* public SLOT */ void Controls::minusVol()
// Hotkey
{
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
