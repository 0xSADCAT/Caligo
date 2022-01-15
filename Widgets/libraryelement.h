/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LIBRARYELEMENT_H
#define LIBRARYELEMENT_H

#include <QtWidgets>

class LibraryElement : public QWidget
{
    Q_OBJECT
public:
    explicit LibraryElement(QString &path, QWidget *parent = nullptr);

    QString path() const;

    void setText(const QString &value);

    QString format() const;

    void setSelected(bool selected);

    QString name() const;

signals:
    void clicked();
    void doubleClicked();
    void ctrlClicked();
    void shiftClicked();

    void focus();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void focusInEvent(QFocusEvent*) override;

private:
    QLabel* _name_label;

    QString _path;
    QString _name;
};

#endif // LIBRARYELEMENT_H
