/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MEDIAELEMENT_H
#define MEDIAELEMENT_H

#include <QtWidgets>

/**
 * @brief The MediaElement class provides element of playlist
 */
class MediaElement : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief The MediaElement class provides element of playlist
     */
    explicit MediaElement(const QString& path, QWidget* parent = nullptr);

    /**
     * @brief Path to media
     * @return Path to media
     */
    QString path() const;

    /**
     * @brief Checks media metadata
     * @return Checks media metadata
     */
    bool hasMetadata() const;

    /**
     * @brief Set text to label
     * @param text Text
     */
    void setText(const QString &text);

    /**
     * @brief Set playing state
     * @param value State (true - playing)
     */
    void setPlaying(bool value);

    /**
     * @brief Converst to string format
     * @return Formated string
     */
    QString format() const;

private:
    QString _file_path;

    QLabel* _text_label;

    bool _has_metadata = false;
    bool _is_playing = false;
};

#endif // MEDIAELEMENT_H
