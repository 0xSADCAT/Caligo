/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    setWindowIcon(QIcon(":/img/icon"));

    QFile file(qApp->applicationDirPath() + QDir::separator() + "style.qss");
    if (file.open(QIODevice::ReadOnly)) {
        QString qss = file.readAll();
        qApp->setStyleSheet(qss);

        file.close();
    } else {
        qWarning() << "Failed to open stylesheet file: " << file.errorString();
    }

    _media_player = new QMediaPlayer;

    _playback_controls = new Controls(_media_player);
    _playback_info = new PlayInfo(_media_player);
    _playlist = new Playlist(_media_player);
    _playlist_controls = new PlaylistControls(_playlist);

    _tab_widget = new QTabWidget;

    _playback_controls->setSizes(20);
    _playlist_controls->setButtonsSizes(16);

    QVBoxLayout *plL = new QVBoxLayout;
    plL->addWidget(_playlist_controls, 0);
    QScrollArea *sa = new QScrollArea;
    sa->setWidget(_playlist);
    sa->setWidgetResizable(true);
    sa->setFrameStyle(QFrame::NoFrame);
    plL->addWidget(sa, 1);

    sw = new QWidget;
    sw->setLayout(plL);
    sw->layout()->setSpacing(0);
    sw->layout()->setContentsMargins(0, 0, 0, 0);

    _splitter = new QSplitter;
    _splitter->addWidget(_tab_widget);
    _splitter->addWidget(sw);

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(_splitter, 1);
    l->addWidget(_playback_controls, 0);
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);

    setLayout(l);

    _library = new MediaLibrary(_playlist);
    _playlist_library = new LibraryPlaylists(_playlist);

    connect(_playback_controls, &Controls::randomPlaybackChanged, _playlist,
            &Playlist::randomPlaybackChanged);

    _settings = new QSettings(qApp->applicationDirPath() + QDir::separator()
                              + qApp->applicationName() + "_settings.ini", QSettings::IniFormat);
    loadSettings();

    _settings_widget = new SettingsWindow(_settings, _playlist_controls, _library,
                                          _playlist_library, this);
    _about_widget = new AboutWindow;
    _help_widget = new HelpWindow;

    _tab_widget->addTab(_playback_info, tr("Now Playing"));
    _tab_widget->addTab(_library, tr("Media library"));
    _tab_widget->addTab(_playlist_library, tr("Playlists"));
    _tab_widget->addTab(_settings_widget, tr("Settings"));
    _tab_widget->addTab(_about_widget, tr("About"));
    _tab_widget->addTab(_help_widget, tr("Help"));

    _tab_widget->setTabBarAutoHide(true);

    _tab_widget->autoFillBackground();

    connect(_playback_controls, &Controls::next, _playlist, &Playlist::next);
    connect(_playback_controls, &Controls::prev, _playlist, &Playlist::previous);

    connect(_playback_info, &PlayInfo::newTitle, this, &MainWindow::setNewWindowTitle);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);

    _playlist->setFocus();

    this->setAcceptDrops(true);

    connect(_playback_info, &PlayInfo::fullScreenClicked, this, &MainWindow::videoFullscreen);
    connect(_playback_controls, &Controls::fullScreen, this, &MainWindow::videoFullscreen);

    QShortcut* key_full_screen = new QShortcut(QKeySequence("F"), this);
    connect(key_full_screen, &QShortcut::activated, this, &MainWindow::videoFullscreen);

    QShortcut* key_exit_fullscreen = new QShortcut(QKeySequence("Esc"), this);
    connect(key_exit_fullscreen, &QShortcut::activated, this, &MainWindow::exitFull);

    QShortcut* key_next = new QShortcut(QKeySequence("N"), this);
    connect(key_next, &QShortcut::activated, _playback_controls, &Controls::next);

    QShortcut* key_previous = new QShortcut(QKeySequence("B"), this);
    connect(key_previous, &QShortcut::activated, _playback_controls, &Controls::prev);

    QShortcut* key_play = new QShortcut(QKeySequence("P"), this);
    connect(key_play, &QShortcut::activated, _playback_controls, &Controls::playPause);

    QShortcut* key_stop = new QShortcut(QKeySequence("S"), this);
    connect(key_stop, &QShortcut::activated, _playback_controls, &Controls::stop);

    QShortcut* key_mute = new QShortcut(QKeySequence("CTRL+M"), this);
    connect(key_mute, &QShortcut::activated, _playback_controls, &Controls::mute);

    QShortcut* key_volume_plus = new QShortcut(QKeySequence(Qt::Key_Plus), this);
    connect(key_volume_plus, &QShortcut::activated, _playback_controls, &Controls::plusVolume);

    QShortcut* key_volume_minus = new QShortcut(QKeySequence(Qt::Key_Minus), this);
    connect(key_volume_minus, &QShortcut::activated, _playback_controls, &Controls::minusVolume);

    QShortcut* key_help = new QShortcut(QKeySequence("CTRL+H"), this);
    connect(key_help, &QShortcut::activated, this, &MainWindow::help);

    _fullscreen_timer = new QTimer(this);
    connect(_fullscreen_timer, &QTimer::timeout, this, &MainWindow::timerTick);
    _fullscreen_timer->setInterval(500);

    _timer_value = 6; // 3 sec

    setMouseTracking(true);
    _playback_info->setMouseTracking(true);

    connect(_playback_info, &PlayInfo::mouseMoved, this, &MainWindow::mouseMoved);
    connect(_playback_controls, &Controls::mouseMoved, this, &MainWindow::mouseMoved);
}

