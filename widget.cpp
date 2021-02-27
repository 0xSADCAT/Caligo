/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
#ifdef DEBUG_OUTPUT
    qDebug() << ">>> Widget class init";
#endif

    setWindowIcon(QIcon(":/img/icon"));

    mp = new QMediaPlayer;
    controls = new Controls(mp);
    playInfo = new PlayInfo(mp);
    playlist = new Playlist(mp);
    plControls = new PlaylistControls(playlist);

    tabWidget = new QTabWidget;

    controls->setSizes(20);
    plControls->setSizes(16);

    QVBoxLayout *plL = new QVBoxLayout;
    plL->addWidget(plControls, 0);
    QScrollArea *sa = new QScrollArea;
    sa->setWidget(playlist);
    sa->setWidgetResizable(true);
    sa->setFrameStyle(QFrame::NoFrame);
    plL->addWidget(sa, 1);

    sw = new QWidget;
    sw->setLayout(plL);
    sw->layout()->setSpacing(0);
    sw->layout()->setContentsMargins(0, 0, 0, 0);

    spl = new QSplitter;
    spl->addWidget(tabWidget);
    spl->addWidget(sw);

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(spl, 1);
    l->addWidget(controls, 0);
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);

    setLayout(l);

    library = new MediaLibrary(playlist);
    radioLibrary = new RadioLibrary(playlist);
    playlistLibrary = new LibraryPlaylists(playlist);

    settings = new QSettings(qApp->applicationDirPath() + QDir::separator() + qApp->applicationName() + "_settings.ini", QSettings::IniFormat);
    loadSettings();

    settingsWindow = new SettingsWindow(settings, plControls, library, radioLibrary, playlistLibrary, this);
    aboutWindow = new AboutWindow;
    helpWindow = new HelpWindow;

    tabWidget->addTab(playInfo, tr("Now Playing"));
    tabWidget->addTab(library, tr("Media library"));
    tabWidget->addTab(playlistLibrary, tr("Playlists"));
    tabWidget->addTab(radioLibrary, tr("Radio library"));
    tabWidget->addTab(settingsWindow, tr("Settings"));
    tabWidget->addTab(aboutWindow, tr("About"));
    tabWidget->addTab(helpWindow, tr("Help"));

    connect(controls, &Controls::next, playlist, &Playlist::next);
    connect(controls, &Controls::prev, playlist, &Playlist::prev);

    connect(playInfo, &PlayInfo::newTitle, this, &Widget::setNewTitle);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);

    playlist->setFocus();

    this->setAcceptDrops(true);

    connect(playInfo, &PlayInfo::fsClicked, this, &Widget::videoFullscreen);
    connect(controls, &Controls::fullScreen, this, &Widget::videoFullscreen);

    QShortcut *sFull = new QShortcut(QKeySequence("F"), this);
    connect(sFull, &QShortcut::activated, this, &Widget::videoFullscreen);

    QShortcut *sExitFull = new QShortcut(QKeySequence("Esc"), this);
    connect(sExitFull, &QShortcut::activated, this, &Widget::exitFull);

    QShortcut *sNext = new QShortcut(QKeySequence("N"), this);
    connect(sNext, &QShortcut::activated, controls, &Controls::next);

    QShortcut *sPrev = new QShortcut(QKeySequence("B"), this);
    connect(sPrev, &QShortcut::activated, controls, &Controls::prev);

    QShortcut *sPlay = new QShortcut(QKeySequence("P"), this);
    connect(sPlay, &QShortcut::activated, controls, &Controls::playPause);

    QShortcut *sStop = new QShortcut(QKeySequence("S"), this);
    connect(sStop, &QShortcut::activated, controls, &Controls::stop);

    QShortcut *sMute = new QShortcut(QKeySequence("CTRL+M"), this);
    connect(sMute, &QShortcut::activated, controls, &Controls::mute);

    QShortcut *sPlus = new QShortcut(QKeySequence(Qt::Key_Plus), this);
    connect(sPlus, &QShortcut::activated, controls, &Controls::plusVol);

    QShortcut *sMinus = new QShortcut(QKeySequence(Qt::Key_Minus), this);
    connect(sMinus, &QShortcut::activated, controls, &Controls::minusVol);

    QShortcut *sHelp = new QShortcut(QKeySequence("CTRL+H"), this);
    connect(sHelp, &QShortcut::activated, this, &Widget::help);

    setStyleSheet(style::theme::light);
}

Widget::~Widget()
{
}

void Widget::closeEvent(QCloseEvent *)
{
#ifdef DEBUG_OUTPUT
    qDebug() << "Widget::closeEvent";
#endif

    library->save();

    settings->setValue("windowConfig/size", this->size());
    settings->setValue("windowConfig/position", this->pos());
    settings->setValue("windowConfig/splitterLeft", this->spl->sizes()[0]);
    settings->setValue("windowConfig/splitterRight", this->spl->sizes()[1]);
    settings->setValue("other/volume", this->controls->getVolume());
    settings->setValue("other/playlist", this->playlist->getList());

    /* Hide error code 139 */
    settings->~QSettings();
    std::exit(0);
}

void Widget::dragEnterEvent(QDragEnterEvent *e)
{
#ifdef DEBUG_OUTPUT
    qDebug() << "Widget::dragEnterEvent";
    qDebug() << "QDragEnterEvent::mimeData()" << e->mimeData();
#endif

    if (e->mimeData()->hasFormat("text/uri-list")) {
        e->acceptProposedAction();
    }
}

