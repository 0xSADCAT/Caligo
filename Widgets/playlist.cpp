/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "playlist.h"

Playlist::Playlist(QMediaPlayer *mp, QWidget *parent) : QWidget(parent)
// Playlist widget. Contains model and view of element.
{
#ifdef DEBUG_OUTPUT
  qDebug() << ">>> Playlist init";
#endif

  randomPlayback = false;

  player = mp;
  index = -1;
  l = new QVBoxLayout;
  QVBoxLayout *ml = new QVBoxLayout;
  ml->setObjectName("FullAlpha");
  l->setObjectName("FullAlpha");
  ml->addLayout(l, 0);
  QWidget *w = new QWidget;
  w->setObjectName("FullAlpha");
  ml->addWidget(w, 1);
  setLayout(ml);

  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->setSpacing(0);

  connect(player, &QMediaPlayer::mediaStatusChanged, this, &Playlist::mediaStatus);

  lastClicked = nullptr;

  scaner = new MetaScaner(&list);

  setObjectName("FullAlpha");

  randomGenerator.seed(QTime::currentTime().msec());
}

QStringList Playlist::getList()
{
  QStringList l;
  foreach (MediaElement *e, list) {
      l << e->getString();
    }

#ifdef DEBUG_OUTPUT
  qDebug() << "Playlist::getList()";
  qDebug() << l;
#endif

  return l;
}

void Playlist::add(const QString &path, const QString &text)
{
  MediaElement *e = new MediaElement(path);
  if (not (text.isEmpty() or text == " "))
    e->setText(text);
  l->addWidget(e, 0);
  list << e;

  connect(e, &MediaElement::focus, this, &Playlist::focusFromElement);
  connect(e, &MediaElement::clicked, this, &Playlist::clickElement);
  connect(e, &MediaElement::doubleClicked, this, &Playlist::doubleClickElement);
  connect(e, &MediaElement::shiftClicked, this, &Playlist::shiftClickElement);
  connect(e, &MediaElement::ctrlClicked, this, &Playlist::ctrlClickElement);
  connect(e, &MediaElement::selectAll, this, &Playlist::cmSelectAll);
  connect(e, &MediaElement::deleteSelected, this, &Playlist::cmDeleteSelected);
  connect(e, &MediaElement::startDrag, this, &Playlist::startDrag);
  connect(e, &MediaElement::elementsDropped, this, &Playlist::elementsDropped);

  if (index == -1) {
      index = 0;
      setCurrentIndexMedia();
      list[0]->setPlaying(true);
    }
}

void Playlist::add(const QString &path, bool sc)
// Add from path or url
{
#ifdef DEBUG_OUTPUT
  qDebug() << "Playlist::add(QString&)";
  qDebug() << path;
#endif

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
  connect(e, &MediaElement::startDrag, this, &Playlist::startDrag);
  connect(e, &MediaElement::elementsDropped, this, &Playlist::elementsDropped);

  if (index == -1) {
      index = 0;
      setCurrentIndexMedia();
      list[0]->setPlaying(true);
    }

  if (sc)
    scaner->scan();
}

void Playlist::add(const QStringList &paths)
// Add files from list
{
#ifdef DEBUG_OUTPUT
  qDebug() << "Playlist::add(QStringList&)";
  qDebug() << paths;
#endif

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
      setCurrentIndexMedia();
      list[0]->setPlaying(true);
    }

  scaner->scan();
}

void Playlist::clear()
// Clear playlist
{
#ifdef DEBUG_OUTPUT
  qDebug() << "Playlist::clear()";
#endif

  player->stop();
  player->setMedia(QUrl());
  foreach (MediaElement *e, list) {
      list.removeAll(e);
      l->removeWidget(e);
      e->~MediaElement();
    }
  index = -1;
}

/* public SLOT */ void Playlist::forceUpdate()
// Update metadata in playlist
{
#ifdef DEBUG_OUTPUT
  qDebug() << "SLOT Playlist::forceUpdate()";
#endif

  scaner->forceScan();
}

void Playlist::randomPlaybackChanged(bool value)
{
  randomPlayback = value;
}

/* public SLOT */ void Playlist::next()
// Set next track
{
#ifdef DEBUG_OUTPUT
  qDebug() << "SLOT Playlist::next()";
  qDebug() << "Current index:" << index;
#endif

  int c = list.count();
  if (c < 2)
    return;

  if (randomPlayback) {
      int nextIndex = randomGenerator.generate() % c;

      if (c > 7) {
          while (randomPrevious.contains(nextIndex)) {
              nextIndex = randomGenerator.generate() % c;
            }
          randomPrevious << nextIndex;
          if (randomPrevious.count() > 5)
            randomPrevious.removeFirst();
        }
      else {
          randomPrevious.clear();
        }

      list[index]->setPlaying(false);
      index = nextIndex;
      list[index]->setPlaying(true);
      setCurrentIndexMedia();

      return;
    }

  list[index]->setPlaying(false);
  index++;
  if (index >= c) {
      index = 0;
    }
  list[index]->setPlaying(true);
  setCurrentIndexMedia();

#ifdef DEBUG_OUTPUT
  qDebug() << "New index:" << index;
#endif
}

