/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef CONTROLS_H
#define CONTROLS_H

#include <QtWidgets>
#include <QMediaPlayer>

#include <Widgets/timeslider.h>

/// Bottom control panel
class Controls : public QWidget
{
  Q_OBJECT
public:
  /// Bottom control panel
  explicit Controls(QMediaPlayer *mp, QWidget *parent = nullptr);

  /// Set buttons sizes
  void setSizes(int v);

  void setVolume(int v);
  int getVolume();

  bool isRandomPlayback() const;
  void setRandomPlayback(bool value);

signals:
  /// Next media in playlist
  void next();
  /// Previous media in playlist
  void prev();
  void fullScreen();

  void randomPlaybackChanged(bool);

public slots:
  void playPause();
  void mute();
  void stop();

  void plusVol();
  void minusVol();

private:
  QMediaPlayer *player;

  TimeSlider *timeSlider;
  QLabel *posLabel;
  QLabel *durLabel;
  QHBoxLayout *topLayout;

  QPushButton *prevButton;
  QPushButton *playButton;
  QPushButton *stopButton;
  QPushButton *nextButton;
  QPushButton *fullScreenButton;
  QPushButton *randomPlaybackButton;
  QPushButton *muteButton;
  QSlider *volumeSlider;
  QHBoxLayout *botLayout;

  QVBoxLayout *l;

  bool randomPlayback;

private slots:
  void mediaState(QMediaPlayer::State s);
  void mutedState(bool v);

  /// Set TimeSlider duration
  void setDur(qint64 v);

  /// Set TimeSlider position
  void setPos(qint64 v);

  /// Converts miliseconds to QString
  QString msToStr(qint64 ms);

  void videoAvailable(bool v);

  void randomPlaybackClicked(bool value);
};

#endif // CONTROLS_H
