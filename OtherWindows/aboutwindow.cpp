/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "aboutwindow.h"

AboutWindow::AboutWindow() : QWidget(nullptr)
{
  setWindowIcon(QIcon(":/img/icon"));

  link = "https://github.com/0xSADCAT/Caligo";

  setWindowTitle(tr("About application") + " # " + qApp->applicationName());

  title = new QLabel;
  mainLabel = new QLabel;
  mainLabel->setWordWrap(true);
  gitHubLinkLabel = new QLabel;
  gitHubLinkLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  openInBrowser = new QPushButton(tr("GitHub"));
  openInBrowser->setIcon(QIcon(":/img/github"));
  openInBrowser->setToolTip(tr("Open in browser"));
  setStyleSheet("QPushButton {border: 1px solid black;}");
  contactsLabel = new QLabel;
  contactsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  licenseLabel = new QLabel;
  licenseLabel->setWordWrap(true);
  QHBoxLayout *licenseLayout = new QHBoxLayout;
  QLabel *licenseImage = new QLabel;
  int imageWidth = qApp->desktop()->width() > 1920 ? 250 : 200;
  licenseImage->setPixmap(QPixmap(":/img/gpl").scaledToWidth(imageWidth));
  licenseImage->setFixedWidth(imageWidth);
  licenseLayout->addWidget(licenseImage, 0);
  licenseLayout->addWidget(licenseLabel, 1);

  QHBoxLayout *hl = new QHBoxLayout;
  QVBoxLayout *l = new QVBoxLayout;

  QHBoxLayout *gl = new QHBoxLayout;
  gl->addWidget(gitHubLinkLabel, 1);
  gl->addWidget(openInBrowser, 0);
  gl->setSpacing(0);
  gl->setContentsMargins(0, 0, 0, 0);

  QPushButton *aboutQtButton = new QPushButton(tr("About Qt"));
  aboutQtButton->setIcon(QIcon(":/img/qt"));
  connect(aboutQtButton, &QPushButton::clicked, qApp, &QApplication::aboutQt);
  aboutQtButton->setStyleSheet("QPushButton {padding: 10px 10px 10px 10px; border: 1px solid black;}");

  QHBoxLayout *cl = new QHBoxLayout;
  cl->addStretch(1);
  cl->addWidget(aboutQtButton, 0);
  cl->addStretch(1);
  cl->setSpacing(0);
  cl->setContentsMargins(0, 0, 0, 0);

  l->addWidget(title, 0);
  l->addWidget(mainLabel, 0);
  l->addStretch(1);
  l->addLayout(licenseLayout, 0);
  l->addStretch(1);
  l->addLayout(gl, 0);
  l->addWidget(contactsLabel, 0);
  l->addLayout(cl, 0);

  hl->addLayout(l, 0);
  QScrollArea *sa = new QScrollArea;
  QWidget *w = new QWidget;
  w->setLayout(hl);
  sa->setWidget(w);
  sa->setWidgetResizable(true);
  QVBoxLayout *la = new QVBoxLayout;
  la->addWidget(sa);
  setLayout(la);

  title->setText(
        "<center><h2>" + qApp->applicationName() + " " + qApp->applicationVersion() +
        "</h2><br><h3>" + tr("About application") + "</h3></center>"
        );

  gitHubLinkLabel->setText(tr("Source code") + ": <a href='" + link + "'>" + link + "</a>");

  contactsLabel->setText(
        tr("Contacts") + ":<br>"
                         "Email: alexsaltykow@gmail.com"
        );

  mainLabel->setText(
        tr("<b>Caligo</b> - is an open source multimedia player.<br>"
           "At the moment, testing is taking place on Linux and Windows, no testing has been conducted on OSX, "
           "iOS and Android are not currently supported. The source code is available at the link below.<br>"
           "The idea of the application is to implement the minimum - necessary components of a multimedia player with "
           "an emphasis on performance.<br>"
           "Help in using it is available in the corresponding menu.<br>"
           "Development is currently being conducted by one person, some functions have not yet been implemented. "
           "Development assistance would be welcome.<br>")
        );

  licenseLabel->setText(
        tr("This application is free software and is distributed under the GNU "
           "General Public License. The license text can be found in the program directory.")
        );

  mainLabel->setAlignment(Qt::AlignJustify);

  connect(openInBrowser, &QPushButton::clicked, this, &AboutWindow::oib);
}

void AboutWindow::oib()
{
  QDesktopServices::openUrl(link);
}
