/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "controls.h"

static QString msToString(qint64 ms);

Controls::Controls(QMediaPlayer* media_player, QWidget* parent)
    : QWidget(parent),
      _player(media_player)
{
    setMouseTracking(true);

    _position_label->setObjectName("AlphaBG");
    _duration_label->setObjectName("AlphaBG");

    QHBoxLayout* top_layout = new QHBoxLayout;
    top_layout->addWidget(_position_label, 0);
    top_layout->addWidget(_time_slider, 1);
    top_layout->addWidget(_duration_label, 0);

    _prev_button = new QPushButton;
    _prev_button->setToolTip(tr("Previous track") + " [B]");
    _prev_button->setIcon(QIcon(":/img/previous"));

    _play_button = new QPushButton;
    _play_button->setToolTip(tr("Play") + " [P]");
    _play_button->setIcon(QIcon(":/img/play"));

    _stop_button = new QPushButton;
    _stop_button->setToolTip(tr("Stop") + " [S]");
    _stop_button->setIcon(QIcon(":/img/stop"));

    _next_button = new QPushButton;
    _next_button->setToolTip(tr("Next track") + " [N]");
    _next_button->setIcon(QIcon(":/img/next"));

    _random_playback_button = new QPushButton;
    _random_playback_button->setToolTip(tr("Random playback"));
    _random_playback_button->setIcon(QIcon(":img/randomPlayback"));
    _random_playback_button->setCheckable(true);
    _random_playback_button->setChecked(false);

    _full_screen_button = new QPushButton;
    _full_screen_button->setToolTip(tr("Toggle fullscreen (video only)") + " [F]");
    _full_screen_button->setIcon(QPixmap(":/img/fullscreen"));

    _mute_button = new QPushButton;
    _mute_button->setToolTip(tr("Mute") + " [Ctrl+M]");
    _mute_button->setIcon(QPixmap(":/img/volume"));

    _volume_slider = new QSlider;
    _volume_slider->setRange(0, 100);
    _volume_slider->setValue(50);
    _volume_slider->setMinimumWidth(qApp->desktop()->size().width() > 1920 ? 150 : 100);
    _volume_slider->setOrientation(Qt::Horizontal);
    _player->setVolume(_volume_slider->value());

    QHBoxLayout* bottom_layout = new QHBoxLayout;

    bottom_layout->addStretch(1);
    bottom_layout->addSpacing(15);

    bottom_layout->addWidget(_prev_button, 0);
    bottom_layout->addSpacing(5);
    bottom_layout->addWidget(_play_button, 0);
    bottom_layout->addSpacing(5);
    bottom_layout->addWidget(_next_button, 0);
    bottom_layout->addSpacing(5);
    bottom_layout->addWidget(_stop_button, 0);
    bottom_layout->addSpacing(5);

    bottom_layout->addStretch(1);
    bottom_layout->addWidget(_full_screen_button, 0);
    bottom_layout->addSpacing(5);
    bottom_layout->addWidget(_random_playback_button, 0);

    bottom_layout->addSpacing(5);
    bottom_layout->addStretch(1);

    bottom_layout->addWidget(_mute_button, 0);
    bottom_layout->addWidget(_volume_slider, 0);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(top_layout);
    main_layout->addLayout(bottom_layout);
    setLayout(main_layout);

    connect(_player, &QMediaPlayer::stateChanged, this, &Controls::onMediaStateChanged);
    connect(_player, &QMediaPlayer::mutedChanged, this, &Controls::onMutedStateChanged);

    connect(_player, &QMediaPlayer::volumeChanged, _volume_slider, &QSlider::setValue);
    connect(_volume_slider, &QSlider::valueChanged, _player, &QMediaPlayer::setVolume);

    connect(_player, &QMediaPlayer::durationChanged, this, &Controls::onDurationChanged);
    connect(_player, &QMediaPlayer::positionChanged, this, &Controls::onPositionChanged);
    connect(_time_slider, &TimeSlider::clicked, _player, &QMediaPlayer::setPosition);

    connect(_prev_button, &QPushButton::clicked, this, &Controls::previousClicked);
    connect(_play_button, &QPushButton::clicked, this, &Controls::onPlayPause);
    connect(_stop_button, &QPushButton::clicked, this, &Controls::onStop);
    connect(_next_button, &QPushButton::clicked, this, &Controls::nextClicked);
    connect(_mute_button, &QPushButton::clicked, this, &Controls::onMute);

    connect(_full_screen_button, &QPushButton::clicked, this, &Controls::fullScreenClicked);
    connect(_player, &QMediaPlayer::videoAvailableChanged, this, &Controls::onVideoAvailableChanged);

    connect(_random_playback_button, &QPushButton::clicked, this, &Controls::onRandomPlaybackClicked);
}

