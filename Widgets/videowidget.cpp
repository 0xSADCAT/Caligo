/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "videowidget.h"

VideoWidget::VideoWidget(QWidget* parent)
    : QVideoWidget(parent)
{
    setMouseTracking(true);
}

void VideoWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit doubleClicked();
}

void VideoWidget::mouseMoveEvent(QMouseEvent*)
{
    emit mouseMoved();
}
