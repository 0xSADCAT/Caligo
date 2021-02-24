/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LIBRARYMETASCANER_H
#define LIBRARYMETASCANER_H

#include <QObject>
#include <QtCore>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include <Widgets/libraryelement.h>

class LibraryMetaScaner : public QObject
{
    Q_OBJECT
public:
    explicit LibraryMetaScaner(QList<LibraryElement*> *list, QProgressBar *prBar, QObject *parent = nullptr);

    void scan();
    void forceScan();

signals:
    void done();

private:
    // Contains pointers of elements.
    QList<LibraryElement*> *list;

    QProgressBar *progress;

    // Second QMediaPlayer for recursive algorithm.
    QMediaPlayer player;

    // Current scanning index.
    int index;
    // Count elements of playlist.
    int count;

    // Old variable. Not deleted because algorithm for scanning metadata is in dev.
    bool force;

private slots:
    void mediaStatus(QMediaPlayer::MediaStatus s);
};

#endif // LIBRARYMETASCANER_H
