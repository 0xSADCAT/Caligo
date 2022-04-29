/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "playlist.h"

Playlist::Playlist(QMediaPlayer* player, QWidget* parent)
    : QWidget(parent),
      _player(player)
{
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(_elements_layout, 0);
    main_layout->addStretch(1);

    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);

    connect(_player, &QMediaPlayer::mediaStatusChanged, this, &Playlist::mediaStatusChanged);

    _scaner = new MetaScaner(&_list);

    _random_generator.seed(QTime::currentTime().msec());
}

QStringList Playlist::toStringList()
{
    QStringList result;
    for (auto* element : _list)
        result << element->format();

    return result;
}

void Playlist::add(const QString &path, const QString &text)
{
    MediaElement* element = new MediaElement(path);
    if (not (text.isEmpty() or text == " "))
        element->setText(text);
    _elements_layout->addWidget(element, 0);
    _list << element;

    if (_index == -1) {
        _index = 0;
        setCurrentIndexMedia();
        _list[0]->setPlaying(true);
    }
}

void Playlist::add(const QString& path, bool scan)
{
    if (path.endsWith(".cpl")) {
        emit loadPlaylist(path);
        return;
    }

    MediaElement *e = new MediaElement(path);
    _elements_layout->addWidget(e, 0);
    _list << e;

    if (_index == -1) {
        _index = 0;
        setCurrentIndexMedia();
        _list[0]->setPlaying(true);
    }

    if (scan)
        _scaner->scan();
}

void Playlist::add(const QStringList &paths)
{
    if (paths.isEmpty())
        return;

    int path_counter = 0;
    for (auto& file_path : paths) {
        add(file_path);

        if (path_counter % 10 == 0)
            qApp->processEvents();
        path_counter++;
    }

    if (_index == -1) {
        _index = 0;
        setCurrentIndexMedia();
        _list[0]->setPlaying(true);
    }

    _scaner->scan();
}

void Playlist::clear()
{
    _player->stop();
    _player->setMedia(QUrl());
    for (auto* element : _list) {
        _list.removeAll(element);
        _elements_layout->removeWidget(element);
        element->~MediaElement();
    }
    _index = -1;
}

void Playlist::forceUpdate()
{
    _scaner->forceScan();
}

void Playlist::randomPlaybackChanged(bool value)
{
    _random_playback = value;
}

void Playlist::next()
{
    int media_count = _list.count();
    if (media_count < 2)
        return;

    _list[_index]->setPlaying(false);
    _index++;
    if (_index >= media_count)
        _index = 0;
    _list[_index]->setPlaying(true);
    setCurrentIndexMedia();
}

void Playlist::previous()
{
    int media_count = _list.count();
    if (media_count < 2)
        return;

    _list[_index]->setPlaying(false);
    _index--;

    if (_index < 0)
        _index = media_count - 1;

    _list[_index]->setPlaying(true);
    setCurrentIndexMedia();
}

void Playlist::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::EndOfMedia:
        next();
        break;

    case QMediaPlayer::BufferedMedia:
    case QMediaPlayer::LoadedMedia:
        if (not _list[_index]->hasMetadata())
            _list[_index]->setText(getMetaData());
        break;

    default:
        break;
    }
}

QString Playlist::getMetaData()
{
    QString result = "";
    QStringList l = _player->availableMetaData();
    if (l.contains(QMediaMetaData::AlbumArtist))
        result += qvariant_cast<QString>(_player->metaData(QMediaMetaData::AlbumArtist));

    if (l.contains(QMediaMetaData::Title)) {
        if (not result.isEmpty())
            result += " - ";
        result += qvariant_cast<QString>(_player->metaData(QMediaMetaData::Title));
    }

    if (result.isEmpty())
        result = _list[_index]->path();

    return result;
}

void Playlist::setCurrentIndexMedia()
{
    _player->stop();
    QString url_string = _list[_index]->path();

    QUrl url;
    if (url_string.startsWith("http"))
        url = QUrl(url_string);
    else
        url = QUrl::fromLocalFile(url_string);

    _player->setMedia(url);
    _player->play();
}
