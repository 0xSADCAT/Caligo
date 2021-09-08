/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef METASCANER_H
#define METASCANER_H

#include <QObject>
#include <QtCore>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include <Widgets/mediaelement.h>

/// Scaning metadata in playlist
class MetaScaner : public QObject
{
  Q_OBJECT
public:
  /// Scaning metadata in playlist
  explicit MetaScaner(QList<MediaElement*> *playlist, QObject *parent = nullptr);

  /// Start scaning
  void scan();
  /// Unused, use MetaScaner::scan()
  void forceScan();

private:
  /// Contains pointers of playlist elements.
  QList<MediaElement*> *list;

  /// Second QMediaPlayer for recursive algorithm.
  QMediaPlayer player;

  /// Current scanning index.
  int index;
  /// Count elements of playlist.
  int count;

  /// Old variable. Not deleted because algorithm for scanning metadata is in dev.
  bool force;

private slots:
  /// Set metadata to MediaElement in list
  void mediaStatus(QMediaPlayer::MediaStatus s);
};

#endif // METASCANER_H
