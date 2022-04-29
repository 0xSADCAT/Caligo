/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "timeslider.h"

TimeSlider::TimeSlider(QWidget *parent)
    : QWidget(parent)
{ }

void TimeSlider::setDuration(qint64 duration)
{
    if (duration < 0)
        duration = 0;
    _duration = duration;
    repaint();
}

void TimeSlider::setPosition(qint64 position)
{
    if (position > _duration)
        position = _duration;
    _position = position;
    repaint();
}

void TimeSlider::enterEvent(QEvent*)
{
    _is_mouse_in = true;
    repaint();
}

void TimeSlider::leaveEvent(QEvent*)
{
    _is_mouse_in = false;
    repaint();
}

void TimeSlider::mousePressEvent(QMouseEvent* event)
{
    emit clicked(qint64(qreal(_duration) / qreal(width()) * (qreal) event->x()));
}

void TimeSlider::paintEvent(QPaintEvent*)
{
    QPainter painter (this);
    int w = width();
    int h = height();

    painter.save();
    painter.setPen(QColor(0, 0, 0, 127));
    painter.drawRect(0, 0, w, h);
    painter.restore();

    if (_is_mouse_in)
        painter.fillRect(0, 0, w, h, QColor(245, 245, 245, 127));
    else
        painter.fillRect(0, 0, w, h, QColor(230, 230, 230, 127));

    if (_duration == 0)
        return;

    int fx = int(qreal(_position) / qreal(_duration) * qreal(w));
    painter.fillRect(0, 0, fx, h, QColor(0, 127, 255, 127));
}
