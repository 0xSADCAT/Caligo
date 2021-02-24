/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtWidgets>

#include <Widgets/playlistcontrols.h>
#include <Widgets/medialibrary.h>
#include <Widgets/radiolibrary.h>
#include <Widgets/libraryplaylists.h>

#include <Style/style.cpp>

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QSettings *s, PlaylistControls *pc, MediaLibrary *ml, RadioLibrary *rl, LibraryPlaylists *pl, QWidget *wgt);

private:
    QSettings *settings;
    PlaylistControls *listControls;
    QWidget *widget;

    MediaLibrary *mediaLibrary;
    RadioLibrary *radioLibrary;
    LibraryPlaylists *playlistLibrary;

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

    QLabel *pathRadioLabel;
    QLabel *pathRadioValue;
    QPushButton *setPathRadioButton;
    QPushButton *setDefaultPathRadioButton;

    QCheckBox *clearBeforeOpenPlaylistCheck;

    QCheckBox *loadOldCheck;

//    QCheckBox *darkThemeCheck;

private slots:
    void pathMusic();
    void pathMusicDefault();

    void pathList();
    void pathListDefault();

    void pathRadio();
    void pathRadioDefault();

    void clearBeforeOpen(bool v);

    void loadOld(bool v);

//    void darkTheme(bool v);
};

#endif // SETTINGSWINDOW_H