/* public SLOT */ void Playlist::prev()
// Set previous track
{
#ifdef DEBUG_OUTPUT
  qDebug() << "SLOT Playlist::prev()";
  qDebug() << "Current index:" << index;
#endif

  int c = list.count();
  if (c < 2)
    return;

  if (randomPlayback) {
      if (not randomPrevious.isEmpty()) {
          randomPrevious.removeLast();
          if (randomPrevious.isEmpty()) {
              int nextIndex = randomGenerator.generate() % c;
              list[index]->setPlaying(false);
              index = nextIndex;
              list[index]->setPlaying(true);
              setCurrentIndexMedia();
            }
          else {
              int nextIndex = randomPrevious.last();
              list[index]->setPlaying(false);
              index = nextIndex;
              list[index]->setPlaying(true);
              setCurrentIndexMedia();
            }
        }
      else {
          int nextIndex = randomGenerator.generate() % c;
          list[index]->setPlaying(false);
          index = nextIndex;
          list[index]->setPlaying(true);
          setCurrentIndexMedia();
        }
      return;
    }

  list[index]->setPlaying(false);
  index--;
  if (index < 0) {
      index = c - 1;
    }
  list[index]->setPlaying(true);
  setCurrentIndexMedia();

#ifdef DEBUG_OUTPUT
  qDebug() << "New index:" << index;
#endif
}

void Playlist::keyPressEvent(QKeyEvent *e)
{
  // Key Del
  // Remove selected element from playlist
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

  // Key Return
  // Play selected element, if selected > 1  -->  play last clicked
  else if (e->key() == Qt::Key::Key_Return) {
      if (lastClicked == nullptr)
        return;

      list[index]->setPlaying(false);
      lastClicked->setPlaying(true);
      index = list.indexOf(lastClicked);
      setCurrentIndexMedia();
      if (selection.count() > 1) {
          foreach (MediaElement* e, selection) {
              if (e != lastClicked) {
                  e->setSelected(false);
                }
            }
          selection.clear();
          selection << lastClicked;
          lastClicked->setSelected(false);
        }
    }

  // Key up
  // Select up element, if has ShiftModifer  -->  add upper element to selection or remove it from selection
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

  // Key down
  // Like key up
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

/* private SLOT */ void Playlist::mediaStatus(QMediaPlayer::MediaStatus s)
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

/* private SLOT */ void Playlist::clickElement()
{
  selection.clear();
  lastClicked = (MediaElement*) sender();
  selection << lastClicked;
  foreach (MediaElement* e, list) {
      e->setSelected(false);
    }
  lastClicked->setSelected(true);
}

/* private SLOT */ void Playlist::shiftClickElement()
{
  if (list.count() < 2)
    return;

  MediaElement *from = lastClicked;
  if (from == nullptr) {
      from = list[index];
    }

  lastClicked = (MediaElement*) sender();

  int iFrom = list.indexOf(from);
  int iTo = list.indexOf(lastClicked);

  if (iFrom == iTo)
    return;

  if (iFrom > iTo) {
      std::swap(iFrom, iTo);
    }

  for (int i = iFrom; i <= iTo; ++i) {
      if (not selection.contains(list[i])) {
          selection << list[i];
          list[i]->setSelected(true);
        }
    }
}

/* private SLOT */ void Playlist::ctrlClickElement()
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

/* private SLOT */ void Playlist::doubleClickElement()
{
  MediaElement *e = (MediaElement*) sender();
  list[index]->setPlaying(false);
  index = list.indexOf(e);
  setCurrentIndexMedia();
  list[index]->setPlaying(true);
  list[index]->setSelected(false);
  lastClicked = e;
  selection.clear();
}

/* private SLOT */ void Playlist::focusFromElement()
{
  this->setFocus();
}

/* private SLOT */ void Playlist::cmSelectAll()
// Context menu event.
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

/* private SLOT */ void Playlist::cmDeleteSelected()
// Context menu event.
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

void Playlist::startDrag()
{
  QMimeData *mimeData = new QMimeData;
  mimeData->setText("application/mediaElements");

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->exec();
}

void Playlist::elementsDropped()
{
  if (selection.isEmpty())
    return;

  MediaElement *current = list[index];
  int i = list.indexOf((MediaElement*) sender());
  if (list.count() < 100) {
      selection.clear();
      foreach (MediaElement *e, list) {
          if (e->isSelected()) {
              selection << e;
            }
        }
    }
  if (i < list.indexOf(selection[0]))
    std::reverse(selection.begin(), selection.end());

  foreach (MediaElement *e, selection) {
      list.removeAll(e);
      l->removeWidget(e);
      list.insert(i, e);
      l->insertWidget(i, e);
    }
  index = list.indexOf(current);
}

QString Playlist::getMetaData()
// Return metadata of current track in format 'Artist - Title'.
{
#ifdef DEBUG_OUTPUT
  qDebug() << "Playlist::getMetaData() [ret QString]";
#endif

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

#ifdef DEBUG_OUTPUT
  qDebug() << s;
#endif

  return s;
}

void Playlist::setCurrentIndexMedia()
{
  player->stop();
  QString u = list[index]->getPath();
  QUrl url;
  if (u.startsWith("http")) {
      url = QUrl(u);
    }
  else {
      url = QUrl::fromLocalFile(u);
    }
  player->setMedia(url);
  player->play();
}
