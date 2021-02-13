#include "mediaelement.h"

MediaElement::MediaElement(const QString &path, QWidget *parent) : QWidget(parent)
// Custom widget. Element of playlist. Contains model and view of component.
{
    this->path = path;

    text = new QLabel("  " + path);

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(text);
    setLayout(l);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);

    playing = false;
    selected = false;

    contextMenu = new QMenu;
    contextMenu->addAction(tr("Select all"), this, &MediaElement::selectAll);
    contextMenu->addAction(tr("Remove selected"), this, &MediaElement::deleteSelected);
}

QString MediaElement::getPath() const
{
    return path;
}

bool MediaElement::hasMeta() const
{
    return meta;
}

void MediaElement::setText(const QString &text)
// Set metadata
{
    this->text->setText("  " + text);
    meta = true;
}

void MediaElement::setPlaying(bool value)
{
    playing = value;
    updStyle();
}

void MediaElement::setSelected(bool value)
{
    selected = value;
    updStyle();
}

void MediaElement::mousePressEvent(QMouseEvent *e)
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
    emit focus();
}

void MediaElement::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        emit doubleClicked();
    emit focus();
}

void MediaElement::focusInEvent(QFocusEvent *)
{
    emit focus();
}

void MediaElement::contextMenuEvent(QContextMenuEvent *e)
{
    contextMenu->exec(e->globalPos());
}

void MediaElement::updStyle()
{
    if (playing && selected) {
        setStyleSheet(style::me::all);
    }
    else if (playing) {
        setStyleSheet(style::me::playing);
    }
    else if (selected) {
        setStyleSheet(style::me::selected);
    }
    else {
        setStyleSheet(style::me::none);
    }
}
