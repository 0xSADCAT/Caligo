/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PLAYLISTCONTROLS_H
#define PLAYLISTCONTROLS_H

#include <QtWidgets>

#include <Widgets/playlist.h>

class PlaylistControls : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistControls(Playlist* playlist, QWidget* parent = nullptr);

    void setButtonsSizes(int size);

    void setClearBeforeOpen(bool value);

    QString getPathPlaylists() const;
    void setPathPlaylists(const QString &value);

    QString getPathMusic() const;
    void setPathMusic(const QString &value);

private:
    Playlist* _playlist;

    QPushButton* _add_button = new QPushButton;
    QPushButton* _add_from_url_button = new QPushButton;
    QPushButton* _clear_button = new QPushButton;

    QPushButton* _save_playlist_button = new QPushButton;
    QPushButton* _load_playlist_button = new QPushButton;

    QPushButton* _scan_all_button = new QPushButton;

    bool _is_clear_before_open;

    QString _playlists_path = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QString _music_path = qApp->applicationDirPath() + QDir::separator() + "playlists";

private slots:
    void add();
    void addUrl();
    void clear();

    void save();
    void load();

    void loadPath(const QString& path);
};

#endif // PLAYLISTCONTROLS_H
