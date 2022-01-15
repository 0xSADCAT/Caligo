/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "aboutwindow.h"

AboutWindow::AboutWindow() : QWidget(nullptr)
{
    setWindowIcon(QIcon(":/img/icon"));

    setWindowTitle(tr("About application") + " # " + qApp->applicationName());

    QLabel* title_label = new QLabel;

    QLabel* main_label = new QLabel;
    main_label->setWordWrap(true);

    QLabel* git_hub_link_label = new QLabel;
    git_hub_link_label->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QPushButton* open_in_browser_button = new QPushButton(tr("GitHub"));
    open_in_browser_button->setIcon(QIcon(":/img/github"));
    open_in_browser_button->setToolTip(tr("Open in browser"));

    QLabel* licence_label = new QLabel;
    licence_label->setWordWrap(true);

    QHBoxLayout* license_layout = new QHBoxLayout;
    QLabel* license_image = new QLabel;

    int image_width = qApp->desktop()->width() > 1920 ? 250 : 200;
    license_image->setPixmap(QPixmap(":/img/gpl").scaledToWidth(image_width));
    license_image->setFixedWidth(image_width);

    license_layout->addWidget(license_image, 0);
    license_layout->addWidget(licence_label, 1);

    QHBoxLayout* git_layout = new QHBoxLayout;
    git_layout->addWidget(git_hub_link_label, 1);
    git_layout->addWidget(open_in_browser_button, 0);
    git_layout->setSpacing(0);
    git_layout->setContentsMargins(0, 0, 0, 0);

    QPushButton* about_qt_button = new QPushButton(tr("About Qt"));
    about_qt_button->setIcon(QIcon(":/img/qt"));
    connect(about_qt_button, &QPushButton::clicked, qApp, &QApplication::aboutQt);
    about_qt_button->setStyleSheet("QPushButton {padding: 10px 10px 10px 10px; border: 1px solid black;}");

    QHBoxLayout *qt_layout = new QHBoxLayout;
    qt_layout->addStretch(1);
    qt_layout->addWidget(about_qt_button, 0);
    qt_layout->addStretch(1);
    qt_layout->setSpacing(0);
    qt_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(title_label, 0);
    l->addWidget(main_label, 0);
    l->addStretch(1);
    l->addLayout(license_layout, 0);
    l->addStretch(1);
    l->addLayout(git_layout, 0);
    l->addLayout(qt_layout, 0);

    QHBoxLayout* hl = new QHBoxLayout;
    hl->addLayout(l, 0);

    QScrollArea *scroll_area = new QScrollArea;
    QWidget *scroll_area_widget = new QWidget;

    scroll_area_widget->setLayout(hl);
    scroll_area->setWidget(scroll_area_widget);
    scroll_area->setWidgetResizable(true);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(scroll_area);
    setLayout(main_layout);

    title_label->setText(
                "<center><h2>" + qApp->applicationName() + " " + qApp->applicationVersion() +
                "</h2><br><h3>" + tr("About application") + "</h3></center>"
                );

    git_hub_link_label->setText(tr("Source code") + ": <a href='" + _git_hub_url + "'>"
                                + _git_hub_url + "</a>");

    main_label->setText(
                tr("<b>Caligo</b> - is an open source multimedia player.<br> At the moment, "
                   "testing is taking place on Linux and Windows, no testing has been conducted "
                   "on OSX, iOS and Android are not currently supported. The source code is "
                   "available at the link below.<br>The idea of the application is to implement "
                   "the minimum - necessary components of a multimedia player with an emphasis on "
                   "performance.<br>Help in using it is available in the corresponding menu.<br>"
                   "Development is currently being conducted by one person, some functions have "
                   "not yet been implemented. Development assistance would be welcome.<br>")
                );

    licence_label->setText(
                tr("This application is free software and is distributed under the GNU "
                   "General Public License. The license text can be found in the program "
                   "directory.")
                );

    main_label->setAlignment(Qt::AlignJustify);

    connect(open_in_browser_button, &QPushButton::clicked, this,
            &AboutWindow::open_github_in_browser);
}

void AboutWindow::open_github_in_browser()
{
    QDesktopServices::openUrl(_git_hub_url);
}