void MainWindow::addToPlaylist(const QString &path)
{
    _playlist->add(path);
}

void MainWindow::forceUpdatePlaylistMetadata()
{
    _playlist->forceUpdate();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    _library->save();

    _settings->setValue("windowConfig/size", this->size());
    _settings->setValue("windowConfig/position", this->pos());
    _settings->setValue("windowConfig/splitterLeft", this->_splitter->sizes()[0]);
    _settings->setValue("windowConfig/splitterRight", this->_splitter->sizes()[1]);
    _settings->setValue("other/volume", this->_playback_controls->volume());
    _settings->setValue("other/playlist", this->_playlist->toStringList());
    _settings->setValue("playback/random", this->_playback_controls->isRandomPlayback());

    /* Hide error code 139 */
    _settings->~QSettings();
    std::exit(0);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    _droppedFiles.clear();

    foreach (QUrl url, urls) {
        QApplication::processEvents();
        if (url.isLocalFile()) {
            QString path = QDir::toNativeSeparators(url.path());

#ifdef Q_OS_WINDOWS
            if (path.startsWith("/") or path.startsWith("\\"))
                path.remove(0, 1);
            path.replace("/", "\\");
#endif

            QFileInfo file_info(path);
            if (file_info.isDir()) {
                QDir dir(path);
                recursiveEntryPoints(dir);
            }
            else {
                _droppedFiles << path;
            }
        }
    }

    if (not _droppedFiles.isEmpty()) {
        QString mime_type = "";
        foreach (QString file, _droppedFiles) {
            mime_type = QMimeDatabase().mimeTypeForFile(file).name();
            if (not mime_type.contains("audio/")
                and not mime_type.contains("video/")
                and not file.endsWith(".cpl")) {
                _droppedFiles.removeAll(file);
            }
        }

        _playlist->add(_droppedFiles);
        _droppedFiles.clear();
    }
}

void MainWindow::mouseMoved()
{
    if (not isFullScreen())
        return;

    _timer_value = _TIMER_BASE_VALUE;
    unsetCursor();
    _playback_controls->setVisible(true);
    if (not _fullscreen_timer->isActive())
        _fullscreen_timer->start();
}

