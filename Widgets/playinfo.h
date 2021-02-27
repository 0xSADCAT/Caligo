/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PLAYINFO_H
#define PLAYINFO_H

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVideoWidget>

#include <Widgets/image.h>
#include <Widgets/videowidget.h>

class PlayInfo : public QWidget
{
    Q_OBJECT
public:
    explicit PlayInfo(QMediaPlayer *mp, QWidget *parent = nullptr);

    void setNotFull(bool v);
    void focus();

    VideoWidget *video;

signals:
    void newTitle(const QString &s);
    void fsClicked();

private:
    QMediaPlayer *player;

    Image *image;
    QLabel *author;
    QLabel *name;
    bool isVideo;
    bool isFSVideo;

    void setTitle();

private slots:
    void mediaStatus(QMediaPlayer::MediaStatus s);
    void videoChanged(bool v);

    void videoClicked();
    void videoDoubleClicked();
};

#endif // PLAYINFO_H
