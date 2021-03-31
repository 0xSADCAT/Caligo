/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QtWidgets>
#include <QVideoWidget>

/// Inherits QVideoWidget. Has signals clicked() and doubleClicked()
class VideoWidget : public QVideoWidget
{
  Q_OBJECT
public:
  explicit VideoWidget(QWidget *parent = nullptr);

signals:
  void clicked();
  void doubleClicked();
  void mouseMoved();

protected:
  virtual void mousePressEvent(QMouseEvent *e) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
  virtual void mouseMoveEvent(QMouseEvent *) override;
};

#endif // VIDEOWIDGET_H