void MainWindow::loadSettings()
{
    resize(qvariant_cast<QSize>(_settings->value("windowConfig/size")));
    move(qvariant_cast<QPoint>(
             _settings->value(
                 "windowConfig/position", QPoint(
                     qApp->desktop()->width()/3, qApp->desktop()->height()/3)
                 )
             )
         );

    QList<int> splitter_sizes;
    splitter_sizes << qvariant_cast<int>(_settings->value("windowConfig/splitterLeft", 0));
    splitter_sizes << qvariant_cast<int>(_settings->value("windowConfig/splitterRight", 0));
    if (splitter_sizes[0] != 0 or splitter_sizes[1] != 0)
        _splitter->setSizes(splitter_sizes);

    _playback_controls->setVolume(qvariant_cast<int>(_settings->value("other/volume", 50)));
    _playback_controls->setRandomPlayback(qvariant_cast<bool>(_settings->value("playback/random",
                                                                               false)));

    bool load_old = qvariant_cast<bool>(_settings->value("other/loadOld", false));
    if (load_old and qApp->arguments().count() == 1) {
        QStringList old_playlist = qvariant_cast<QStringList>(_settings->value("other/playlist"));

        bool need_scan = false;
        for (auto& media_file : old_playlist) {
            QStringList splitted_media_file = media_file.split(" ## ");
            if (splitted_media_file.count() == 1) {
                _playlist->add(splitted_media_file[0]);
                need_scan = true;
            }
            else {
                if (splitted_media_file[1] == " ") {
                    _playlist->add(splitted_media_file[0]);
                    need_scan = true;
                }
                else {
                    _playlist->add(splitted_media_file[0], splitted_media_file[1]);
                }
            }
        }

        if (need_scan)
            _playlist->forceUpdate();
    } else if (qApp->arguments().count() != 1) {
        QStringList media_files;

        for (auto& arg : qApp->arguments()) {
            if (QFile(arg).exists()
                and (QMimeDatabase().mimeTypeForFile(arg).name().contains("audio/")
                     or QMimeDatabase().mimeTypeForFile(arg).name().contains("video/")
                     or QMimeDatabase().mimeTypeForFile(arg).name().endsWith(".cpl"))
                ) {
                qApp->processEvents();
                media_files << arg;
            }
        }
        _playlist->add(media_files);
    }

    _playlist_library->scan();
}

void MainWindow::recursiveEntryPoints(QDir dir)
{
    QApplication::processEvents();

    QStringList files = dir.entryList(QDir::Files);
    for (auto& file : files)
        _droppedFiles << dir.absoluteFilePath(file);

    QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for(auto& dir_path : dirs) {
        recursiveEntryPoints(QDir(dir.absoluteFilePath(dir_path)));
    }
}

void MainWindow::setNewWindowTitle(const QString& title)
{
    setWindowTitle(title);
}

void MainWindow::help()
{
    _tab_widget->setCurrentIndex(_tab_widget->count() - 1);
}

void MainWindow::videoFullscreen()
{
    if (not _media_player->isVideoAvailable()) {
        if (not this->isFullScreen())
            return;
    }

    bool v = not sw->isVisible();

    sw->setVisible(v);
    _playback_info->setMediaTitleVisible(v);

    if (v) {
        showNormal();
        _tab_widget->tabBar()->setVisible(true);
        _playback_controls->setVisible(true);
        unsetCursor();
        _fullscreen_timer->stop();
    }
    else {
        showFullScreen();
        _tab_widget->tabBar()->setVisible(false);
        _timer_value = _TIMER_BASE_VALUE;
        _fullscreen_timer->start();
    }
}

void MainWindow::exitFull()
{
    if (isFullScreen())
        videoFullscreen();
}

void MainWindow::timerTick()
{
    if (not isFullScreen()) {
        _fullscreen_timer->stop();
        _tab_widget->tabBar()->setVisible(true);
        _playback_controls->setVisible(true);
        unsetCursor();
        return;
    }

    _timer_value--;

    if (_timer_value < 0) {
        _timer_value = _TIMER_BASE_VALUE;
        _fullscreen_timer->stop();
        _playback_controls->setVisible(false);
        setCursor(Qt::BlankCursor);
    }
}
