#include "libraryelement.h"

LibraryElement::LibraryElement(QString &path, QWidget *parent) : QWidget(parent)
{
    this->path = path;
    name = path;

    nameLabel = new QLabel(path);

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(nameLabel, 0);
    setLayout(l);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);
}

QString LibraryElement::getPath() const
{
    return path;
}

void LibraryElement::setText(const QString &value)
{
    if (value.isEmpty())
        return;

    name = value;
    nameLabel->setText(value);
}

QString LibraryElement::getString() const
{
    QString s = "";

    s += path;
    s += " ## ";
    if (not name.isEmpty())
        s += name;

    return s;
}

void LibraryElement::setSelected(bool v)
{
    if (v) {
        setStyleSheet(style::le::selected);
    }
    else {
        setStyleSheet(style::le::none);
    }
}

void LibraryElement::mousePressEvent(QMouseEvent *e)
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

void LibraryElement::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        emit doubleClicked();
    }
}

void LibraryElement::focusInEvent(QFocusEvent *)
{
    emit focus();
}

QString LibraryElement::getName() const
{
    return name;
}
