/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QSettings>

#include <Widgets/controls.h>
#include <Widgets/playinfo.h>
#include <Widgets/playlist.h>
#include <Widgets/playlistcontrols.h>
#include <Widgets/medialibrary.h>
#include <Widgets/libraryplaylists.h>

#include <OtherWindows/aboutwindow.h>
#include <OtherWindows/helpwindow.h>
#include <OtherWindows/settingswindow.h>

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  void addToPlaylist(const QString &path);

  void forceUpdatePlaylistMetadata();

protected:
  virtual void closeEvent(QCloseEvent *) override;
  virtual void dragEnterEvent(QDragEnterEvent *e) override;
  virtual void dropEvent(QDropEvent *e) override;
  virtual void resizeEvent(QResizeEvent *) override;

private:
  QMediaPlayer *mp;

  Controls *controls;
  PlayInfo *playInfo;
  Playlist *playlist;
  PlaylistControls *plControls;

  MediaLibrary *library;
  LibraryPlaylists *playlistLibrary;

  QSplitter *spl;
  QWidget *sw;

  QSettings *settings;

  void loadSettings();

  /// Entry points (dirs and files) after drop dir in app window
  void recursiveEntryPoints(QDir d);
  QStringList droppedFiles;

  AboutWindow *aboutWindow;
  HelpWindow *helpWindow;
  SettingsWindow *settingsWindow;

  QTabWidget *tabWidget;

  QList<QWidget*> tabs;

  QPixmap backgroundPixmap;

  QTimer *timerFullScreen;
  int timerVal;
  const int timerBaseVal = 6;

private slots:
  void setNewTitle(const QString &s);
  void help();

  void setBackgroundPixmap(const QPixmap &value);

  void videoFullscreen();

  /// Exit fullscreen mode
  void exitFull();

  void timerTick();

  void mouseMoved();
};

QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);
#endif // WIDGET_H
