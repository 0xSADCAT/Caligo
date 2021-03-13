/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "metascaner.h"

MetaScaner::MetaScaner(QList<MediaElement*> *playlist, QObject *parent) : QObject(parent)
// Gets metadata to playlist elements via second QMediaPlayer.
{
#ifdef DEBUG_OUTPUT
  qDebug() << ">>> MetaScaner init";
#endif

  list = playlist;
  index = -1;
  count = -1;
  force = false;

  connect(&player, &QMediaPlayer::mediaStatusChanged, this, &MetaScaner::mediaStatus);
}

void MetaScaner::scan()
// First part of recursive algorithm based on QMediaPlayer::MediaStatus::BufferMedia and LoadedMedia.
// Use second QMediaPlayer which defined in this class.
{
  force = true;

  if (index == -1) {
      index = 0;
      count = list->count();
    }

  QString u = list->at(index)->getPath();
  QUrl url;
  if (u.startsWith("http")) {
      url = QUrl(u);
    }
  else {
      url = QUrl::fromLocalFile(u);
    }
  player.setMedia(url);
}

void MetaScaner::forceScan()
// Earler 'forece = true' was only here.
{
  force = true;
  scan();
}

/* SLOT */ void MetaScaner::mediaStatus(QMediaPlayer::MediaStatus s)
// Second path of signal-slot recursive algorithm.
{
  switch (s) {
    case QMediaPlayer::MediaStatus::BufferedMedia:
    case QMediaPlayer::MediaStatus::LoadedMedia:
      if (not list->at(index)->hasMeta() or force) {
          QString str = "";
          QStringList l = player.availableMetaData();
          if (l.contains(QMediaMetaData::AlbumArtist)) {
              str += qvariant_cast<QString>(player.metaData(QMediaMetaData::AlbumArtist));
            }
          if (l.contains(QMediaMetaData::Title)) {
              if (not str.isEmpty()) {
                  str += " - ";
                }
              str += qvariant_cast<QString>(player.metaData(QMediaMetaData::Title));
            }
          if (not str.isEmpty()) {
              list->at(index)->setText(str);
            }

#ifdef DEBUG_OUTPUT
          qDebug() << "SLOT MetaScaner::mediaStatus(...)";
          qDebug() << "Result:" << str;
#endif

        }
      index++;
      if (index >= count) {
          index = -1;
          count = -1;
          player.setMedia(QUrl());
          force = false;
        }
      else {
          scan();
        }
      break;

    default:
      break;
    }
}
