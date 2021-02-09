#include "playlist.h"

Playlist::Playlist(QMediaPlayer *mp, QWidget *parent) : QWidget(parent)
{
    player = mp;
    index = -1;
    l = new QVBoxLayout;
    QVBoxLayout *ml = new QVBoxLayout;
    ml->addLayout(l, 0);
    ml->addStretch(1);
    setLayout(ml);

    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Playlist::mediaStatus);

    lastClicked = nullptr;

    scaner = new MetaScaner(&list);
}

QStringList Playlist::getList()
{
    QStringList l;
    foreach (MediaElement *e, list) {
        l << e->getPath();
    }
    return l;
}

void Playlist::add(const QString &path)
{
    if (path.endsWith(".cpl")) {
        emit loadPlaylist(path);
        return;
    }

    MediaElement *e = new MediaElement(path);
    l->addWidget(e, 0);
    list << e;

    connect(e, &MediaElement::focus, this, &Playlist::focusFromElement);
    connect(e, &MediaElement::clicked, this, &Playlist::clickElement);
    connect(e, &MediaElement::doubleClicked, this, &Playlist::doubleClickElement);
    connect(e, &MediaElement::shiftClicked, this, &Playlist::shiftClickElement);
    connect(e, &MediaElement::ctrlClicked, this, &Playlist::ctrlClickElement);
    connect(e, &MediaElement::selectAll, this, &Playlist::cmSelectAll);
    connect(e, &MediaElement::deleteSelected, this, &Playlist::cmDeleteSelected);
}

void Playlist::add(const QStringList &paths)
{
    if (paths.isEmpty())
        return;

    int c = 0;
    foreach (QString p, paths) {
        if (c > 9) {
            c = 0;
            qApp->processEvents();
        }
        else {
            c++;
        }
        add(p);
    }

    if (index == -1) {
        index = 0;
        player->setMedia(QUrl::fromLocalFile(list[0]->getPath()));
        list[0]->setPlaying(true);
        player->play();
    }

    scaner->scan();
}

void Playlist::clear()
{
    player->stop();
    player->setMedia(QUrl());
    foreach (MediaElement *e, list) {
        list.removeAll(e);
        l->removeWidget(e);
        e->~MediaElement();
    }
    index = -1;
}

void Playlist::forceUpdate()
{
    scaner->forceScan();
}

void Playlist::next()
{
    int c = list.count();
    if (c < 2)
        return;

    list[index]->setPlaying(false);
    index++;
    if (index >= c) {
        index = 0;
    }
    list[index]->setPlaying(true);
    player->setMedia(QUrl::fromLocalFile(list[index]->getPath()));
    player->play();
}

void Playlist::prev()
{
    int c = list.count();
    if (c < 2)
        return;

    list[index]->setPlaying(false);
    index--;
    if (index < 0) {
        index = c - 1;
    }
    list[index]->setPlaying(true);
    player->setMedia(QUrl::fromLocalFile(list[index]->getPath()));
    player->play();
}

void Playlist::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key::Key_Delete) {
        if (lastClicked == nullptr)
            return;

        lastClicked = nullptr;

        if (selection.count() == list.count()) {
            clear();
            return;
        }

        foreach (MediaElement* e, selection) {
            int di = list.indexOf(e);
            if (di == index) {
                next();
                index--;
                if (index == -1) {
                    index = 0;
                }
            }
            else if (di < index) {
                index--;
            }
            list.removeAll(e);
            l->removeWidget(e);
            e->deleteLater();
        }
        selection.clear();
    }
    else if (e->key() == Qt::Key::Key_Return) {
        if (lastClicked == nullptr)
            return;

        list[index]->setPlaying(false);
        lastClicked->setPlaying(true);
        index = list.indexOf(lastClicked);
        player->stop();
        player->setMedia(QUrl::fromLocalFile(list[index]->getPath()));
        player->play();
        if (selection.count() > 1) {
            foreach (MediaElement* e, selection) {
                if (e != lastClicked) {
                    e->setSelected(false);
                }
            }
            selection.clear();
            selection << lastClicked;
        }
    }
    else if (e->key() == Qt::Key::Key_Up) {
        if (list.isEmpty())
            return;
        if (list.count() == 1) {
            lastClicked = list[0];
            if (not selection.isEmpty() || lastClicked == nullptr) {
                selection.clear();
                selection << lastClicked;
            }
            return;
        }

        int id;
        if (lastClicked == nullptr) {
            lastClicked = list[index];
            id = index;
        }
        else {
            id = list.indexOf(lastClicked);
        }
        id--;
        if (id < 0) {
            id = list.count() - 1;
        }

        if (e->modifiers() & Qt::ShiftModifier) {
            if (selection.contains(list[id])) {
                lastClicked->setSelected(false);
                selection.removeAll(lastClicked);
            }
            else {
                if (selection.isEmpty()) {
                    lastClicked->setSelected(true);
                    selection << lastClicked;
                }
                list[id]->setSelected(true);
                selection << list[id];
            }
            lastClicked = list[id];
            return;
        }

        lastClicked = list[id];
        foreach (MediaElement* e, selection) {
            e->setSelected(false);
        }
        lastClicked->setSelected(true);
        selection.clear();
        selection << lastClicked;
    }
    else if (e->key() == Qt::Key::Key_Down) {
        if (list.isEmpty())
            return;
        if (list.count() == 1) {
            lastClicked = list[0];
            if (not selection.isEmpty() || lastClicked == nullptr) {
                selection.clear();
                selection << lastClicked;
            }
            return;
        }

        int id;
        if (lastClicked == nullptr) {
            lastClicked = list[index];
            id = index;
        }
        else {
            id = list.indexOf(lastClicked);
        }
        id++;
        if (id > list.count() - 1) {
            id = 0;
        }

        if (e->modifiers() & Qt::ShiftModifier) {
            if (selection.contains(list[id])) {
                lastClicked->setSelected(false);
                selection.removeAll(lastClicked);
            }
            else {
                if (selection.isEmpty()) {
                    lastClicked->setSelected(true);
                    selection << lastClicked;
                }
                list[id]->setSelected(true);
                selection << list[id];
            }
            lastClicked = list[id];
            return;
        }

        lastClicked = list[id];
        foreach (MediaElement* e, selection) {
            e->setSelected(false);
        }
        lastClicked->setSelected(true);
        selection.clear();
        selection << lastClicked;
    }
}

