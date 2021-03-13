/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

/// Displays size-adaptive image
class Image : public QWidget
{
  Q_OBJECT
public:
  explicit Image(QWidget *parent = nullptr);

  void setPix(const QPixmap &value);

protected:
  virtual void paintEvent(QPaintEvent *) override;
  virtual void enterEvent(QEvent *) override;
  virtual void leaveEvent(QEvent *) override;

private:
  QPixmap pix;
};

#endif // IMAGE_H
