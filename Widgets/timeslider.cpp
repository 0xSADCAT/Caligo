#include "timeslider.h"

TimeSlider::TimeSlider(QWidget *parent) : QWidget(parent)
{
    _pos = _dur = 0;
    isIn = false;
}

void TimeSlider::setDuration(qint64 v)
{
    if (v < 0)
        v = 0;
    _dur = v;
    repaint();
}

void TimeSlider::setPosition(qint64 v)
{
    if (v > _dur)
        v = _dur;
    _pos = v;
    repaint();
}

void TimeSlider::enterEvent(QEvent *)
{
    isIn = true;
    repaint();
}

void TimeSlider::leaveEvent(QEvent *)
{
    isIn = false;
    repaint();
}

void TimeSlider::mousePressEvent(QMouseEvent *e)
{
    qreal x = (qreal) e->x();
    emit clicked(qint64(qreal(_dur) / qreal(width()) * x));
}

void TimeSlider::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int w = width();
    int h = height();

    if (isIn)
        p.fillRect(0, 0, w, h, QColor(245, 245, 245));
    else
        p.fillRect(0, 0, w, h, QColor(230, 230, 230));

    if (_dur == 0)
        return;

    int fx = int(qreal(_pos) / qreal(_dur) * qreal(w));
    p.fillRect(0, 0, fx, h, QColor(0, 127, 255, 127));
}
