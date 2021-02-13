#include "metascaner.h"

MetaScaner::MetaScaner(QList<MediaElement*> *playlist, QObject *parent) : QObject(parent)
// Gets metadata to playlist elements via second QMediaPlayer.
{
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

    player.setMedia(QUrl::fromLocalFile(list->at(index)->getPath()));
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
            QString s = "";
            QStringList l = player.availableMetaData();
            if (l.contains(QMediaMetaData::AlbumArtist)) {
                s += qvariant_cast<QString>(player.metaData(QMediaMetaData::AlbumArtist));
            }
            if (l.contains(QMediaMetaData::Title)) {
                if (not s.isEmpty()) {
                    s += " - ";
                }
                s += qvariant_cast<QString>(player.metaData(QMediaMetaData::Title));
            }
            if (not s.isEmpty()) {
                list->at(index)->setText(s);
            }
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
