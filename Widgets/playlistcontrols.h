#ifndef PLAYLISTCONTROLS_H
#define PLAYLISTCONTROLS_H

#include <QtWidgets>

#include <Widgets/playlist.h>

class PlaylistControls : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistControls(Playlist *pl, QWidget *parent = nullptr);

    void setSizes(int v);

    void setClearBeforeOpen(bool value);

    QString getPathPlaylists() const;
    void setPathPlaylists(const QString &value);

    QString getPathMusic() const;
    void setPathMusic(const QString &value);

private:
    Playlist *playlist;

    QPushButton *addButton;
    QPushButton *clearButton;

    QPushButton *savePlaylist;
    QPushButton *loadPlaylist;

    QPushButton *forceScanButton;

    bool clearBeforeOpen;

    QString pathPlaylists;
    QString pathMusic;

private slots:
    void add();
    void clear();

    void save();
    void load();

    void loadPath(const QString &path);
};

#endif // PLAYLISTCONTROLS_H
