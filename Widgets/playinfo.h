/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
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
    explicit PlayInfo(QMediaPlayer* player, QWidget* parent = nullptr);

    void setMediaTitleVisible(bool v);
    void focus();

signals:
    void newTitle(const QString&);
    void fullScreenClicked();
    void mouseMoved();

private:
    QMediaPlayer* _player;
    VideoWidget* _video = new VideoWidget;

    Image* _image = new Image;
    QLabel* _author = new QLabel;
    QLabel* _name = new QLabel;

    bool _is_video = false;
    bool _is_fullscreen = false;

    void setTitle();

private slots:
    void mediaStatus(QMediaPlayer::MediaStatus status);
    void videoAvailableChanged(bool video_available);

    void videoClicked();
    void videoDoubleClicked();
};

#endif // PLAYINFO_H
