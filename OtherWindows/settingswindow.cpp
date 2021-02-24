/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "settingswindow.h"

SettingsWindow::SettingsWindow(QSettings *s, PlaylistControls *pc, MediaLibrary *ml, RadioLibrary *rl, LibraryPlaylists *pl, QWidget *wgt)
    : QWidget(nullptr)
{
    setWindowIcon(QIcon(":/img/icon"));

    setWindowTitle(tr("Settings") + " # " + qApp->applicationName());

    settings = s;
    listControls = pc;
    widget = wgt;

    mediaLibrary = ml;
    radioLibrary = rl;
    playlistLibrary = pl;

    l = new QVBoxLayout;
    setLayout(l);

    pathMusicLabel = new QLabel(tr("Music library path:"));
    pathMusicValue = new QLabel;
    setPathMusicButton = new QPushButton;
    setPathMusicButton->setToolTip(tr("Select directory"));
    setPathMusicButton->setIcon(QIcon(":/img/dir"));
    setDefaultPathMusicButton = new QPushButton;
    setDefaultPathMusicButton->setToolTip(tr("Set default path"));
    setDefaultPathMusicButton->setIcon(QIcon(":/img/update"));
    connect(setPathMusicButton, &QPushButton::clicked, this, &SettingsWindow::pathMusic);
    connect(setDefaultPathMusicButton, &QPushButton::clicked, this, &SettingsWindow::pathMusicDefault);
    /* Add this layout to main layout */
    QHBoxLayout *pathMusicLayout = new QHBoxLayout;
    /* */
    QVBoxLayout *pathMusicLabelsLayout = new QVBoxLayout;
    pathMusicLabelsLayout->addWidget(pathMusicLabel, 0);
    pathMusicLabelsLayout->addWidget(pathMusicValue, 0);
    pathMusicLabelsLayout->setSpacing(0);
    pathMusicLabelsLayout->setContentsMargins(0, 0, 0, 0);
    pathMusicLayout->addLayout(pathMusicLabelsLayout, 1);
    pathMusicLayout->addWidget(setPathMusicButton, 0);
    pathMusicLayout->addWidget(setDefaultPathMusicButton, 0);

    pathListLabel = new QLabel(tr("Playlists path:"));
    pathListValue = new QLabel;
    setPathListButton = new QPushButton;
    setPathListButton->setToolTip(tr("Select directory"));
    setPathListButton->setIcon(QIcon(":/img/dir"));
    setDefaultPathListButton = new QPushButton;
    setDefaultPathListButton->setToolTip(tr("Set default path"));
    setDefaultPathListButton->setIcon(QIcon(":/img/update"));
    connect(setPathListButton, &QPushButton::clicked, this, &SettingsWindow::pathList);
    connect(setDefaultPathListButton, &QPushButton::clicked, this, &SettingsWindow::pathListDefault);
    /* Add this layout to main layout */
    QHBoxLayout *pathListLayout = new QHBoxLayout;
    /* */
    QVBoxLayout *pathListLabelsLayout = new QVBoxLayout;
    pathListLabelsLayout->addWidget(pathListLabel, 0);
    pathListLabelsLayout->addWidget(pathListValue, 0);
    pathListLabelsLayout->setSpacing(0);
    pathListLabelsLayout->setContentsMargins(0, 0, 0, 0);
    pathListLayout->addLayout(pathListLabelsLayout, 1);
    pathListLayout->addWidget(setPathListButton, 0);
    pathListLayout->addWidget(setDefaultPathListButton, 0);

    pathRadioLabel = new QLabel(tr("Radio lists path:"));
    pathRadioValue = new QLabel;
    setPathRadioButton = new QPushButton;
    setPathRadioButton->setToolTip(tr("Select directory"));
    setPathRadioButton->setIcon(QIcon(":/img/dir"));
    setDefaultPathRadioButton = new QPushButton;
    setDefaultPathRadioButton->setToolTip(tr("Set default path"));
    setDefaultPathRadioButton->setIcon(QIcon(":/img/update"));
    connect(setPathRadioButton, &QPushButton::clicked, this, &SettingsWindow::pathRadio);
    connect(setDefaultPathRadioButton, &QPushButton::clicked, this, &SettingsWindow::pathRadioDefault);
    /* Add this layout to main layout */
    QHBoxLayout *pathRadioLayout = new QHBoxLayout;
    /* */
    QVBoxLayout *pathRadioLabelsLayout = new QVBoxLayout;
    pathRadioLabelsLayout->addWidget(pathRadioLabel, 0);
    pathRadioLabelsLayout->addWidget(pathRadioValue, 0);
    pathRadioLabelsLayout->setSpacing(0);
    pathRadioLabelsLayout->setContentsMargins(0, 0, 0, 0);
    pathRadioLayout->addLayout(pathRadioLabelsLayout, 1);
    pathRadioLayout->addWidget(setPathRadioButton, 0);
    pathRadioLayout->addWidget(setDefaultPathRadioButton, 0);

    clearBeforeOpenPlaylistCheck = new QCheckBox;
    connect(clearBeforeOpenPlaylistCheck, &QCheckBox::toggled, this, &SettingsWindow::clearBeforeOpen);
    QLabel *clearBeforeOpenListLabel = new QLabel(tr("Clear current playlist before open playlist"));
    /* Add this layout to main layout */
    QHBoxLayout *clearBedoreOpenListLayout = new QHBoxLayout;
    /* */
    clearBedoreOpenListLayout->addWidget(clearBeforeOpenListLabel, 1);
    clearBedoreOpenListLayout->addWidget(clearBeforeOpenPlaylistCheck, 0);

    loadOldCheck = new QCheckBox;
    connect(loadOldCheck, &QCheckBox::toggled, this, &SettingsWindow::loadOld);
    QLabel *loadOldLabel = new QLabel(tr("Load old playlist on start application"));
    QHBoxLayout *loadOldLayout = new QHBoxLayout;
    loadOldLayout->addWidget(loadOldLabel, 1);
    loadOldLayout->addWidget(loadOldCheck, 0);

//    darkThemeCheck = new QCheckBox;
//    connect(darkThemeCheck, &QCheckBox::toggled, this, &SettingsWindow::darkTheme);
//    QLabel *darkThemeLabel = new QLabel(tr("Use dark theme"));
//    QHBoxLayout *darkThemeLayout = new QHBoxLayout;
//    darkThemeLayout->addWidget(darkThemeLabel, 1);
//    darkThemeLayout->addWidget(darkThemeCheck, 0);

    /* start adding elements to main layout */
    l->addLayout(pathMusicLayout, 0);
    l->addLayout(pathListLayout, 0);
    l->addLayout(pathRadioLayout, 0);
    l->addLayout(clearBedoreOpenListLayout, 0);
    l->addLayout(loadOldLayout, 0);
//    l->addLayout(darkThemeLayout, 0);
    /* end adding elements to main layout */

    l->addStretch(1); /* cosmetic */

    QScrollArea *sa = new QScrollArea;
    QWidget *w = new QWidget;
    w->setLayout(l);
    sa->setWidget(w);
    sa->setWidgetResizable(true);
    QVBoxLayout *la = new QVBoxLayout;
    la->addWidget(sa);
    setLayout(la);

    setState();
}

