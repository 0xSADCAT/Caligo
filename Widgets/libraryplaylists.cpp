/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "libraryplaylists.h"

LibraryPlaylists::LibraryPlaylists(Playlist* playlist, QWidget* parent)
    : QWidget(parent),
      _playlist(playlist)
{
    assert(playlist != nullptr);

    QVBoxLayout* main_layout = new QVBoxLayout;

    QHBoxLayout* header = new QHBoxLayout;

    QPushButton* scanButton = new QPushButton("");
    scanButton->setIcon(QIcon(":/img/scan"));
    scanButton->setToolTip(tr("Search playlists in selected directory"));
    connect(scanButton, &QPushButton::clicked, this, &LibraryPlaylists::scan);

    header->addStretch(1);
    header->addWidget(scanButton, 0);

    QVBoxLayout* header_layout = new QVBoxLayout;
    header_layout->addLayout(header, 0);

    QScrollArea* scroll_area = new QScrollArea;
    QWidget* scroll_widget = new QWidget;
    QVBoxLayout* scroll_area_layout = new QVBoxLayout;

    scroll_area_layout->addLayout(main_layout, 0);
    scroll_area_layout->addStretch(1);
    scroll_widget->setLayout(scroll_area_layout);
    scroll_area->setWidget(scroll_widget);
    scroll_area->setWidgetResizable(true);
    header_layout->addWidget(scroll_area, 1);

    setLayout(header_layout);
}

void LibraryPlaylists::add(QString &path, QString &name)
{
    PlaylistElement *element = new PlaylistElement(path, name);
    layout()->addWidget(element);
    _elements << element;

    connect(element, &PlaylistElement::clicked, this, &LibraryPlaylists::elementClicked);
    connect(element, &PlaylistElement::doubleClicked, this, &LibraryPlaylists::elementDoubleClicked);
    connect(element, &PlaylistElement::ctrlClicked, this, &LibraryPlaylists::elementCtrl);
    connect(element, &PlaylistElement::shiftClicked, this, &LibraryPlaylists::elementShift);
    connect(element, &PlaylistElement::focus, this, &LibraryPlaylists::elementFocus);
}

void LibraryPlaylists::remove(PlaylistElement* element)
{
    assert(element != nullptr);

    _selection.removeAll(element);
    if (_last_clicked == element) {
        if (_selection.isEmpty())
            _last_clicked = nullptr;
        else
            _last_clicked = _selection.back();
    }

    _elements.removeAll(element);
    layout()->removeWidget(element);
    element->deleteLater();
}

void LibraryPlaylists::remove(int index)
{
    if (index > _elements.count() - 1)
        return;

    remove(_elements[index]);
}

void LibraryPlaylists::clear()
{
    _selection.clear();
    _last_clicked = nullptr;

    foreach (PlaylistElement* element, _elements) {
        layout()->removeWidget(element);
        _elements.removeAll(element);
        element->deleteLater();
    }
}

void LibraryPlaylists::scan()
{
    if (_playlists_path.isEmpty())
        setPath();

    clear();

    QDir d(_playlists_path);
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
    _clear_before_open = value;
}

QString LibraryPlaylists::getPathPlaylists() const
{
    return _playlists_path;
}

void LibraryPlaylists::setPathPlaylists(const QString &value)
{
    _playlists_path = value;
    scan();
}

void LibraryPlaylists::elementClicked()
{
    _selection.clear();
    _last_clicked = (PlaylistElement*) sender();
    _selection << _last_clicked;
    foreach (PlaylistElement* e, _elements)
        e->setSelected(false);
    _last_clicked->setSelected(true);
}

void LibraryPlaylists::elementDoubleClicked()
{
    if (_clear_before_open)
        _playlist->clear();

    PlaylistElement* element = qobject_cast<PlaylistElement*>(sender());
    assert(element != nullptr);
    QFile file (element->path());
    bool needScan = false;

    if (file.open(QIODevice::ReadOnly)) {
        while (not file.atEnd()) {
            QString media = QString::fromLocal8Bit(file.readLine());
            media.remove("\n");
            if (media.isEmpty() or media.startsWith("#"))
                continue;

            QStringList splitted_line = media.split(" ## ");
            if (splitted_line.count() == 1) {
                _playlist->add(splitted_line[0]);
                needScan = true;
            }
            else {
                if (splitted_line[1] == " ") {
                    _playlist->add(splitted_line[0]);
                    needScan = true;
                }
                else {
                    _playlist->add(splitted_line[0], splitted_line[1]);
                }
            }
        }
        file.close();
    }
    if (needScan)
        _playlist->forceUpdate();

    _last_clicked = element;
}

void LibraryPlaylists::elementShift()
{
    if (_elements.count() < 2)
        return;

    PlaylistElement* from = _last_clicked;
    if (from == nullptr) {
        from = _last_clicked;
        if (from == nullptr)
            return;
    }

    _last_clicked = (PlaylistElement*) sender();

    int index_from = _elements.indexOf(from);
    int index_to = _elements.indexOf(_last_clicked);

    if (index_from == index_to)
        return;

    // XOR swap
    if (index_from > index_to)
        std::swap(index_from, index_to);

    for (auto* element : _elements) {
        if (not _selection.contains(element)) {
            _selection << element;
            element->setSelected(true);
        }
    }
}

void LibraryPlaylists::elementCtrl()
{
    _last_clicked = qobject_cast<PlaylistElement*>(sender());
    assert(_last_clicked != nullptr);

    if (_selection.contains(_last_clicked)) {
        _last_clicked->setSelected(false);
        _selection.removeAll(_last_clicked);
        return;
    } else {
        _selection << _last_clicked;
        _last_clicked->setSelected(true);
    }
}

void LibraryPlaylists::elementFocus()
{
    setFocus();
}

void LibraryPlaylists::setPath()
{
    QString path = QFileDialog::getExistingDirectory(0,
                                                    tr("Select directory") + " # " +
                                                    qApp->applicationName(),
                                                    QDir::home().absolutePath());
    if (path.isEmpty())
        return;
    _playlists_path = path;
}
