/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "helpwindow.h"

static QVBoxLayout* createHotkeyLayout(const QString& group_name,
                                       const QList<QPair<QString, QString>> hotkeys);

HelpWindow::HelpWindow() : QWidget(nullptr)
{
    QScrollArea* scroll_area = new QScrollArea;
    QVBoxLayout* hotkey_layout = new QVBoxLayout;
    QWidget* scroll_area_widget = new QWidget;

    scroll_area_widget->setLayout(hotkey_layout);
    scroll_area_widget->layout()->setSpacing(0);
    scroll_area_widget->layout()->setContentsMargins(0, 0, 0, 0);

    scroll_area->setWidget(scroll_area_widget);
    scroll_area->setWidgetResizable(true);

    QVBoxLayout *main_layout = new QVBoxLayout;
    setLayout(main_layout);
    main_layout->addWidget(scroll_area);
    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);

    hotkey_layout->addLayout(createHotkeyLayout(
                                 tr("Controls"),
                                 {
                                     {"F", tr("Toggle full screen mode (video only)")},
                                     {"Esc", tr("Exit full screen mode (video only)")},
                                     {"N", tr("Next track")},
                                     {"B", tr("Previous track")},
                                     {"Ctrl+M", tr("Mute")},
                                     {"S", tr("Stop playing")},
                                     {"P", tr("Play / Pause")},
                                     {"Num+", tr("Increase volume")},
                                     {"Num-", tr("Decrease volume")}
                                 }));

    hotkey_layout->addLayout(createHotkeyLayout(
                                 tr("Playlist"),
                                 {
                                     {"Ctrl+O", tr("Open music")}, {"Ctrl+U", tr("Open URL")},
                                     {"Shift+O", tr("Open playlist")},
                                     {"Ctrl+Shift+S", tr("Save playlist")},
                                     {"Ctrl+Shift+C", tr("Clear playlist")},
                                     {"Shift+U", tr("Update playlist metadata")}
                                 }));

    hotkey_layout->addLayout(createHotkeyLayout(
                                 tr("Other"),
                                 {
                                     {"Ctrl+H", tr("Open this window")}
                                 }));
    hotkey_layout->addStretch(1);
}

void HelpWindow::openGitHub()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Alex13kyky/Caligo"));
}

QVBoxLayout* createHotkeyLayout(const QString& group_name,
                                const QList<QPair<QString, QString>> hotkeys)
{
    QVBoxLayout* result = new QVBoxLayout;

    result->addWidget(new QLabel("<center><b>" + group_name + "</b></center>"));
    QGridLayout* key_layout = new QGridLayout;
    key_layout->setContentsMargins(5, 5, 5, 5);
    result->addLayout(key_layout);

    int index = 0;
    for (auto& key : hotkeys) {
        key_layout->addWidget(new QLabel(key.first), index, 0);
        key_layout->addWidget(new QLabel(key.second), index, 1);
        ++index;
    }
    result->addSpacing(5);

    return result;
}
