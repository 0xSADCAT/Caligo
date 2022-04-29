/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PLAYINFO_H
#define PLAYINFO_H

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVideoWidget>

#include <Widgets/image.h>
#include <Widgets/videowidget.h>

class PlayInfo : public QWidget
{
  Q_OBJECT
public:
  explicit PlayInfo(QMediaPlayer *mp, QWidget *parent = nullptr);

  /// Full screen mode
  void setNotFull(bool v);
  void focus();

  VideoWidget *video;

signals:
  /// Set new window title
  void newTitle(const QString &s);
  void newPixmap(const QPixmap &pix);
  void fsClicked();
  void mouseMoved();

private:
  QMediaPlayer *player;

  Image *image;
  QLabel *author;
  QLabel *name;
  bool isVideo;
  /// Video fullscreen mode
  bool isFSVideo;

  /// Set new window title
  void setTitle();

private slots:
  void mediaStatus(QMediaPlayer::MediaStatus s);
  void videoChanged(bool v);

  void videoClicked();
  void videoDoubleClicked();
};

#endif // PLAYINFO_H
