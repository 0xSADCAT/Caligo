/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "libraryelement.h"

LibraryElement::LibraryElement(QString &path, QWidget *parent) : QWidget(parent)
{
    _path = path;
    _name = path;

    _name_label = new QLabel(path);

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addWidget(_name_label, 0);
    setLayout(main_layout);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);
}

QString LibraryElement::path() const
{
    return _path;
}

void LibraryElement::setText(const QString &value)
{
    if (value.isEmpty())
        return;

    _name = value;
    _name_label->setText(value);
}

QString LibraryElement::format() const
{
    QString s = "";

    s += _path;
    s += " ## ";
    if (not _name.isEmpty())
        s += _name;

    return s;
}

void LibraryElement::setSelected(bool selected)
{
    if (selected)
        setStyleSheet(qvariant_cast<QString>(qApp->property("LeSelectedQSS")));
    else
        setStyleSheet(qvariant_cast<QString>(qApp->property("LeNoneQSS")));
}

void LibraryElement::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() & Qt::ShiftModifier)
            emit shiftClicked();
        else if (event->modifiers() & Qt::ControlModifier)
            emit ctrlClicked();
        else
            emit clicked();
    }
}

void LibraryElement::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit doubleClicked();
}

void LibraryElement::focusInEvent(QFocusEvent*)
{
    emit focus();
}

QString LibraryElement::name() const
{
    return _name;
}
