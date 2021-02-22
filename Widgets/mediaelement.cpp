#include "mediaelement.h"

MediaElement::MediaElement(const QString &path, QWidget *parent) : QWidget(parent)
// Custom widget. Element of playlist. Contains model and view of component.
{
#ifdef DEBUG_OUTPUT
        qDebug() << ">>> MediaElement init:" << path;
#endif

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
    contextMenu->addAction(QPixmap(":/img/selectAll"), tr("Select all"), this, &MediaElement::selectAll);
    contextMenu->addAction(QPixmap(":/img/delete"), tr("Remove selected"), this, &MediaElement::deleteSelected);
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
#ifdef DEBUG_OUTPUT
        qDebug() << "MediaElement::setText" << path;
        qDebug() << "---> " << text;
#endif

    this->text->setText(text);
    meta = true;
}

void MediaElement::setPlaying(bool value)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "MediaElement::setPlaying" << path;
        qDebug() << "---> " << value;
#endif

    playing = value;
    updStyle();
}

void MediaElement::setSelected(bool value)
{
#ifdef DEBUG_OUTPUT
        qDebug() << "MediaElement::setSelected" << path;
        qDebug() << "---> " << value;
#endif

    selected = value;
    updStyle();
}

QString MediaElement::getString() const
{
    QString s;
    s += path;
    s += " ## ";
    if (text->text() != path) {
        s += text->text();
    }
    return s;
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
