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

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

    void addToPlaylist(const QString& path);

    void forceUpdatePlaylistMetadata();

protected:
    void closeEvent(QCloseEvent*) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void loadSettings();

    void recursiveEntryPoints(QDir dir);

    QMediaPlayer* _media_player;

    Controls* _playback_controls;
    PlayInfo* _playback_info;
    Playlist* _playlist;
    PlaylistControls* _playlist_controls;

    MediaLibrary* _library;
    LibraryPlaylists* _playlist_library;

    QSplitter* _splitter;
    QWidget* sw;

    QSettings* _settings;
    QStringList _droppedFiles;

    AboutWindow* _about_widget;
    HelpWindow* _help_widget;
    SettingsWindow* _settings_widget;

    QTabWidget* _tab_widget;

    QList<QWidget*> _tabs;

    QTimer* _fullscreen_timer;
    int _timer_value;
    const int _TIMER_BASE_VALUE = 6;

private slots:
    void setNewWindowTitle(const QString& title);
    void help();

    void videoFullscreen();

    void exitFull();

    void timerTick();

    void mouseMoved();
};
#endif // WIDGET_H
