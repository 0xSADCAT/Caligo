/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "playlistcontrols.h"

PlaylistControls::PlaylistControls(Playlist *pl, QWidget *parent) : QWidget(parent)
{
#ifdef DEBUG_OUTPUT
        qDebug() << ">>> PlaylistControls init";
#endif

    playlist = pl;
    pathMusic = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    pathPlaylists = qApp->applicationDirPath() + QDir::separator() + "playlists";

    QDir d;
    if (not d.exists(pathPlaylists)) {
        d.mkpath(pathPlaylists);
    }

    addButton = new QPushButton;
    addUrlButton = new QPushButton;
    clearButton = new QPushButton;

    savePlaylist = new QPushButton;
    loadPlaylist = new QPushButton;

    forceScanButton = new QPushButton;

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(addButton, 0);
    l->addSpacing(10);
    l->addWidget(addUrlButton, 0);
    l->addStretch(1);
    l->addWidget(loadPlaylist, 0);
    l->addSpacing(10);
    l->addWidget(savePlaylist, 0);
    l->addStretch(1);
    l->addWidget(forceScanButton, 0);
    l->addStretch(1);
    l->addWidget(clearButton, 0);
    setLayout(l);

    addButton->setIcon(QIcon(":/img/openFile"));
    addUrlButton->setIcon(QIcon(":/img/openUrl"));
    clearButton->setIcon(QIcon(":/img/clear"));

    savePlaylist->setIcon(QIcon(":/img/save"));
    loadPlaylist->setIcon(QIcon(":/img/load"));

    forceScanButton->setIcon(QIcon(":/img/update"));

    addButton->setToolTip(tr("Add media") + " [Ctrl+O]");
    addUrlButton->setToolTip(tr("Add media from URL") + " [Ctrl+U]");
    clearButton->setToolTip(tr("Clear playlist") + " [Ctrl+Shift+C]");
    savePlaylist->setToolTip(tr("Save this playlist") + " [Ctrl+Shift+S]");
    loadPlaylist->setToolTip(tr("Open playlist") + " [Shift+O]");
    forceScanButton->setToolTip(tr("Update metadata") + " [Shift+U]");

    connect(addButton, &QPushButton::clicked, this, &PlaylistControls::add);
    connect(addUrlButton, &QPushButton::clicked, this, &PlaylistControls::addUrl);
    connect(clearButton, &QPushButton::clicked, this, &PlaylistControls::clear);
    connect(savePlaylist, &QPushButton::clicked, this, &PlaylistControls::save);
    connect(loadPlaylist, &QPushButton::clicked, this, &PlaylistControls::load);
    connect(forceScanButton, &QPushButton::clicked, playlist, &Playlist::forceUpdate);

    connect(playlist, &Playlist::loadPlaylist, this, &PlaylistControls::loadPath);

    clearBeforeOpen = false;

    /* Hotkeys */

    QShortcut *sAdd = new QShortcut(QKeySequence("CTRL+O"), this);
    connect(sAdd, &QShortcut::activated, this, &PlaylistControls::add);

    QShortcut *sLoad = new QShortcut(QKeySequence("Shift+O"), this);
    connect(sLoad, &QShortcut::activated, this, &PlaylistControls::load);

    QShortcut *sSave = new QShortcut(QKeySequence("CTRL+Shift+S"), this);
    connect(sSave, &QShortcut::activated, this, &PlaylistControls::save);

    QShortcut *sClear = new QShortcut(QKeySequence("CTRL+Shift+C"), this);
    connect(sClear, &QShortcut::activated, this, &PlaylistControls::clear);

    QShortcut *sOpenUrl = new QShortcut(QKeySequence("Ctrl+U"), this);
    connect(sOpenUrl, &QShortcut::activated, this, &PlaylistControls::addUrl);

    QShortcut *sForceUpdate = new QShortcut(QKeySequence("Shift+U"), this);
    connect(sForceUpdate, &QShortcut::activated, playlist, &Playlist::forceUpdate);
}

void PlaylistControls::setSizes(int v)
{
    if (v < 16)
        return;

    QSize s(v, v);

    addButton->setIconSize(s);
    addUrlButton->setIconSize(s);
    clearButton->setIconSize(s);
    savePlaylist->setIconSize(s);
    loadPlaylist->setIconSize(s);
    forceScanButton->setIconSize(s);
}

void PlaylistControls::setClearBeforeOpen(bool value)
{
    clearBeforeOpen = value;
}

QString PlaylistControls::getPathPlaylists() const
{
    return pathPlaylists;
}

void PlaylistControls::setPathPlaylists(const QString &value)
{
    pathPlaylists = value;
}

