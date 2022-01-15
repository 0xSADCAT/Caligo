/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef TIMESLIDER_H
#define TIMESLIDER_H

#include <QMouseEvent>
#include <QWidget>
#include <QPainter>

class TimeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit TimeSlider(QWidget *parent = nullptr);

signals:
    void clicked(qint64);

public slots:
    void setDuration(qint64 duration);
    void setPosition(qint64 position);

protected:
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent*) override;

private:
    qint64 _position = 0;
    qint64 _duration = 0;
    bool _is_mouse_in = false;
};

#endif // TIMESLIDER_H