void Widget::dropEvent(QDropEvent *e)
{
#ifdef DEBUG_OUTPUT
    qDebug() << "Widget::dropEvent()";
    qDebug() << "QDropEvent::mimeData->urls()" << e->mimeData()->urls();
#endif

    QList<QUrl> urls = e->mimeData()->urls();
    droppedFiles.clear();

    foreach (QUrl u, urls) {
        QApplication::processEvents();
        if (u.isLocalFile()) {
            QString tp = QDir::toNativeSeparators(u.path());

#ifdef Q_OS_WINDOWS
            if (tp.startsWith("/") or tp.startsWith("\\")) {
                tp.remove(0, 1);
            }
            tp.replace("/", "\\");
#endif

            QFileInfo fi(tp);
            if (fi.isDir()) {
                QDir d(tp);
                recursiveEntryPoints(d);
            }
            else {
                droppedFiles << tp;
            }
        }
    }

    if (not droppedFiles.isEmpty()) {
        QString c = "";
        foreach (QString s, droppedFiles) {
            c = QMimeDatabase().mimeTypeForFile(s).name();
            if (not c.contains("audio/") and not c.contains("video/") and not s.endsWith(".cpl")) {
                droppedFiles.removeAll(s);
            }
        }

        playlist->add(droppedFiles);
        droppedFiles.clear();
    }
}

void Widget::loadSettings()
{
#ifdef DEBUG_OUTPUT
    qDebug() << "Widget::loadSettings()";
#endif
    this->resize(qvariant_cast<QSize>(settings->value("windowConfig/size")));
    this->move(qvariant_cast<QPoint>(settings->value("windowConfig/position", QPoint(qApp->desktop()->width()/3, qApp->desktop()->height()/3))));
    QList<int> s;
    s << qvariant_cast<int>(settings->value("windowConfig/splitterLeft", 0));
    s << qvariant_cast<int>(settings->value("windowConfig/splitterRight", 0));
    if (s[0] != 0 or s[1] != 0) {
        spl->setSizes(s);
    }
    controls->setVolume(qvariant_cast<int>(settings->value("other/volume", 50)));
    bool loadOld = qvariant_cast<bool>(settings->value("other/loadOld", false));
    if (loadOld and qApp->arguments().count() == 1) {
        QStringList list = qvariant_cast<QStringList>(settings->value("other/playlist"));

#ifdef DEBUG_OUTPUT
        qDebug() << "Old playlist:";
        qDebug() << list;
#endif

        bool needScan = false;
        foreach (QString s, list) {
            QStringList li = s.split(" ## ");
            if (li.count() == 1) {
                playlist->add(li[0]);
                needScan = true;
            }
            else {
                if (li[1] == " ") {
                    playlist->add(li[0]);
                    needScan = true;
                }
                else {
                    playlist->add(li[0], li[1]);
                }
            }
        }

        if (needScan) {
            playlist->forceUpdate();
        }
    }

    if (qApp->arguments().count() != 1) {
        QStringList slist;
        for (int i = 1; i < qApp->arguments().count(); ++i) {
            if (QFile(qApp->arguments()[i]).exists() and
                    (QMimeDatabase().mimeTypeForFile(qApp->arguments()[i]).name().contains("audio/")
                     or QMimeDatabase().mimeTypeForFile(qApp->arguments()[i]).name().contains("video/")
                     or QMimeDatabase().mimeTypeForFile(qApp->arguments()[i]).name().endsWith(".cpl"))) {
                qApp->processEvents();
                slist << qApp->arguments()[i];
            }

#ifdef DEBUG_OUTPUT
            if (QFile(qApp->arguments()[i]).exists()) {
                qDebug() << "File exists:" << qApp->arguments()[i];
                qDebug() << "Mime type:" << QMimeDatabase().mimeTypeForFile(qApp->arguments()[i]).name();
            }
#endif

        }

#ifdef DEBUG_OUTPUT
        qDebug() << "qApp->arguments() != 1";
        qDebug() << "Arguments:";
        qDebug() << qApp->arguments();
        qDebug() << "List:";
        qDebug() << slist;
#endif

        playlist->add(slist);
    }

    radioLibrary->scanLibrary();
    playlistLibrary->scan();
}

void Widget::recursiveEntryPoints(QDir d)
{
    QApplication::processEvents();

    QStringList files = d.entryList(QDir::Files);
    foreach (QString file, files) {
        droppedFiles << d.absoluteFilePath(file);
    }

    QStringList dirs = d.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QString dir, dirs) {
        recursiveEntryPoints(QDir(d.absoluteFilePath(dir)));
    }
}

void Widget::setNewTitle(const QString &s)
{
    this->setWindowTitle(s);
}

void Widget::help()
{
    tabWidget->setCurrentIndex(tabWidget->count()-1);
}

/* In DEV */
void Widget::videoFullscreen()
{
    if (not mp->isVideoAvailable()) {
        if (not this->isFullScreen())
            return;
    }

    bool v = not sw->isVisible();

    controls->setVisible(v);
    sw->setVisible(v);
    playInfo->setNotFull(v);

    if (v) {
        showNormal();
    }
    else {
        showFullScreen();
    }
}

void Widget::exitFull()
{
    if (this->isFullScreen()) {
        videoFullscreen();
    }
}

