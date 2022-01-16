#include "playlistwidget.hpp"

PlaylistWidget::PlaylistWidget(QMediaPlayer* media_player, QWidget *parent)
    : QWidget(parent),
      _playlist(new Playlist(media_player)),
      _playlist_controls(new PlaylistControls(_playlist))
{
    _playlist_controls->setButtonsSizes(16);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(_playlist_controls, 0);
    QScrollArea* scroll_area = new QScrollArea;
    scroll_area->setWidget(_playlist);
    scroll_area->setWidgetResizable(true);
    scroll_area->setFrameStyle(QFrame::NoFrame);
    main_layout->addWidget(scroll_area, 1);

    setLayout(main_layout);
    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);
}

Playlist* PlaylistWidget::playlist() const
{
    return _playlist;
}

PlaylistControls* PlaylistWidget::playlistControls() const
{
    return _playlist_controls;
}
