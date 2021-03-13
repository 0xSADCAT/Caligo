/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include <Widgets/libraryelement.h>
#include <Widgets/playlist.h>
#include <Inside/librarymetascaner.h>

#include <algorithm>

class MediaLibrary : public QWidget
{
  Q_OBJECT
public:
  explicit MediaLibrary(Playlist *pls, QWidget *parent = nullptr);

  /// Scanning status
  enum Status {
    Done,
    Paths,
    Meta
  };

  QString getLibraryPath() const;
  void setLibraryPath(QString path);

  void save();

public slots:
  void done();
  void setProgress(int v);
  void setStatus(Status s);

protected:
  virtual void keyPressEvent(QKeyEvent *e) override;

private:
  QList<LibraryElement*> list;
  QList<LibraryElement*> selection;
  LibraryElement *lastClicked;

  QStringList files;

  Playlist *playlist;
  QString scanPath;

  QVBoxLayout *mainLayout;

  QPushButton *scanButton;

  /// Add new element
  void add(QString &path);

  /// Remove element from library
  void remove(LibraryElement *e);

  /// Clear media library
  void clear();

  /// Entry points of subdirs
  void scanDir(QDir d);

  QProgressBar *progress;
  QLabel *status;
  QWidget *statusWidget;

  LibraryMetaScaner *scaner;

  /// Load media library from file
  void load();
  QString libraryFilePath;
  bool rewriteLibrary;

private slots:
  void elementClicked();
  void elementDouble();
  void elementShift();
  void elementCtrl();
  void elementFocus();

  void scanLibrary();
  void setScanPath();

  void scanerDone();
};

/// Compare elements. Needs for sorting.
inline bool compareLibraryElements(const LibraryElement *e1, const LibraryElement *e2) noexcept;

#endif // MEDIALIBRARY_H
