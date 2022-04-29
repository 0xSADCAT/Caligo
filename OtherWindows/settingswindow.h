/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtWidgets>

#include <Widgets/playlistcontrols.h>
#include <Widgets/medialibrary.h>
#include <Widgets/libraryplaylists.h>

/// Application settings
class SettingsWindow : public QWidget
{
  Q_OBJECT
public:
  /// Application settings
  explicit SettingsWindow(QSettings *s, PlaylistControls *pc, MediaLibrary *ml, LibraryPlaylists *pl, QWidget *wgt);

private:
  QSettings *settings;
  PlaylistControls *listControls;
  QWidget *widget;

  MediaLibrary *mediaLibrary;
  LibraryPlaylists *playlistLibrary;

  /// Read settings and set
  void setState();

  QVBoxLayout *l;

  QLabel *pathMusicLabel;
  QLabel *pathMusicValue;
  QPushButton *setPathMusicButton;
  QPushButton *setDefaultPathMusicButton;

  QLabel *pathListLabel;
  QLabel *pathListValue;
  QPushButton *setPathListButton;
  QPushButton *setDefaultPathListButton;

  QCheckBox *clearBeforeOpenPlaylistCheck;

  QCheckBox *loadOldCheck;

private slots:
  void pathMusic();
  void pathMusicDefault();

  void pathList();
  void pathListDefault();

  /// Clear playlist before open new
  void clearBeforeOpen(bool v);

  /// Load old playlist (current playlist before last use)
  void loadOld(bool v);
};

#endif // SETTINGSWINDOW_H
