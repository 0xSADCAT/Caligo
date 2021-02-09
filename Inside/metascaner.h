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
    QList<MediaElement*> *list;

    QMediaPlayer player;

    int index;
    int count;

    bool force;

private slots:
    void mediaStatus(QMediaPlayer::MediaStatus s);
};

#endif // METASCANER_H
