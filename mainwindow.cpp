/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent),
      _media_player(new QMediaPlayer(this)),
      _playlist_widget(new PlaylistWidget(_media_player)),
      _playback_controls(new Controls(_media_player)),
      _playback_info(new PlayInfo(_media_player)),
      _library(new MediaLibrary(_playlist_widget->playlist())),
      _playlist_library(new LibraryPlaylists(_playlist_widget->playlist())),
      _settings_widget(new SettingsWindow(_settings, _playlist_widget->playlistControls(), _library,
                                          _playlist_library, this))
{
    setWindowIcon(QIcon(":/img/icon"));

    _playback_controls->setSizes(20);

    _splitter->addWidget(_tab_widget);
    _splitter->addWidget(_playlist_widget);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(_splitter, 1);
    main_layout->addWidget(_playback_controls, 0);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);

    loadSettings();

    _tab_widget->addTab(_playback_info, tr("Now Playing"));
    _tab_widget->addTab(_library, tr("Media library"));
    _tab_widget->addTab(_playlist_library, tr("Playlists"));
    _tab_widget->addTab(_settings_widget, tr("Settings"));
    _tab_widget->addTab(_about_widget, tr("About"));
    _tab_widget->addTab(_help_widget, tr("Help"));

    _tab_widget->setTabBarAutoHide(true);
    _tab_widget->autoFillBackground();

    setAcceptDrops(true);
    setMouseTracking(true);

    _fullscreen_timer = new QTimer(this);
    _fullscreen_timer->setInterval(500);

    _playback_info->setMouseTracking(true);

    connect(_playback_controls, &Controls::playbackModeChanged, _playlist_widget->playlist(),
            &Playlist::randomPlaybackChanged);

    connect(_playback_controls, &Controls::nextClicked,
            _playlist_widget->playlist(), &Playlist::next);
    connect(_playback_controls, &Controls::previousClicked,
            _playlist_widget->playlist(), &Playlist::previous);

    connect(_playback_info, &PlayInfo::newTitle, this, &MainWindow::setNewWindowTitle);

    connect(_playback_info, &PlayInfo::fullScreenClicked, this, &MainWindow::videoFullscreen);
    connect(_playback_info, &PlayInfo::mouseMoved, this, &MainWindow::mouseMoved);

    connect(_playback_controls, &Controls::mouseMoved, this, &MainWindow::mouseMoved);
    connect(_playback_controls, &Controls::fullScreenClicked, this, &MainWindow::videoFullscreen);

    connect(_fullscreen_timer, &QTimer::timeout, this, &MainWindow::timerTick);
}

void MainWindow::addToPlaylist(const QString &path)
{
    _playlist_widget->playlist()->add(path);
}

void MainWindow::forceUpdatePlaylistMetadata()
{
    _playlist_widget->playlist()->forceUpdate();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    _library->save();

    _settings->setValue("windowConfig/size", size());
    _settings->setValue("windowConfig/position", pos());
    _settings->setValue("windowConfig/splitterLeft", _splitter->sizes()[0]);
    _settings->setValue("windowConfig/splitterRight", _splitter->sizes()[1]);
    _settings->setValue("other/volume", _playback_controls->volume());
    _settings->setValue("other/playlist", _playlist_widget->playlist()->toStringList());
    _settings->setValue("playback/random", _playback_controls->isRandomPlayback());

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
            } else {
                _droppedFiles << path;
            }
        }
    }

    if (not _droppedFiles.isEmpty()) {
        QString mime_type = "";
        for (auto& file : _droppedFiles) {
            mime_type = QMimeDatabase().mimeTypeForFile(file).name();
            if (not mime_type.contains("audio/")
                and not mime_type.contains("video/")
                and not file.endsWith(".cpl")) {
                _droppedFiles.removeAll(file);
            }
        }

        _playlist_widget->playlist()->add(_droppedFiles);
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
                _playlist_widget->playlist()->add(splitted_media_file[0]);
                need_scan = true;
            }
            else {
                if (splitted_media_file[1] == " ") {
                    _playlist_widget->playlist()->add(splitted_media_file[0]);
                    need_scan = true;
                }
                else {
                    _playlist_widget->playlist()->add(splitted_media_file[0],
                            splitted_media_file[1]);
                }
            }
        }

        if (need_scan)
            _playlist_widget->playlist()->forceUpdate();

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
        _playlist_widget->playlist()->add(media_files);
    }

    _playlist_library->scan();
}

void MainWindow::createShortcuts()
{
    connect(new QShortcut(QKeySequence("F"), this), &QShortcut::activated,
            this, &MainWindow::videoFullscreen);
    connect(new QShortcut(QKeySequence("Esc"), this), &QShortcut::activated,
            this, &MainWindow::exitFull);
    connect(new QShortcut(QKeySequence("CTRL+H"), this), &QShortcut::activated,
            this, &MainWindow::help);
    connect(new QShortcut(QKeySequence("N"), this), &QShortcut::activated,
            _playback_controls, &Controls::nextClicked);
    connect(new QShortcut(QKeySequence("B"), this), &QShortcut::activated,
            _playback_controls, &Controls::previousClicked);
    connect(new QShortcut(QKeySequence("P"), this), &QShortcut::activated,
            _playback_controls, &Controls::onPlayPause);
    connect(new QShortcut(QKeySequence("S"), this), &QShortcut::activated,
            _playback_controls, &Controls::onStop);
    connect(new QShortcut(QKeySequence("CTRL+M"), this), &QShortcut::activated,
            _playback_controls, &Controls::onMute);
    connect(new QShortcut(QKeySequence(Qt::Key_Plus), this), &QShortcut::activated,
            _playback_controls, &Controls::onPlusVolume);
    connect(new QShortcut(QKeySequence(Qt::Key_Minus), this), &QShortcut::activated,
            _playback_controls, &Controls::onMinusVolume);
}

void MainWindow::recursiveEntryPoints(QDir dir)
{
    QApplication::processEvents();

    QStringList files = dir.entryList(QDir::Files);
    for (auto& file : files)
        _droppedFiles << dir.absoluteFilePath(file);

    QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (auto& dir_path : dirs)
        recursiveEntryPoints(QDir(dir.absoluteFilePath(dir_path)));
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
    if (not _media_player->isVideoAvailable() and not isFullScreen())
            return;

    bool v = not _playlist_widget->isVisible();

    _playlist_widget->setVisible(v);
    _playback_info->setMediaTitleVisible(v);

    if (v) {
        showNormal();
        _tab_widget->tabBar()->setVisible(true);
        _playback_controls->setVisible(true);
        unsetCursor();
        _fullscreen_timer->stop();
    } else {
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
