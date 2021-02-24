/* This file is path of the Caligo multimedia player
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
    // Clicked on element (_pos)
    void clicked(qint64);

public slots:
    void setDuration(qint64 v);
    void setPosition(qint64 v);

protected:
    virtual void enterEvent(QEvent *) override;
    virtual void leaveEvent(QEvent *) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void paintEvent(QPaintEvent *) override;

private:
    qint64 _pos, _dur;
    // Mouse in widget
    bool isIn;
};

#endif // TIMESLIDER_H
