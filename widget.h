/* This file is path of the Caligo multimedia player
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
#include <Widgets/radiolibrary.h>
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

protected:
    virtual void closeEvent(QCloseEvent *) override;
    virtual void dragEnterEvent(QDragEnterEvent *e) override;
    virtual void dropEvent(QDropEvent *e) override;

private:
    QMediaPlayer *mp;

    Controls *controls;
    PlayInfo *playInfo;
    Playlist *playlist;
    PlaylistControls *plControls;

    MediaLibrary *library;
    RadioLibrary *radioLibrary;
    LibraryPlaylists *playlistLibrary;

    QSplitter *spl;
    QWidget *sw;

    QSettings *settings;

    void loadSettings();

    void recursiveEntryPoints(QDir d);
    QStringList droppedFiles;

    AboutWindow *aboutWindow;
    HelpWindow *helpWindow;
    SettingsWindow *settingsWindow;

    QTabWidget *tabWidget;

private slots:
    void setNewTitle(const QString &s);
    void help();

    void videoFullscreen();
    void exitFull();
};
#endif // WIDGET_H
