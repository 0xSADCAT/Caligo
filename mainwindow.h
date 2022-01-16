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
#include <Widgets/playlistwidget.hpp>
#include <Widgets/medialibrary.h>
#include <Widgets/libraryplaylists.h>

#include <OtherWindows/aboutwindow.h>
#include <OtherWindows/helpwindow.h>
#include <OtherWindows/settingswindow.h>

/**
 * @brief The MainWindow class provides application window
 */
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief The MainWindow class provides application window
     */
    MainWindow(QWidget* parent = nullptr);

    /**
     * @brief App media to playlist
     * @param path Path to file
     */
    void addToPlaylist(const QString& path);

    /**
     * @brief Update metadata in playlist
     */
    void forceUpdatePlaylistMetadata();

protected:
    void closeEvent(QCloseEvent*) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void loadSettings();

    void createShortcuts();

    void recursiveEntryPoints(QDir dir);

    QMediaPlayer* _media_player;

    PlaylistWidget* _playlist_widget;

    Controls* _playback_controls;
    PlayInfo* _playback_info;

    MediaLibrary* _library;
    LibraryPlaylists* _playlist_library;

    QSplitter* _splitter = new QSplitter;

    QSettings* _settings = new QSettings(qApp->applicationDirPath() + QDir::separator()
                                         + qApp->applicationName() + "_settings.ini",
                                         QSettings::IniFormat);

    SettingsWindow* _settings_widget;

    AboutWindow* _about_widget = new AboutWindow;
    HelpWindow* _help_widget = new HelpWindow;
    QTabWidget* _tab_widget = new QTabWidget;

    QStringList _droppedFiles;

    QTimer* _fullscreen_timer;
    const int _TIMER_BASE_VALUE = 6;
    int _timer_value = _TIMER_BASE_VALUE;

private slots:
    void setNewWindowTitle(const QString& title);
    void help();

    void videoFullscreen();

    void exitFull();

    void timerTick();

    void mouseMoved();
};
#endif // WIDGET_H
