/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef RADIOLIBRARY_H
#define RADIOLIBRARY_H

#include <Widgets/radioelement.h>
#include <Widgets/playlist.h>

class RadioLibrary : public QWidget
{
    Q_OBJECT
public:
    explicit RadioLibrary(Playlist *pls, QWidget *parent = nullptr);

    QString getRadioPath() const;
    void setRadioPath(const QString &value);

public slots:
    void scanLibrary();

private:
    Playlist *playlist;
    QList<RadioElement*> list;
    QVBoxLayout *mainLayout;

    QList<RadioElement*> selection;
    RadioElement *lastClicked;

    void clear();
    void remove(RadioElement *e);
    void remove(int index);
    void add(QString url, QString name = "");

    QString radioPath;

    void save(const QString& fileName);

    QListWidget *listWidget;

    void scanDir(QDir d);
    QStringList files;

private slots:
    void elementClicked();
    void elementDouble();
    void elementCtrl();
    void elementShift();
    void elementFocus();

    void setLibraryPath();

    void itemClicked(QListWidgetItem *item);
};

#endif // RADIOLIBRARY_H
