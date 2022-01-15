/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LIBRARYPLAYLISTS_H
#define LIBRARYPLAYLISTS_H

#include <Widgets/playlistelement.h>
#include <Widgets/playlist.h>

class LibraryPlaylists : public QWidget
{
    Q_OBJECT
public:
    explicit LibraryPlaylists(Playlist* playlist, QWidget* parent = nullptr);

    QString getPathPlaylists() const;
    void setPathPlaylists(const QString& value);

    void setClearBeforeOpen(bool value);

public slots:
    void scan();

private:
    bool _clear_before_open = true;

    Playlist* _playlist;
    QList<PlaylistElement*> _elements;

    QString _playlists_path = qApp->applicationDirPath() + QDir::separator() + "playlists";

    QList<PlaylistElement*> _selection;
    PlaylistElement* _last_clicked = nullptr;

    void add(QString& path, QString& name);
    void remove(PlaylistElement* element);
    void remove(int index);
    void clear();

private slots:
    void elementClicked();
    void elementDoubleClicked();
    void elementShift();
    void elementCtrl();
    void elementFocus();

    void setPath();
};

#endif // LIBRARYPLAYLISTS_H