void Controls::setSizes(int size)
{
    assert(size >= 16 and size <= 128);

    qreal vr = qreal(size) * 1.5;
    QSize regular_button_size(size, size);
    QSize play_button_size((int(vr)), (int(vr)));

    _prev_button->setIconSize(regular_button_size);
    _play_button->setIconSize(play_button_size);
    _stop_button->setIconSize(regular_button_size);
    _next_button->setIconSize(regular_button_size);
    _mute_button->setIconSize(regular_button_size);
    _full_screen_button->setIconSize(regular_button_size);
    _random_playback_button->setIconSize(regular_button_size);
}

void Controls::setVolume(int volume)
{
    if (volume < 0)
        volume = 0;
    else if (volume > 100)
        volume = 100;

    _player->setVolume(volume);
    _volume_slider->setValue(volume);
}

int Controls::volume() const
{
    return _player->volume();
}

void Controls::onVideoAvailableChanged(bool v)
{
    _full_screen_button->setEnabled(v);
    _full_screen_button->setVisible(v);
}

void Controls::onRandomPlaybackClicked(bool value)
{
    emit playbackModeChanged(value);
    setRandomPlayback(value);
}

void Controls::onMediaStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::State::PlayingState) {
        _play_button->setIcon(QIcon(":/img/pause"));
        _play_button->setToolTip(tr("Pause") + " [P]");
    } else {
        _play_button->setIcon(QIcon(":/img/play"));
        _play_button->setToolTip(tr("Play") + " [P]");
    }
    _full_screen_button->setVisible(_player->isVideoAvailable());
}

void Controls::onMutedStateChanged(bool muted)
{
    if (muted) {
        _mute_button->setIcon(QIcon(":/img/mute"));
        _mute_button->setToolTip(tr("Unmute") + " [Ctrl+M]");
    } else {
        _mute_button->setIcon(QIcon(":/img/volume"));
        _mute_button->setToolTip(tr("Mute") + " [Ctrl+M]");
    }
}

void Controls::onDurationChanged(qint64 duration)
{
    _time_slider->setDuration(duration);
    _duration_label->setText(msToString(duration));
}

void Controls::onPositionChanged(qint64 position)
{
    _time_slider->setPosition(position);
    _position_label->setText(msToString(position));
}

void Controls::onPlayPause()
{
    if (_player->state() == QMediaPlayer::State::PlayingState)
        _player->pause();
    else
        _player->play();
}

void Controls::onMute()
{
    _player->setMuted(not _player->isMuted());
}

void Controls::onStop()
// Not used QMediaPlayer::stop() because emits signal
// QMediaPlayer::mediaStatusChanged(QMediaPlayer::LoadedMedia)
{
    _player->pause();
    _player->setPosition(0);
}

static constexpr int volume_delta = 5;

void Controls::onPlusVolume()
{
    setVolume(_player->volume() + volume_delta);
}

void Controls::onMinusVolume()
{
    setVolume(_player->volume() - volume_delta);
}

void Controls::mouseMoveEvent(QMouseEvent*)
{
    emit mouseMoved();
}

bool Controls::isRandomPlayback() const
{
    return _is_random_playback;
}

void Controls::setRandomPlayback(bool value)
{
    _random_playback_button->setChecked(value);
    _is_random_playback = value;
    emit playbackModeChanged(value);
}

QString msToString(qint64 ms)
{
    QString result;
    ms /= 1000;

    int seconds = ms % 60;
    ms /= 60;
    int minutes = ms % 60;
    int hours = ms / 60;

    if (hours != 0)
        result += QString::number(hours) + ":";

    if (minutes < 10)
        result += "0";
    result += QString::number(minutes) + ":";

    if (seconds < 10)
        result += "0";
    result += QString::number(seconds);

    return result;
}
