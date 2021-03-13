/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "image.h"

Image::Image(QWidget *parent) : QWidget(parent)
// Custom widget to display image.
{
  pix = QPixmap(":/img/noImage");
  setMinimumSize(32, 32);
}

void Image::setPix(const QPixmap &value)
{
  pix = value;
  repaint();
}

void Image::paintEvent(QPaintEvent *)
{
  int w = width();
  int h = height();

  // Minimum if width and height.
  int x = w > h ? h : w;

  int px = w - x;
  int py = h - x;

  QPainter p(this);

  // pix.isNull() == true  if  music not contains image in metadata, invalid media or playlist is empty.
  if (pix.isNull()) {
      pix = QPixmap(":/img/noImage");
    }

  QSize s = pix.size();
  if (s.width() < x or s.height() < x) {
      x = s.width() < s.height() ? s.height() : s.width();
    }

  if (width() > height()) {
      px = width() / 2 - x / 2;
      py = 0;
    }
  else {
      px = 0;
      py = height() / 2 - x / 2;
    }

  px = width() / 2 - x / 2;
  py = height() / 2 - x / 2;

  p.drawPixmap(px, py, pix.scaled(x, x));
}

void Image::enterEvent(QEvent *)
{
  /* do nothing */
  return;
}

void Image::leaveEvent(QEvent *)
{
  /* do nothing */
  return;
}
