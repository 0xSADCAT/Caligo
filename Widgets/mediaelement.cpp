/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mediaelement.h"

MediaElement::MediaElement(const QString &path, QWidget *parent) : QWidget(parent)
// Custom widget. Element of playlist. Contains model and view of component.
{
#ifdef DEBUG_OUTPUT
  qDebug() << ">>> MediaElement init:" << path;
#endif

  setObjectName("AlphaBG");

  this->path = path;

  text = new QLabel("  " + path);
  text->setObjectName("AlphaBG");

  QHBoxLayout *l = new QHBoxLayout;
  l->addWidget(text);
  l->setObjectName("AlphaBG");
  setLayout(l);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);

  playing = false;
  selected = false;

  contextMenu = new QMenu;
  contextMenu->addAction(QPixmap(":/img/selectAll"), tr("Select all"), this, &MediaElement::selectAll);
  contextMenu->addAction(QPixmap(":/img/delete"), tr("Remove selected"), this, &MediaElement::deleteSelected);

  setAcceptDrops(true);

  updStyle();
}

QString MediaElement::getPath() const
{
  return path;
}

bool MediaElement::hasMeta() const
{
  return meta;
}

void MediaElement::setText(const QString &text)
// Set metadata
{
#ifdef DEBUG_OUTPUT
  qDebug() << "MediaElement::setText" << path;
  qDebug() << "---> " << text;
#endif

  this->text->setText(text);
  meta = true;
}

void MediaElement::setPlaying(bool value)
{
#ifdef DEBUG_OUTPUT
  qDebug() << "MediaElement::setPlaying" << path;
  qDebug() << "---> " << value;
#endif

  playing = value;
  updStyle();
}

void MediaElement::setSelected(bool value)
{
#ifdef DEBUG_OUTPUT
  qDebug() << "MediaElement::setSelected" << path;
  qDebug() << "---> " << value;
#endif

  selected = value;
  updStyle();
}

QString MediaElement::getString() const
{
  QString s;
  s += path;
  s += " ## ";
  if (text->text() != path) {
      s += text->text();
    }
  return s;
}

void MediaElement::mousePressEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) {
      dragPos = e->pos();
    }
  emit focus();
}

void MediaElement::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) {
      if (e->modifiers() & Qt::ShiftModifier) {
          emit shiftClicked();
        }
      else if (e->modifiers() & Qt::ControlModifier) {
          emit ctrlClicked();
        }
      else {
          emit clicked();
        }
    }
}

void MediaElement::mouseMoveEvent(QMouseEvent *e)
{
  if (e->buttons() & Qt::LeftButton) {
      int dist = (e->pos() - dragPos).manhattanLength();
      if (dist > qApp->startDragDistance()) {
          emit startDrag();
        }
    }
}

void MediaElement::mouseDoubleClickEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton)
    emit doubleClicked();
  emit focus();
}

void MediaElement::focusInEvent(QFocusEvent *)
{
  emit focus();
}

void MediaElement::contextMenuEvent(QContextMenuEvent *e)
{
  contextMenu->exec(e->globalPos());
}

void MediaElement::dragEnterEvent(QDragEnterEvent *e)
{
  if (e->mimeData()->text() == "application/mediaElements") {
      this->setStyleSheet(this->styleSheet() + "* {border-bottom: 1px solid black; margin-bottom: 3px;}");
      e->acceptProposedAction();
    }
}

void MediaElement::dragLeaveEvent(QDragLeaveEvent *)
{
  updStyle();
}

void MediaElement::dropEvent(QDropEvent *)
{
  emit elementsDropped();
  updStyle();
}

bool MediaElement::isSelected() const
{
  return selected;
}

void MediaElement::updStyle()
{
  if (playing and selected) {
      setStyleSheet(qvariant_cast<QString>(qApp->property("MePlayingAndSelectedQSS")));
    }
  else if (playing) {
      setStyleSheet(qvariant_cast<QString>(qApp->property("MePlayingQSS")));
    }
  else if (selected) {
      setStyleSheet(qvariant_cast<QString>(qApp->property("MeSelectedQSS")));
    }
  else {
      setStyleSheet(qvariant_cast<QString>(qApp->property("MeNoneQSS")));
    }
}
