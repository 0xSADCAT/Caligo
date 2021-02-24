/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "radioelement.h"

RadioElement::RadioElement(QString &url, QString &name, QWidget *parent) : QWidget(parent)
{
    nameLabel = new QLabel(name);
    urlLabel = new QLabel(url);

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(urlLabel, 1);
    l->addWidget(nameLabel, 0);
    setLayout(l);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);
}

QString RadioElement::getName() const
{
    return nameLabel->text();
}

QString RadioElement::getUrl() const
{
    return urlLabel->text();
}

void RadioElement::setSelected(bool v)
{
    if (v) {
        setStyleSheet(style::re::selected);
    }
    else {
        setStyleSheet(style::re::none);
    }
}

void RadioElement::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (e->modifiers() & Qt::ShiftModifier) {
            emit shiftClicked();
        }
        else if (e->modifiers() & Qt::ControlModifier) {
            emit ctrlClicked();
        }
        else {
            emit clicked();
        }
    }
}

void RadioElement::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        emit doubleClicked();
    }
}

void RadioElement::focusInEvent(QFocusEvent *)
{
    emit focus();
}
