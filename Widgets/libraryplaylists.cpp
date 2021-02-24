/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "libraryplaylists.h"

LibraryPlaylists::LibraryPlaylists(Playlist *pls, QWidget *parent) : QWidget(parent)
{
    clearBeforeOpen = true;

    playlist = pls;
    pathPlaylists = qApp->applicationDirPath() + QDir::separator() + "playlists";
    mainLayout = new QVBoxLayout;
    lastClicked = nullptr;

    QHBoxLayout *header = new QHBoxLayout;

    QPushButton *scanButton = new QPushButton("");
    scanButton->setIcon(QIcon(":/img/scan"));
    scanButton->setToolTip(tr("Search playlists in selected directory"));
    connect(scanButton, &QPushButton::clicked, this, &LibraryPlaylists::scan);

    header->addStretch(1);
    header->addWidget(scanButton, 0);

    QVBoxLayout *l = new QVBoxLayout;
    l->addLayout(header, 0);
    QScrollArea *sa = new QScrollArea;
    QWidget *w = new QWidget;
    QVBoxLayout *sal = new QVBoxLayout;
    sal->addLayout(mainLayout, 0);
    sal->addStretch(1);
    w->setLayout(sal);
    sa->setWidget(w);
    sa->setWidgetResizable(true);
    l->addWidget(sa, 1);
    setLayout(l);
}

void LibraryPlaylists::add(QString &path, QString &name)
{
    ElementPlaylist *e = new ElementPlaylist(path, name);
    mainLayout->addWidget(e);
    list << e;

    connect(e, &ElementPlaylist::clicked, this, &LibraryPlaylists::elementClicked);
    connect(e, &ElementPlaylist::doubleClicked, this, &LibraryPlaylists::elementDouble);
    connect(e, &ElementPlaylist::ctrlClicked, this, &LibraryPlaylists::elementCtrl);
    connect(e, &ElementPlaylist::shiftClicked, this, &LibraryPlaylists::elementShift);
    connect(e, &ElementPlaylist::focus, this, &LibraryPlaylists::elementFocus);
}

void LibraryPlaylists::remove(ElementPlaylist *e)
{
    selection.removeAll(e);
    if (lastClicked == e) {
        if (selection.isEmpty()) {
            lastClicked = nullptr;
        }
        else {
            lastClicked = selection.back();
        }
    }

    list.removeAll(e);
    mainLayout->removeWidget(e);
    e->~ElementPlaylist();
}

void LibraryPlaylists::remove(int index)
{
    if (index > list.count() - 1)
        return;

    remove(list[index]);
}

void LibraryPlaylists::clear()
{
    selection.clear();
    lastClicked = nullptr;

    foreach (ElementPlaylist *e, list) {
        mainLayout->removeWidget(e);
        list.removeAll(e);
        e->~ElementPlaylist();
    }
}

void LibraryPlaylists::scan()
{
    if (pathPlaylists.isEmpty()) {
        setPath();
    }

    clear();

    QDir d(pathPlaylists);
    QStringList files;
    QStringList fl = d.entryList(QDir::Files);
    foreach (QString file, fl) {
        if (file.endsWith(".cpl"))
            files << d.absoluteFilePath(file);
    }

    QString empty = "";
    foreach (QString s, files) {
        QString name = QFileInfo(s).fileName();
        name.remove(".cpl");
        add(s, name);
    }
}

void LibraryPlaylists::setClearBeforeOpen(bool value)
{
    clearBeforeOpen = value;
}

QString LibraryPlaylists::getPathPlaylists() const
{
    return pathPlaylists;
}

void LibraryPlaylists::setPathPlaylists(const QString &value)
{
    pathPlaylists = value;
    scan();
}

void LibraryPlaylists::elementClicked()
{
    selection.clear();
    lastClicked = (ElementPlaylist*) sender();
    selection << lastClicked;
    foreach (ElementPlaylist* e, list) {
        e->setSelected(false);
    }
    lastClicked->setSelected(true);
}

void LibraryPlaylists::elementDouble()
{
    if (clearBeforeOpen) {
        playlist->clear();
    }

    ElementPlaylist *e = (ElementPlaylist*) sender();
    QFile file(e->getPath());
    bool needScan = false;
    if (file.open(QIODevice::ReadOnly)) {
        while (not file.atEnd()) {
            QString str = file.readLine();
            str.remove("\n");
            if (str.isEmpty() or str.startsWith("#")) {
                continue;
            }
            QStringList li = str.split(" ## ");
            if (li.count() == 1) {
                playlist->add(li[0]);
                needScan = true;
            }
            else {
                if (li[1] == " ") {
                    playlist->add(li[0]);
                    needScan = true;
                }
                else {
                    playlist->add(li[0], li[1]);
                }
            }
        }
        file.close();
    }
    if (needScan) {
        playlist->forceUpdate();
    }

    lastClicked = e;
}

void LibraryPlaylists::elementShift()
{
    if (list.count() < 2)
        return;

    ElementPlaylist *from = lastClicked;
    if (from == nullptr) {
        from = lastClicked;
        if (from == nullptr) {
            return;
        }
    }

    lastClicked = (ElementPlaylist*) sender();

    int iFrom = list.indexOf(from);
    int iTo = list.indexOf(lastClicked);

    if (iFrom == iTo)
        return;

    // XOR swap
    if (iFrom > iTo) {
        iFrom ^= iTo;
        iTo ^= iFrom;
        iFrom ^= iTo;
    }

    for (int i = iFrom; i <= iTo; ++i) {
        if (not selection.contains(list[i])) {
            selection << list[i];
            list[i]->setSelected(true);
        }
    }
}

void LibraryPlaylists::elementCtrl()
{
    lastClicked = (ElementPlaylist*) sender();
    if (selection.contains(lastClicked)) {
        lastClicked->setSelected(false);
        selection.removeAll(lastClicked);
        return;
    }
    else {
        selection << lastClicked;
        lastClicked->setSelected(true);
    }
}

void LibraryPlaylists::elementFocus()
{
    this->setFocus();
}

void LibraryPlaylists::setPath()
{
    QString str = QFileDialog::getExistingDirectory(0, tr("Select directory") + " # " + qApp->applicationName(), QDir::home().absolutePath());
    if (str.isEmpty())
        return;
    pathPlaylists = str;
}
