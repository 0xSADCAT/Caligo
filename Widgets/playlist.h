/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include <Widgets/mediaelement.h>
#include <Inside/metascaner.h>

class Playlist : public QWidget
{
    Q_OBJECT
public:
    explicit Playlist(QMediaPlayer *mp, QWidget *parent = nullptr);

    QStringList getList();

    void add(const QString &path, const QString &text);
    void add(const QString &path, bool sc=false);
    void add(const QStringList &paths);

    void clear();

signals:
    void loadPlaylist(const QString &);

public slots:
    void next();
    void prev();

    void forceUpdate();

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *) override;

private:
    QMediaPlayer *player;

    int index;
    QList<MediaElement*> list;

    QVBoxLayout *l;

    MediaElement *lastClicked;
    QList<MediaElement*> selection;

    MetaScaner *scaner;

    QString getMetaData();

    void setCurrentIndexMedia();

private slots:
    void mediaStatus(QMediaPlayer::MediaStatus s);

    void clickElement();
    void shiftClickElement();
    void ctrlClickElement();
    void doubleClickElement();

    void focusFromElement();

    void cmSelectAll();
    void cmDeleteSelected();
};

#endif // PLAYLIST_H
