/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets>

class AboutWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWindow();

private:
    QString _git_hub_url = "https://github.com/0xSADCAT/Caligo";

private slots:
    void open_github_in_browser();
};

#endif // ABOUTWINDOW_H
