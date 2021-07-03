<!--
SPDX-License-Identifier: LGPL-3.0-or-later
-->

# Caligo
Simple multimedia player.

## Introduction
<b>Caligo</b> - simple multimedia player. The idea of the project is to implement a minimal set of tools for playing various multimedia formats, including Internet radio. The minimalism of the interface and functionality allows you to achieve a relatively low resource consumption.
![Screenshot Caligo mainwindow](https://i.ibb.co/T4zp5SB/Main-Window.png)
![Screenshot Caligo media library](https://i.ibb.co/BzNyT6W/media-Library.png)
![Screenshot Caligo minimal view playlist](https://i.ibb.co/ZfkxXQ5/Hidden-Playlist.png)
![Screenshot Caligo minimal view play information](https://i.ibb.co/YWd3Jmx/Hidden-Info.png)
<br>The functionality includes scanning the selected directory for the presence of multimedia files and compiling a media library. It is also possible to create and save playlists and Internet radio lists by category.

## Playlists formats
Playlists must have the extension <b>*.cpl</b> (Caligo playlist).
Playlist is a plain text document that contains a file path or a link to a stream. By default, the ./playlists directory is used for playlists. If you need to add a name, then after the path to the file or the link to the stream, write the name, separated by a combination of characters <b>" ## "</b> (without quotes). Also, you can add comments to the lists, for this the line must start with the <b>#</b> character. The name of the list that is displayed in the program corresponds to a file name without an extension.

## Known bugs
1. Temporary freeze or slowdown of the GUI when scanning a large number of files. The reason is unknown, noticed a correlation with the slow HDD or congestion CPU. Failed to play. Observed on Windows 7 64 bit.
2. Double-wedging or highlighting and pressing Enter in the library does not produce the expected result (adding to the playlist). During testing on Windows 7 64 bit, the application reaction was 5-15 minutes after the user's action, while everything else was functioning correctly, playback was not interrupted. The problem was not observed on Linux OS. The error could not be reproduced or the cause could not be found.
3. Incorrect behavior of the style sheet on Windows 7 64-bit OS and on Linux with a Gnome 3 desktop environment. The problem was noticed with the translucency of some elements. You can fix it by simplifying the style sheet in the <b>./style.qss</b> file by deleting / disabling sections. <b>#AlphaBG</b> is responsible for this in the file.
