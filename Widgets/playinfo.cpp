/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "playinfo.h"

PlayInfo::PlayInfo(QMediaPlayer *mp, QWidget *parent) : QWidget(parent)
// Shows metadata of current track if this is music or video.
{
#ifdef DEBUG_OUTPUT
  qDebug() << ">>> PlayInfo init";
#endif

  player = mp;
  image = new Image;
  author = new QLabel;
  name = new QLabel;
  video = new VideoWidget;
  isVideo = false;
  isFSVideo = false;

  author->setFont(QFont(this->font().family(), 12, QFont::Bold));
  name->setFont(QFont(this->font().family(), 10));

  video->setVisible(false);
  player->setVideoOutput(video);

  QVBoxLayout *l = new QVBoxLayout;
  l->addWidget(image, 1);
  l->addWidget(video, 1);
  QVBoxLayout *nameLayout = new QVBoxLayout;
  nameLayout->addWidget(author, 0, Qt::AlignCenter);
  nameLayout->addWidget(name, 0, Qt::AlignCenter);
  QWidget *w = new QWidget;
  w->setObjectName("AlphaBGBorderRadius");
  w->setLayout(nameLayout);
  w->layout()->setSpacing(0);
  w->layout()->setContentsMargins(5, 0, 5, 2);
  l->addWidget(w, 0, Qt::AlignCenter);
  setLayout(l);

  connect(player, &QMediaPlayer::mediaStatusChanged, this, &PlayInfo::mediaStatus);
  connect(player, &QMediaPlayer::videoAvailableChanged, this, &PlayInfo::videoChanged);

  connect(video, &VideoWidget::clicked, this, &PlayInfo::videoClicked);
  connect(video, &VideoWidget::doubleClicked, this, &PlayInfo::videoDoubleClicked);

  mediaStatus(QMediaPlayer::MediaStatus::NoMedia);

  layout()->setSpacing(0);
  layout()->setContentsMargins(0, 0, 0, 0);
}

void PlayInfo::setNotFull(bool v)
{
  author->setVisible(v);
  name->setVisible(v);
}

void PlayInfo::focus()
{
  video->setFocus();
}

void PlayInfo::setTitle()
// Set new winodw title.
{
  QString s = "";

  switch (player->mediaStatus()) {
    case QMediaPlayer::MediaStatus::InvalidMedia:
    case QMediaPlayer::MediaStatus::NoMedia:
    case QMediaPlayer::MediaStatus::UnknownMediaStatus:
      break;

    default:
      if (not author->text().isEmpty()) {
          s += author->text();
        }
      if (not name->text().isEmpty()) {
          s += " - " + name->text();
        }
    }

  if (not s.isEmpty()) {
      s += " # " + qApp->applicationName();
    }

  emit newTitle(s);
}

/* private SLOT */ void PlayInfo::mediaStatus(QMediaPlayer::MediaStatus s)
{
#ifdef DEBUG_OUTPUT
  qDebug() << "PlayInfo::mediaStatus" << s;
#endif

  switch (s) {
    case QMediaPlayer::MediaStatus::BufferedMedia:
    case QMediaPlayer::MediaStatus::LoadedMedia:
      if (player->availableMetaData().contains(QMediaMetaData::CoverArtImage)) {
          image->setPix(qvariant_cast<QPixmap>(player->metaData(QMediaMetaData::CoverArtImage)));
          emit newPixmap(qvariant_cast<QPixmap>(player->metaData(QMediaMetaData::CoverArtImage)));
        }
      else {
          image->setPix(qvariant_cast<QPixmap>(player->metaData(QMediaMetaData::ThumbnailImage)));
          emit newPixmap(qvariant_cast<QPixmap>(player->metaData(QMediaMetaData::ThumbnailImage)));
        }
      author->setText(qvariant_cast<QString>(player->metaData(QMediaMetaData::AlbumArtist)));
      name->setText(qvariant_cast<QString>(player->metaData(QMediaMetaData::Title)));
      break;

    case QMediaPlayer::MediaStatus::NoMedia:
      image->setPix(QPixmap());
      author->setText(tr("No media"));
      name->setText("");
      break;

    case QMediaPlayer::MediaStatus::InvalidMedia:
      image->setPix(QPixmap());
      author->setText(tr("Invalid media"));
      name->setText("");
      break;

    default:
      break;
    }

  setTitle();
}

/* private SLOT */ void PlayInfo::videoChanged(bool v)
// Sets visibility of Album image or QVideoWidget
{
#ifdef DEBUG_OUTPUT
  qDebug() << "PlayInfo::videoChanged" << v;
#endif

  isVideo = v;
  image->setVisible(not v);
  author->setVisible(not v);
  video->setVisible(v);

  if (not isVideo and not name->isVisible()) {
      emit fsClicked();
    }
}

/* private SLOT */ void PlayInfo::videoClicked()
{
  if (player->state() == QMediaPlayer::PlayingState) {
      player->pause();
    }
  else {
      player->play();
    }
}

/* private SLOT */ void PlayInfo::videoDoubleClicked()
{
  emit fsClicked();
}
