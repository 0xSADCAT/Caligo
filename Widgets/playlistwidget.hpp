#ifndef PLAYLISTWIDGET_HPP
#define PLAYLISTWIDGET_HPP

#include <QWidget>
#include <QMediaPlayer>

#include "Widgets/playlist.h"
#include "Widgets/playlistcontrols.h"

class PlaylistWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistWidget(QMediaPlayer* media_player, QWidget *parent = nullptr);

    Playlist* playlist() const;

    PlaylistControls* playlistControls() const;

private:
    Playlist* _playlist;
    PlaylistControls* _playlist_controls;
};

#endif // PLAYLISTWIDGET_HPP
