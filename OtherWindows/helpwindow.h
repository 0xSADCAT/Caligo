/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QtWidgets>

class HelpWindow : public QWidget
{
  Q_OBJECT
public:
  HelpWindow();

private slots:
  /// Open GitHub repository in browser
  void openGitHub();
};

#endif // HELPWINDOW_H
