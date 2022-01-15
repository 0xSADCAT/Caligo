/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "image.h"

Image::Image(QWidget* parent)
    : QWidget(parent)
{
    _pixmap = QPixmap(":/img/noImage");
    setMinimumSize(32, 32);
}

void Image::setPixmap(const QPixmap &value)
{
    _pixmap = value;
    repaint();
}

void Image::paintEvent(QPaintEvent*)
{
    int w = width();
    int h = height();

    int x = w > h ? h : w;

    int px = w - x;
    int py = h - x;

    QPainter painter (this);

    if (_pixmap.isNull())
        _pixmap = QPixmap(":/img/icon");

    QSize s = _pixmap.size();
    if (s.width() < x or s.height() < x)
        x = s.width() < s.height() ? s.height() : s.width();

    if (width() > height()) {
        px = width() / 2 - x / 2;
        py = 0;
    } else {
        px = 0;
        py = height() / 2 - x / 2;
    }

    px = width() / 2 - x / 2;
    py = height() / 2 - x / 2;

    painter.drawPixmap(px, py, _pixmap.scaled(x, x));
}
