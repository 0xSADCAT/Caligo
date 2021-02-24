/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "elementplaylist.h"

ElementPlaylist::ElementPlaylist(QString &path, QString &name, QWidget *parent) : QWidget(parent)
{
    this->path = path;
    if (name.isEmpty()) {
        name = path;
    }
    nameLabel = new QLabel(name);

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(nameLabel, 0);
    setLayout(l);

    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);
}

QString ElementPlaylist::getName() const
{
    return nameLabel->text();
}

QString ElementPlaylist::getString() const
{
    if (nameLabel->text() == path) {
        return path + " ## ";
    }
    else {
        return path + " ## " + nameLabel->text();
    }
}

void ElementPlaylist::setSelected(bool v)
{
    if (v) {
        setStyleSheet(style::le::selected);
    }
    else {
        setStyleSheet(style::le::none);
    }
}

void ElementPlaylist::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (e->modifiers() & Qt::ControlModifier) {
            emit ctrlClicked();
        }
        else if (e->modifiers() & Qt::ShiftModifier) {
            emit shiftClicked();
        }
        else {
            emit clicked();
        }
    }
}

void ElementPlaylist::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        emit doubleClicked();
    }
}

void ElementPlaylist::focusInEvent(QFocusEvent *)
{
    emit focus();
}

QString ElementPlaylist::getPath() const
{
    return path;
}
