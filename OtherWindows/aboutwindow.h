/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets>

/// About application
class AboutWindow : public QWidget
{
  Q_OBJECT
public:
  /// About application
  explicit AboutWindow();

private:
  QLabel *title;

  QLabel *mainLabel;

  QLabel *licenseLabel;

  QLabel *gitHubLinkLabel;

  QLabel *contactsLabel;

  QPushButton *openInBrowser;

  QString link;

private slots:
  /// Open GitHub repository in browser
  void oib();
};

#endif // ABOUTWINDOW_H
