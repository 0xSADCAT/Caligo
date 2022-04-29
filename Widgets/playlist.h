/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include <Widgets/mediaelement.h>
#include <Inside/metascaner.h>

class Playlist : public QWidget
{
  Q_OBJECT
public:
  explicit Playlist(QMediaPlayer *mp, QWidget *parent = nullptr);

  /// QStringList for saving playlist in file
  QStringList getList();

  /// Add new element. [const QString&] - path to file, [const QString&] - display text (medatata)
  void add(const QString &path, const QString &text);

  /// Add new element. [const QString&] - path to file, [bool (= false)] - scan element metadata
  void add(const QString &path, bool sc=false);

  /// Add new element. [const QStringList&] - paths to files
  void add(const QStringList &paths);

  /// Clear playlist
  void clear();

signals:
  void loadPlaylist(const QString &);

public slots:
  void next();
  void prev();

  /// Update metadata in all elements of playlist
  void forceUpdate();

  void randomPlaybackChanged(bool value);

protected:
  virtual void keyPressEvent(QKeyEvent *e) override;
  virtual void mousePressEvent(QMouseEvent *) override;

private:
  QMediaPlayer *player;

  int index;
  QList<MediaElement*> list;

  QVBoxLayout *l;

  MediaElement *lastClicked;
  QList<MediaElement*> selection;

  MetaScaner *scaner;

  QString getMetaData();

  void setCurrentIndexMedia();

  bool randomPlayback;

  QRandomGenerator randomGenerator;
  QList<int> randomPrevious;

private slots:
  void mediaStatus(QMediaPlayer::MediaStatus s);

  void clickElement();
  void shiftClickElement();
  void ctrlClickElement();
  void doubleClickElement();

  void focusFromElement();

  /// Context menu
  void cmSelectAll();

  /// Context menu
  void cmDeleteSelected();

  void startDrag();

  void elementsDropped();
};

#endif // PLAYLIST_H