void SettingsWindow::setState()
{
    if (pathMusicValue->text().isEmpty()) {
        pathMusicValue->setText(listControls->getPathMusic());
    }

    if (pathListValue->text().isEmpty()) {
        pathListValue->setText(listControls->getPathPlaylists());
    }

    QString pm = qvariant_cast<QString>(settings->value("path/music", ""));
    if (not pm.isEmpty()) {
        listControls->setPathMusic(pm);
        mediaLibrary->setLibraryPath(pm);
        pathMusicValue->setText(pm);
    }

    QString pl = qvariant_cast<QString>(settings->value("path/lists", ""));
    if (not pl.isEmpty()) {
        listControls->setPathPlaylists(pl);
        playlistLibrary->setPathPlaylists(pl);
        pathListValue->setText(pl);
    }

    QString rl = qvariant_cast<QString>(settings->value("path/radio", ""));
    if (not rl.isEmpty()) {
        radioLibrary->setRadioPath(rl);
        pathRadioValue->setText(rl);
    }

    bool cbop = qvariant_cast<bool>(settings->value("other/clearBeforeOpenPlaylist", true));
    clearBeforeOpenPlaylistCheck->setChecked(cbop);
    listControls->setClearBeforeOpen(cbop);
    playlistLibrary->setClearBeforeOpen(cbop);

    loadOldCheck->setChecked(qvariant_cast<bool>(settings->value("other/loadOld", false)));

//    darkThemeCheck->setChecked(qvariant_cast<bool>(settings->value("other/darkTheme", false)));
//    darkTheme(darkThemeCheck->isChecked());
}

