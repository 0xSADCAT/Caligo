/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QtWidgets>
#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget* parent = nullptr);

signals:
    void clicked();
    void doubleClicked();
    void mouseMoved();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent*) override;
};

#endif // VIDEOWIDGET_H
