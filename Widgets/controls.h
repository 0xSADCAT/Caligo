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

/**
 * @brief The Controls class provides playback controls widget
 */
class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QMediaPlayer* media_player, QWidget* parent = nullptr);

    /**
     * @brief Set buttons sizes
     * @param size Button size (buttons is square)
     *
     * @note Play/pause button size scales by 1.5
     */
    void setSizes(int size);

    /**
     * @brief Set player volume and moves slider
     * @param volume Volume value (0 .. 100)
     *
     * @note If value > 100 it will be 100
     * @note If value < 0 it will be 0
     */
    void setVolume(int volume);

    /**
     * @brief Current volume value
     * @return Current volume
     */
    int volume() const;

    /**
     * @brief Is playback random
     * @return true or false
     */
    bool isRandomPlayback() const;

    /**
     * @brief Set random playback mode
     * @param value Mode: true - random
     */
    void setRandomPlayback(bool value);

signals:
    /**
     * @brief Clicked on next button
     */
    void nextClicked();

    /**
     * @brief Clicked on previous button
     */
    void previousClicked();

    /**
     * @brief Clicked on full screen button
     */
    void fullScreenClicked();

    /**
     * @brief Playback mode changed (true - random)
     */
    void playbackModeChanged(bool);

    /**
     * @brief Mouse moved on widget
     *
     * @note Translates mouseMoveEvent()
     */
    void mouseMoved();

public slots:
    /**
     * @brief Action on play/pause button clicked
     */
    void onPlayPause();

    /**
     * @brief Action on mute button clicked
     */
    void onMute();

    /**
     * @brief Action on stop button clicked
     */
    void onStop();

    /**
     * @brief Increase volume on shortcut
     */
    void onPlusVolume();

    /**
     * @brief Decrease volume on shortcut
     */
    void onMinusVolume();

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
    void onMediaStateChanged(QMediaPlayer::State state);
    void onMutedStateChanged(bool muted);

    void onDurationChanged(qint64 duration);

    void onPositionChanged(qint64 position);

    void onVideoAvailableChanged(bool v);

    void onRandomPlaybackClicked(bool value);
};

#endif // CONTROLS_H
