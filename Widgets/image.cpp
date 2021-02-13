#include "image.h"

Image::Image(QWidget *parent) : QWidget(parent)
// Custom widget to display image.
{
    pix = QPixmap();
    setMinimumSize(32, 32);

    // By default.
    // if notSquare == false  -->  pix.width() == pix.heigth()
    notSquare = false;
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
    if (notSquare)
        p.drawPixmap(px, py, pix);
    else
        p.drawPixmap(px, py, pix.scaled(x, x));
}
