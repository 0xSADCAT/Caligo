/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mediaelement.h"
#include "Inside/formatter.hpp"

MediaElement::MediaElement(const QString& path, QWidget* parent)
    : QWidget(parent),
      _file_path(path),
      _text_label(new QLabel("  " + path))
{
    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addWidget(_text_label);
    setLayout(main_layout);

    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);
}

QString MediaElement::path() const
{
    return _file_path;
}

bool MediaElement::hasMetadata() const
{
    return _has_metadata;
}

void MediaElement::setText(const QString &text)
{
    _text_label->setText(text);
    _has_metadata = true;
}

void MediaElement::setPlaying(bool value)
{
    _is_playing = value;
}

QString MediaElement::format() const
{
    return MediaElementFormat().format(_file_path, _text_label->text());
}
