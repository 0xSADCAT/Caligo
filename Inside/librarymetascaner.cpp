#include "librarymetascaner.h"

LibraryMetaScaner::LibraryMetaScaner(QList<LibraryElement*> *list, QProgressBar *prBar, QObject *parent) : QObject(parent)
  // Copy of MetaScaner
{
    this->list = list;
    progress = prBar;
    index = -1;
    count = -1;
    force = false;

    connect(&player, &QMediaPlayer::mediaStatusChanged, this, &LibraryMetaScaner::mediaStatus);
}

void LibraryMetaScaner::scan()
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

    if (count != 0) {
        int pr = int(qreal(index) / qreal(count) * qreal(100));
        progress->setValue(pr);
    }

    player.setMedia(url);
}

void LibraryMetaScaner::forceScan()
// Earler 'forece = true' was only here.
{
    force = true;
    scan();
}

/* SLOT */ void LibraryMetaScaner::mediaStatus(QMediaPlayer::MediaStatus s)
// Second path of signal-slot recursive algorithm.
{
    switch (s) {
    case QMediaPlayer::MediaStatus::BufferedMedia:
    case QMediaPlayer::MediaStatus::LoadedMedia:

        if (force) {
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
        qDebug() << "SLOT LibraryMetaScaner::mediaStatus(...)";
        qDebug() << "Result:" << str;
#endif

        }
        index++;
        if (index >= count) {
            index = -1;
            count = -1;
            player.setMedia(QUrl());
            force = false;
            emit done();
        }
        else {
            scan();
        }
        break;

    default:
        break;
    }
}
