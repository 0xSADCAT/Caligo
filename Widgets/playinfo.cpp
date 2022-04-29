/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "playinfo.h"

PlayInfo::PlayInfo(QMediaPlayer* player, QWidget* parent)
    : QWidget(parent),
      _player(player)
{
    _author->setFont(QFont(font().family(), 12, QFont::Bold));
    _name->setFont(QFont(font().family(), 10));

    _video->setVisible(false);
    _video->setMouseTracking(true);
    _player->setVideoOutput(_video);

    connect(_player, &QMediaPlayer::mediaStatusChanged, this, &PlayInfo::mediaStatus);
    connect(_player, &QMediaPlayer::videoAvailableChanged, this, &PlayInfo::videoAvailableChanged);

    connect(_video, &VideoWidget::clicked, this, &PlayInfo::videoClicked);
    connect(_video, &VideoWidget::doubleClicked, this, &PlayInfo::videoDoubleClicked);

    connect(_video, &VideoWidget::mouseMoved, this, &PlayInfo::mouseMoved);

    mediaStatus(QMediaPlayer::MediaStatus::NoMedia);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(_image, 1);
    main_layout->addWidget(_video, 1);

    QVBoxLayout* nameLayout = new QVBoxLayout;
    nameLayout->addWidget(_author, 0, Qt::AlignCenter);
    nameLayout->addWidget(_name, 0, Qt::AlignCenter);

    QWidget* media_title_widget = new QWidget;
    media_title_widget->setObjectName("AlphaBGBorderRadius");
    media_title_widget->setLayout(nameLayout);
    media_title_widget->layout()->setSpacing(0);
    media_title_widget->layout()->setContentsMargins(5, 0, 5, 2);
    main_layout->addWidget(media_title_widget, 0, Qt::AlignCenter);

    setLayout(main_layout);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);
}

void PlayInfo::setMediaTitleVisible(bool v)
{
    _author->setVisible(v);
    _name->setVisible(v);
}

void PlayInfo::focus()
{
    _video->setFocus();
}

void PlayInfo::setTitle()
{
    QString title = "";

    switch (_player->mediaStatus()) {
    case QMediaPlayer::MediaStatus::InvalidMedia:
    case QMediaPlayer::MediaStatus::NoMedia:
    case QMediaPlayer::MediaStatus::UnknownMediaStatus:
        break;

    default:
        if (not _author->text().isEmpty())
            title += _author->text();
        if (not _name->text().isEmpty())
            title += " - " + _name->text();
    }

    if (not title.isEmpty())
        title += " # " + qApp->applicationName();

    emit newTitle(title);
}

void PlayInfo::mediaStatus(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::MediaStatus::BufferedMedia:
    case QMediaPlayer::MediaStatus::LoadedMedia:
        if (_player->availableMetaData().contains(QMediaMetaData::CoverArtImage)) {
            _image->setPixmap(qvariant_cast<QPixmap>(_player->metaData(QMediaMetaData::CoverArtImage)));
            emit newPixmap(qvariant_cast<QPixmap>(_player->metaData(QMediaMetaData::CoverArtImage)));
        } else {
            _image->setPixmap(qvariant_cast<QPixmap>(_player->metaData(QMediaMetaData::ThumbnailImage)));
            emit newPixmap(qvariant_cast<QPixmap>(_player->metaData(QMediaMetaData::ThumbnailImage)));
        }
        _author->setText(qvariant_cast<QString>(_player->metaData(QMediaMetaData::AlbumArtist)));
        _name->setText(qvariant_cast<QString>(_player->metaData(QMediaMetaData::Title)));
        break;

    case QMediaPlayer::MediaStatus::NoMedia:
        _image->setPixmap(QPixmap());
        _author->setText(tr("No media"));
        _name->setText("");
        break;

    case QMediaPlayer::MediaStatus::InvalidMedia:
        _image->setPixmap(QPixmap());
        _author->setText(tr("Invalid media"));
        _name->setText("");
        break;

    default:
        break;
    }

    setTitle();
}

void PlayInfo::videoAvailableChanged(bool v)
{
    _is_video = v;
    _image->setVisible(not v);
    _author->setVisible(not v);
    _video->setVisible(v);

    if (not _is_video and not _name->isVisible())
        emit fullScreenClicked();
}

void PlayInfo::videoClicked()
{
    _player->state() == QMediaPlayer::PlayingState ? _player->pause() : _player->play();
}

void PlayInfo::videoDoubleClicked()
{
    emit fullScreenClicked();
}
