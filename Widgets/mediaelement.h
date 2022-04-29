/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MEDIAELEMENT_H
#define MEDIAELEMENT_H

#include <QtWidgets>

class MediaElement : public QWidget
{
    Q_OBJECT
public:
    explicit MediaElement(const QString& path, QWidget* parent = nullptr);

    QString path() const;

    bool hasMetadata() const;

    void setText(const QString &text);

    void setPlaying(bool value);

    QString format() const;

protected:
    void focusInEvent(QFocusEvent*) override;

private:
    QString _file_path;

    QLabel* _text_label;

    bool _has_metadata = false;
    bool _is_playing = false;

    QPoint _drag_position;
};

#endif // MEDIAELEMENT_H
