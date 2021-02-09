#include "image.h"

Image::Image(QWidget *parent) : QWidget(parent)
{
    pix = QPixmap();
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

    int x = w > h ? h : w;

    int px = w - x;
    int py = h - x;

    QPainter p(this);

    if (pix.isNull()) {
        return;
    }

    if (width() > height()) {
        px = width() / 2 - x / 2;
        py = 0;
    }
    else {
        px = 0;
        py = height() / 2 - x / 2;
    }
    p.drawPixmap(px, py, pix.scaled(x, x));
}
