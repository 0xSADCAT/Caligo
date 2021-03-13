/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MEDIAELEMENT_H
#define MEDIAELEMENT_H

#include <QtWidgets>

#include <Style/style.cpp>

class MediaElement : public QWidget
{
  Q_OBJECT
public:
  explicit MediaElement(const QString &path, QWidget *parent = nullptr);

  QString getPath() const;

  bool hasMeta() const;

  void setText(const QString &text);

  /// Display state
  void setPlaying(bool value);

  /// Display state
  void setSelected(bool value);

  /// String for saving
  QString getString() const;

signals:
  void clicked();
  void shiftClicked();
  void ctrlClicked();
  void doubleClicked();

  void startDrag();

  void elementsDropped();

  /// Needs to set focus to Playlist but not on element (playlist keyboard controls)
  void focus();

  /// Signal from context menu.
  void selectAll();

  /// Signal from context menu.
  void deleteSelected();

protected:
  virtual void mousePressEvent(QMouseEvent *e) override;
  virtual void mouseReleaseEvent(QMouseEvent *e) override;
  virtual void mouseMoveEvent(QMouseEvent *e) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
  virtual void focusInEvent(QFocusEvent *) override;
  virtual void contextMenuEvent(QContextMenuEvent *e) override;
  virtual void dragEnterEvent(QDragEnterEvent *e) override;
  virtual void dragLeaveEvent(QDragLeaveEvent *) override;
  virtual void dropEvent(QDropEvent *) override;

private:
  QLabel *text;
  // Path to file.
  QString path;
  bool meta;
  // Playing/selected states.
  bool playing;
  bool selected;

  void updStyle();

  QMenu *contextMenu;

  QPoint dragPos;
};

#endif // MEDIAELEMENT_H
