/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "playlistelement.h"

PlaylistElement::PlaylistElement(const QString& path, const QString& name, QWidget* parent)
    : QWidget(parent),
      _path(path)
{
    _name_label = new QLabel(name.isEmpty() ? path : name);

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addWidget(_name_label, 0);
    setLayout(main_layout);

    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);
}

QString PlaylistElement::name() const
{
    return _name_label->text();
}

QString PlaylistElement::format() const
{
    if (_name_label->text() == _path)
        return _path + " ## ";
    else
        return _path + " ## " + _name_label->text();
}

void PlaylistElement::setSelected(bool selected)
{
    if (selected)
        setStyleSheet(qvariant_cast<QString>(qApp->property("LeSelectedQSS")));
    else
        setStyleSheet(qvariant_cast<QString>(qApp->property("LeNoneQSS")));
}

void PlaylistElement::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() & Qt::ControlModifier)
            emit ctrlClicked();
        else if (event->modifiers() & Qt::ShiftModifier)
            emit shiftClicked();
        else
            emit clicked();
    }
}

void PlaylistElement::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit doubleClicked();
}

void PlaylistElement::focusInEvent(QFocusEvent*)
{
    emit focus();
}

QString PlaylistElement::path() const
{
    return _path;
}
