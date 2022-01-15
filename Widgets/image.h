/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

class Image : public QWidget
{
    Q_OBJECT
public:
    explicit Image(QWidget* parent = nullptr);

    void setPixmap(const QPixmap& value);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QPixmap _pixmap;
};

#endif // IMAGE_H
