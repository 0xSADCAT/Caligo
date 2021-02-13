#ifndef METASCANER_H
#define METASCANER_H

#include <QObject>
#include <QtCore>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include <Widgets/mediaelement.h>

class MetaScaner : public QObject
{
    Q_OBJECT
public:
    explicit MetaScaner(QList<MediaElement*> *playlist, QObject *parent = nullptr);

    void scan();
    void forceScan();

private:
    // Contains pointers of playlist elements.
    QList<MediaElement*> *list;

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

#endif // METASCANER_H