void Playlist::mousePressEvent(QMouseEvent *)
{
    if (not selection.isEmpty()) {
        foreach (MediaElement* e, selection) {
            e->setSelected(false);
        }
        selection.clear();
    }
}

void Playlist::mediaStatus(QMediaPlayer::MediaStatus s)
{
    switch (s) {
    case QMediaPlayer::EndOfMedia:
        next();
        break;

    case QMediaPlayer::BufferedMedia:
    case QMediaPlayer::LoadedMedia:
        if (not list[index]->hasMeta()) {
            list[index]->setText(getMetaData());
        }
        break;

    default:
        break;
    }
}

void Playlist::clickElement()
{
    selection.clear();
    lastClicked = (MediaElement*) sender();
    selection << lastClicked;
    foreach (MediaElement* e, list) {
        e->setSelected(false);
    }
    lastClicked->setSelected(true);
}

void Playlist::shiftClickElement()
{
    MediaElement *from = lastClicked;
    lastClicked = (MediaElement*) sender();

    int iFrom = list.indexOf(from);
    int iTo = list.indexOf(lastClicked);

    if (iFrom == iTo)
        return;

    if (iFrom > iTo) {
        iFrom ^= iTo;
        iTo ^= iFrom;
        iFrom ^= iTo;
    }

    for (int i = iFrom; i <= iTo; ++i) {
        if (not selection.contains(list[i])) {
            selection << list[i];
            list[i]->setSelected(true);
        }
    }
}

void Playlist::ctrlClickElement()
{
    lastClicked = (MediaElement*) sender();
    if (selection.contains(lastClicked)) {
        lastClicked->setSelected(false);
        selection.removeAll(lastClicked);
        return;
    }
    else {
        selection << lastClicked;
        lastClicked->setSelected(true);
    }
}

void Playlist::doubleClickElement()
{
    MediaElement *e = (MediaElement*) sender();
    list[index]->setPlaying(false);
    index = list.indexOf(e);
    player->stop();
    player->setMedia(QUrl::fromLocalFile(list[index]->getPath()));
    player->play();
    list[index]->setPlaying(true);
}

void Playlist::focusFromElement()
{
    this->setFocus();
}

void Playlist::cmSelectAll()
{
    if (list.isEmpty())
        return;

    lastClicked = list[0];
    selection.clear();
    foreach (MediaElement *e, list) {
        selection << e;
        e->setSelected(true);
    }
}

void Playlist::cmDeleteSelected()
{
    if (lastClicked == nullptr)
        return;

    lastClicked = nullptr;

    if (selection.count() == list.count()) {
        clear();
        return;
    }

    foreach (MediaElement* e, selection) {
        int di = list.indexOf(e);
        if (di == index) {
            next();
            index--;
            if (index == -1) {
                index = 0;
            }
        }
        else if (di < index) {
            index--;
        }
        list.removeAll(e);
        l->removeWidget(e);
        e->deleteLater();
    }
    selection.clear();
}

QString Playlist::getMetaData()
{
    QString s = "";
    QStringList l = player->availableMetaData();
    if (l.contains(QMediaMetaData::AlbumArtist)) {
        s += qvariant_cast<QString>(player->metaData(QMediaMetaData::AlbumArtist));
    }
    if (l.contains(QMediaMetaData::Title)) {
        if (not s.isEmpty()) {
            s += " - ";
        }
        s += qvariant_cast<QString>(player->metaData(QMediaMetaData::Title));
    }
    if (s.isEmpty()) {
        s = list[index]->getPath();
    }
    return s;
}
