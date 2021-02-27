/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include <Widgets/libraryelement.h>
#include <Widgets/playlist.h>
#include <Inside/librarymetascaner.h>

class MediaLibrary : public QWidget
{
    Q_OBJECT
public:
    explicit MediaLibrary(Playlist *pls, QWidget *parent = nullptr);

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

    void add(QString &path);
    void remove(LibraryElement *e);
    void clear();

    void scanDir(QDir d);

    QProgressBar *progress;
    QLabel *status;
    QWidget *statusWidget;

    LibraryMetaScaner *scaner;

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

#endif // MEDIALIBRARY_H
