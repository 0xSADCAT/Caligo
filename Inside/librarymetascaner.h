/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LIBRARYMETASCANER_H
#define LIBRARYMETASCANER_H

#include <QObject>
#include <QtCore>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include <Widgets/libraryelement.h>

/// Scans metadata in media library
class LibraryMetaScaner : public QObject
{
  Q_OBJECT
public:
  /// Scans metadata in media library
  explicit LibraryMetaScaner(QList<LibraryElement*> *list, QProgressBar *prBar, QObject *parent = nullptr);

  /// Start scan
  void scan();
  /// Unused, use LibraryMetaScaner::scan()
  void forceScan();

signals:
  /// Emits then end of scaning
  void done();

private:
  /// Contains pointers of elements.
  QList<LibraryElement*> *list;

  QProgressBar *progress;

  /// Second QMediaPlayer for recursive algorithm.
  QMediaPlayer player;

  /// Current scanning index.
  int index;
  /// Count elements of playlist.
  int count;

  /// Old variable. Not deleted because algorithm for scanning metadata is in dev.
  bool force;

private slots:
  /// Set metadata to LibraryElement in list
  void mediaStatus(QMediaPlayer::MediaStatus s);
};

#endif // LIBRARYMETASCANER_H
