/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LIBRARYELEMENT_H
#define LIBRARYELEMENT_H

#include <QtWidgets>

class LibraryElement : public QWidget
{
  Q_OBJECT
public:
  explicit LibraryElement(QString &path, QWidget *parent = nullptr);

  QString getPath() const;

  /// Set text to display in label
  void setText(const QString &value);

  /// String for saving in file
  QString getString() const;

  void setSelected(bool v);

  QString getName() const;

signals:
  void clicked();
  void doubleClicked();
  void ctrlClicked();
  void shiftClicked();

  void focus();

protected:
  virtual void mousePressEvent(QMouseEvent *e) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
  virtual void focusInEvent(QFocusEvent *) override;

private:
  QLabel *nameLabel;

  QString path;
  QString name;
};

#endif // LIBRARYELEMENT_H