void SettingsWindow::pathMusic()
{
    QString str = QFileDialog::getExistingDirectory(0, tr("Select directory") + " # " + qApp->applicationName(), listControls->getPathMusic());
    if (str.isEmpty())
        return;

    listControls->setPathMusic(str);
    pathMusicValue->setText(str);
    mediaLibrary->setLibraryPath(str);

    settings->setValue("path/music", str);
}

void SettingsWindow::pathMusicDefault()
{
    listControls->setPathMusic(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
    pathMusicValue->setText(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
    mediaLibrary->setLibraryPath(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));

    settings->setValue("path/music", QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
}

void SettingsWindow::pathList()
{
    QString str = QFileDialog::getExistingDirectory(0, tr("Select directory") + " # " + qApp->applicationName(), listControls->getPathPlaylists());
    if (str.isEmpty())
        return;

    listControls->setPathPlaylists(str);
    pathListValue->setText(str);
    playlistLibrary->setPathPlaylists(str);

    settings->setValue("path/lists", str);
}

void SettingsWindow::pathListDefault()
{
    listControls->setPathPlaylists(qApp->applicationDirPath() + QDir::separator() + "playlists");
    pathListValue->setText(qApp->applicationDirPath() + QDir::separator() + "playlists");
    playlistLibrary->setPathPlaylists(qApp->applicationDirPath() + QDir::separator() + "playlists");

    settings->setValue("path/lists", qApp->applicationDirPath() + QDir::separator() + "playlists");
}

void SettingsWindow::pathRadio()
{
    QString str = QFileDialog::getExistingDirectory(0, tr("Select directory") + " # " + qApp->applicationName(), radioLibrary->getRadioPath());
    if (str.isEmpty())
        return;

    radioLibrary->setRadioPath(str);
    pathRadioValue->setText(str);

    settings->setValue("path/radio", str);
}

void SettingsWindow::pathRadioDefault()
{
    radioLibrary->setRadioPath(qApp->applicationDirPath() + QDir::separator() + "radio");
    pathRadioValue->setText(qApp->applicationDirPath() + QDir::separator() + "radio");

    settings->setValue("path/radio", qApp->applicationDirPath() + QDir::separator() + "radio");
}

void SettingsWindow::clearBeforeOpen(bool v)
{
    listControls->setClearBeforeOpen(v);
    playlistLibrary->setClearBeforeOpen(v);
    settings->setValue("other/clearBeforeOpenPlaylist", v);
}

void SettingsWindow::loadOld(bool v)
{
    settings->setValue("other/loadOld", v);
}

//void SettingsWindow::darkTheme(bool v)
//{
//    if (v) {
////        Uncomment for design only main window
////        widget->setStyleSheet(style::theme::dark);
//        qApp->setStyleSheet(style::theme::dark);
//    }
//    else {
////        Uncomment for design only main window
////        widget->setStyleSheet(style::theme::light);
//        qApp->setStyleSheet(style::theme::light);
//    }

//    settings->setValue("other/darkTheme", v);
//}
