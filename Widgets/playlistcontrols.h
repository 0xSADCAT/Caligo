/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
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
  explicit PlaylistControls(Playlist *pl, QWidget *parent = nullptr);

  /// Set buttons size
  void setSizes(int v);

  /// Clear current playlist before open new
  void setClearBeforeOpen(bool value);

  QString getPathPlaylists() const;
  void setPathPlaylists(const QString &value);

  QString getPathMusic() const;
  void setPathMusic(const QString &value);

private:
  Playlist *playlist;

  QPushButton *addButton;
  QPushButton *addUrlButton;
  QPushButton *clearButton;

  QPushButton *savePlaylist;
  QPushButton *loadPlaylist;

  QPushButton *forceScanButton;

  bool clearBeforeOpen;

  QString pathPlaylists;
  QString pathMusic;

private slots:
  void add();
  void addUrl();
  void clear();

  void save();
  void load();

  void loadPath(const QString &path);
};

#endif // PLAYLISTCONTROLS_H
