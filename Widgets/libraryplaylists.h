/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LIBRARYPLAYLISTS_H
#define LIBRARYPLAYLISTS_H

#include <Widgets/elementplaylist.h>
#include <Widgets/playlist.h>

class LibraryPlaylists : public QWidget
{
  Q_OBJECT
public:
  explicit LibraryPlaylists(Playlist *pls, QWidget *parent = nullptr);

  QString getPathPlaylists() const;
  void setPathPlaylists(const QString &value);

  /// Clear current playlist before open new
  void setClearBeforeOpen(bool value);

public slots:
  /// Search playlists
  void scan();

private:
  bool clearBeforeOpen;

  Playlist *playlist;
  QList<ElementPlaylist*> list;
  QVBoxLayout *mainLayout;

  QString pathPlaylists;

  void add(QString &path, QString &name);
  void remove(ElementPlaylist *e);
  void remove(int index);
  void clear();

  QList<ElementPlaylist*> selection;
  ElementPlaylist *lastClicked;

private slots:
  void elementClicked();
  void elementDouble();
  void elementShift();
  void elementCtrl();
  void elementFocus();

  void setPath();
};

#endif // LIBRARYPLAYLISTS_H
