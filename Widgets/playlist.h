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
    explicit Playlist(QMediaPlayer* player, QWidget* parent = nullptr);

    QStringList toStringList();

    void add(const QString& path, const QString &text);

    void add(const QString& path, bool scan = false);

    void add(const QStringList& paths);

    void clear();

signals:
    void loadPlaylist(const QString&);

public slots:
    void next();
    void previous();

    void forceUpdate();

    void randomPlaybackChanged(bool value);

private:
    QString getMetaData();

    void setCurrentIndexMedia();

    QMediaPlayer* _player;

    int _index = -1;
    QList<MediaElement*> _list;

    QVBoxLayout* _elements_layout = new QVBoxLayout;

    MetaScaner* _scaner;

    bool _random_playback = false;

    QRandomGenerator _random_generator;
    QList<int> _previous_on_random;

private slots:
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
};

#endif // PLAYLIST_H
