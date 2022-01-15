/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef CONTROLS_H
#define CONTROLS_H

#include <QtWidgets>
#include <QMediaPlayer>

#include <Widgets/timeslider.h>

class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QMediaPlayer* media_player, QWidget* parent = nullptr);

    void setSizes(int size);

    void setVolume(int volume);
    int volume() const;

    bool isRandomPlayback() const;
    void setRandomPlayback(bool value);

signals:
    void next();
    void prev();
    void fullScreen();

    void randomPlaybackChanged(bool);

    void mouseMoved();

public slots:
    void playPause();
    void mute();
    void stop();

    void plusVolume();
    void minusVolume();

protected:
    void mouseMoveEvent(QMouseEvent*) override;

private:
    QMediaPlayer* _player;

    TimeSlider* _time_slider = new TimeSlider;
    QLabel* _position_label = new QLabel("00:00");
    QLabel* _duration_label = new QLabel("00:00");

    QPushButton* _prev_button;
    QPushButton* _play_button;
    QPushButton* _stop_button;
    QPushButton* _next_button;
    QPushButton* _full_screen_button;
    QPushButton* _random_playback_button;
    QPushButton* _mute_button;
    QSlider* _volume_slider;

    bool _is_random_playback = false;

private slots:
    void mediaState(QMediaPlayer::State state);
    void mutedState(bool muted);

    void setDuration(qint64 duration);

    void setPosition(qint64 position);

    void videoAvailable(bool v);

    void randomPlaybackClicked(bool value);
};

#endif // CONTROLS_H
