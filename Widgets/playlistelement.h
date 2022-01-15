/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef ELEMENTPLAYLIST_H
#define ELEMENTPLAYLIST_H

#include <QtWidgets>

class PlaylistElement : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistElement(const QString& path, const QString& name = "",
                             QWidget *parent = nullptr);

    QString name() const;

    QString path() const;

    QString format() const;

    void setSelected(bool selected);

signals:
    void clicked();
    void doubleClicked();
    void shiftClicked();
    void ctrlClicked();
    void focus();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void focusInEvent(QFocusEvent*) override;

private:
    QLabel* _name_label;
    QString _path;
};

#endif // ELEMENTPLAYLIST_H