QString PlaylistControls::getPathMusic() const
{
    return pathMusic;
}

void PlaylistControls::setPathMusic(const QString &value)
{
    pathMusic = value;
}

/* private SLOT */ void PlaylistControls::loadPath(const QString &path)
// Loads playlist from path to file
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT PlaylistControls::loadPath" << path;
#endif

    QStringList paths;
    QStringList names;
    QString s;
    QFile f;
    f.setFileName(path);
    if (f.open(QIODevice::ReadOnly)) {
        while (not f.atEnd()) {
            s = f.readLine();
            s.remove("\n");
            if (not s.isEmpty() and not s.startsWith("#")) {
                QString path;
                QString name = "";
                QStringList splitted = s.split(" ## ");
                path = splitted[0];
                if (splitted.count() > 1) {
                    name = splitted[1];
                }
                QFile tf(path);
                if (tf.exists()) {
                    paths << path;
                    names << name;
                }
            }
        }
        f.close();
    }
    else {
        QMessageBox::warning(0, tr("Warning") + " # " + qApp->applicationName(), tr("Failed to open file, check access rights."));
    }

#ifdef DEBUG_OUTPUT
        qDebug() << "Playlist:";
        qDebug() << l;
#endif

    if (not paths.isEmpty()) {
        if (clearBeforeOpen) {
            playlist->clear();
        }
        for (int i = 0; i < paths.count(); ++i) {
            playlist->add(paths[i], names[i]);
        }
    }
}

/* private SLOT */ void PlaylistControls::add()
{
    QStringList l = QFileDialog::getOpenFileNames(0, tr("Add media files") + " # " + qApp->applicationName(), pathMusic);
    playlist->add(l);

#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT PlaylistControls::add";
        qDebug() << "Selected paths:";
        qDebug() << l;
#endif
}

void PlaylistControls::addUrl()
{
    bool isOk;
    QString url = QInputDialog::getText(0, tr("Add from URL") + " # " + qApp->applicationName(), tr("Enter URL:"),
                                        QLineEdit::Normal, "", &isOk);
    if (not isOk) {
        // Cancel clicked
        return;
    }
    if (not url.isEmpty() and url.startsWith("http")) {
        playlist->add(url, true);
    }
}

/* private SLOT */ void PlaylistControls::clear()
{
    playlist->clear();
}

/* private SLOT */ void PlaylistControls::save()
// Save current playlist.
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT PlaylistControls::save()";
#endif

    QStringList l;
    l << "# Caligo playlist :: Do not edit this file by yourself!";
    l << playlist->getList();
    if (l.count() < 2) {
        return;
    }

    bool isOk;
    QString str = QInputDialog::getText(0, tr("Save playlist") + " # " + qApp->applicationName(), tr("Enter playlist name:"),
                                        QLineEdit::Normal, "", &isOk);
    if (not isOk) {
        // Cancel clicked
        return;
    }
    if (str.isEmpty()) {
        QMessageBox::warning(0, tr("Warning") + " # " + qApp->applicationName(), tr("Playlist name is not entered. Try again."));
        save();
        return;
    }

    if (not str.endsWith(".cpl")) {
        str += ".cpl";
    }
    str = pathPlaylists + QDir::separator() + str;

    QFile file;
    file.setFileName(str);

    // Rewrite file if exists
    bool rewrite = true;
    if (file.exists()) {
        int n = QMessageBox::warning(0, tr("Warning") + " # " + qApp->applicationName(), tr("File name is already exists. Rewrite?"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (n == QMessageBox::Yes) {
            rewrite = true;
        }
        else {
            rewrite = false;
        }
    }

    if (file.open(QIODevice::WriteOnly)) {
        // If file exists and choosed 'Yes' on question 'Rewrite?'
        if (rewrite) {
            QTextStream stream(&file);
            foreach (QString s, l) {
                stream << s + "\n";
            }
        }

        file.close();

        // If file exists and choosed 'No' on question 'Rewrite?'
        if (not rewrite) {
            save();
            return;
        }
    }
    else {
        QMessageBox::warning(0, tr("Warning") + " # " + qApp->applicationName(), tr("Failed to create file, check access rights."));
    }
}

/* private SLOT */ void PlaylistControls::load()
// Load playlist from file (dialog)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "SLOT PlaylistControls::load()";
#endif

    QString path = QFileDialog::getOpenFileName(0, tr("Open playlist") + " # " + qApp->applicationName(), pathPlaylists);

#ifdef DEBUG_OUTPUT
        qDebug() << "Loaded:";
        qDebug() << path;
#endif

    if (path.isEmpty())
        return;

    loadPath(path);
}
