/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "playlistcontrols.h"

PlaylistControls::PlaylistControls(Playlist* playlist, QWidget* parent)
    : QWidget(parent),
      _playlist(playlist)
{
    QDir playlists_dir;
    if (not playlists_dir.exists(_playlists_path))
        playlists_dir.mkpath(_playlists_path);

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addWidget(_add_button, 0);
    main_layout->addSpacing(5);

    main_layout->addWidget(_add_from_url_button, 0);
    main_layout->addStretch(1);
    main_layout->addSpacing(5);

    main_layout->addWidget(_load_playlist_button, 0);
    main_layout->addSpacing(5);

    main_layout->addWidget(_save_playlist_button, 0);
    main_layout->addStretch(1);
    main_layout->addSpacing(5);

    main_layout->addWidget(_scan_all_button, 0);
    main_layout->addSpacing(5);

    main_layout->addWidget(_clear_button, 0);
    setLayout(main_layout);

    _add_button->setIcon(QIcon(":/img/openFile"));
    _add_from_url_button->setIcon(QIcon(":/img/openUrl"));
    _clear_button->setIcon(QIcon(":/img/clear"));

    _save_playlist_button->setIcon(QIcon(":/img/save"));
    _load_playlist_button->setIcon(QIcon(":/img/load"));

    _scan_all_button->setIcon(QIcon(":/img/update"));

    _add_button->setToolTip(tr("Add media") + " [Ctrl+O]");
    _add_from_url_button->setToolTip(tr("Add media from URL") + " [Ctrl+U]");
    _clear_button->setToolTip(tr("Clear playlist") + " [Ctrl+Shift+C]");
    _save_playlist_button->setToolTip(tr("Save this playlist") + " [Ctrl+Shift+S]");
    _load_playlist_button->setToolTip(tr("Open playlist") + " [Shift+O]");
    _scan_all_button->setToolTip(tr("Update metadata") + " [Shift+U]");

    connect(_add_button, &QPushButton::clicked, this, &PlaylistControls::add);
    connect(_add_from_url_button, &QPushButton::clicked, this, &PlaylistControls::addUrl);
    connect(_clear_button, &QPushButton::clicked, this, &PlaylistControls::clear);
    connect(_save_playlist_button, &QPushButton::clicked, this, &PlaylistControls::save);
    connect(_load_playlist_button, &QPushButton::clicked, this, &PlaylistControls::load);
    connect(_scan_all_button, &QPushButton::clicked, _playlist, &Playlist::forceUpdate);

    connect(_playlist, &Playlist::loadPlaylist, this, &PlaylistControls::loadPath);

    _is_clear_before_open = false;

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
    connect(sForceUpdate, &QShortcut::activated, _playlist, &Playlist::forceUpdate);
}

void PlaylistControls::setButtonsSizes(int size)
{
    assert(size >= 16 and size <= 128);

    QSize button_size(size, size);

    _add_button->setIconSize(button_size);
    _add_from_url_button->setIconSize(button_size);
    _clear_button->setIconSize(button_size);
    _save_playlist_button->setIconSize(button_size);
    _load_playlist_button->setIconSize(button_size);
    _scan_all_button->setIconSize(button_size);
}

void PlaylistControls::setClearBeforeOpen(bool value)
{
    _is_clear_before_open = value;
}

QString PlaylistControls::getPathPlaylists() const
{
    return _playlists_path;
}

void PlaylistControls::setPathPlaylists(const QString &value)
{
    _playlists_path = value;
}

QString PlaylistControls::getPathMusic() const
{
    return _music_path;
}

void PlaylistControls::setPathMusic(const QString &value)
{
    _music_path = value;
}

void PlaylistControls::loadPath(const QString& path)
{
    QStringList paths;
    QStringList names;
    QString s;
    QFile f;
    f.setFileName(path);
    if (f.open(QIODevice::ReadOnly)) {
        while (not f.atEnd()) {
            s = QString::fromLocal8Bit(f.readLine());
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
    } else {
        QMessageBox::warning(0, tr("Warning") + " # " + qApp->applicationName(),
                             tr("Failed to open file, check access rights."));
    }

    if (not paths.isEmpty()) {
        if (_is_clear_before_open) {
            _playlist->clear();
        }
        for (int i = 0; i < paths.count(); ++i) {
            _playlist->add(paths[i], names[i]);
        }
    }
}

void PlaylistControls::add()
{
    QStringList file_paths = QFileDialog::getOpenFileNames(0,
                                                  tr("Add media files") + " # " +
                                                  qApp->applicationName(), _music_path);
    _playlist->add(file_paths);
}

void PlaylistControls::addUrl()
{
    bool is_ok;
    QString url = QInputDialog::getText(0, tr("Add from URL") + " # " + qApp->applicationName(),
                                        tr("Enter URL:"), QLineEdit::Normal, "", &is_ok);

    if (is_ok and not url.isEmpty() and url.startsWith("http"))
        _playlist->add(url, true);
}

void PlaylistControls::clear()
{
    _playlist->clear();
}

void PlaylistControls::save()
{
    QStringList list;
    list << "# Caligo playlist :: Do not edit this file by yourself!";
    list << _playlist->toStringList();
    if (list.count() < 2)
        return;

    bool is_ok;
    QString str = QInputDialog::getText(0, tr("Save playlist") + " # " + qApp->applicationName(),
                                        tr("Enter playlist name:"), QLineEdit::Normal, "", &is_ok);
    if (not is_ok)
        return;

    if (str.isEmpty()) {
        QMessageBox::warning(0, tr("Warning") + " # " + qApp->applicationName(),
                             tr("Playlist name is not entered. Try again."));
        save();
        return;
    }

    if (not str.endsWith(".cpl"))
        str += ".cpl";

    str = _playlists_path + QDir::separator() + str;

    QFile file;
    file.setFileName(str);

    bool rewrite = true;
    if (file.exists()) {
        int rewrite_answer = QMessageBox::warning(0, tr("Warning") + " # "
                                                  + qApp->applicationName(),
                                                  tr("File name is already exists. Rewrite?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes);
        if (rewrite_answer == QMessageBox::Yes)
            rewrite = true;
        else
            rewrite = false;
    }

    if (file.open(QIODevice::WriteOnly)) {
        if (rewrite) {
            QTextStream stream(&file);
            QString endl;
            foreach (QString s, list) {
                stream << s + endl;
            }
        }

        file.close();

        if (not rewrite) {
            save();
            return;
        }
    }
    else {
        QMessageBox::warning(0, tr("Warning") + " # " + qApp->applicationName(),
                             tr("Failed to create file, check access rights."));
    }
}

void PlaylistControls::load()
{
    QString path = QFileDialog::getOpenFileName(0, tr("Open playlist") + " # "
                                                + qApp->applicationName(), _playlists_path);

    if (path.isEmpty())
        return;

    loadPath(path);
}
