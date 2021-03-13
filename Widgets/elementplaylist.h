/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef ELEMENTPLAYLIST_H
#define ELEMENTPLAYLIST_H

#include <QtWidgets>

#include <Style/style.cpp>

class ElementPlaylist : public QWidget
{
  Q_OBJECT
public:
  explicit ElementPlaylist(QString &path, QString &name, QWidget *parent = nullptr);

  /// Media name
  QString getName() const;

  /// Path to media file
  QString getPath() const;

  /// Path to file and name for saving
  QString getString() const;

  void setSelected(bool v);

signals:
  void clicked();
  void doubleClicked();
  void shiftClicked();
  void ctrlClicked();
  void focus();

protected:
  virtual void mousePressEvent(QMouseEvent *e) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
  virtual void focusInEvent(QFocusEvent *) override;

private:
  QLabel *nameLabel;
  QString path;
};

#endif // ELEMENTPLAYLIST_H
