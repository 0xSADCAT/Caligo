#ifndef LIBRARYPLAYLISTS_H
#define LIBRARYPLAYLISTS_H

#include <Widgets/elementplaylist.h>
#include <Widgets/playlist.h>

class LibraryPlaylists : public QWidget
{
    Q_OBJECT
public:
    explicit LibraryPlaylists(Playlist *pls, QWidget *parent = nullptr);

    QString getPathPlaylists() const;
    void setPathPlaylists(const QString &value);

public slots:
    void scan();

private:
    Playlist *playlist;
    QList<ElementPlaylist*> list;
    QVBoxLayout *mainLayout;

    QString pathPlaylists;

    void add(QString &path, QString &name);
    void remove(ElementPlaylist *e);
    void remove(int index);
    void clear();

    QList<ElementPlaylist*> selection;
    ElementPlaylist *lastClicked;

private slots:
    void elementClicked();
    void elementDouble();
    void elementShift();
    void elementCtrl();
    void elementFocus();

    void setPath();
};

#endif // LIBRARYPLAYLISTS_H
