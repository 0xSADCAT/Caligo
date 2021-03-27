<!--
SPDX-License-Identifier: LGPL-3.0-or-later
-->

# Caligo
Simple multimedia player.

## Introduction
Caligo - simple multimedia player. The idea of the project is to implement a minimal set of tools for playing various multimedia formats, including Internet radio. The minimalism of the interface and functionality allows you to achieve a relatively low resource consumption.
![Screenshot Caligo mainwindow](https://i.ibb.co/T4zp5SB/Main-Window.png)
![Screenshot Caligo media library](https://i.ibb.co/BzNyT6W/media-Library.png)
![Screenshot Caligo minimal view playlist](https://i.ibb.co/ZfkxXQ5/Hidden-Playlist.png)
![Screenshot Caligo minimal view play information](https://i.ibb.co/YWd3Jmx/Hidden-Info.png)

The functionality includes scanning the selected directory for the presence of multimedia files and compiling a media library. It is also possible to create and save playlists.

## Playlists formats
Playlists must have the extension *.cpl (Caligo playlist).
Playlist is a plain text document that contains a file path or a link to a stream. By default, the ./playlists directory is used for playlists. If you need to add a name, then after the path to the file or the link to the stream, write the name, separated by a combination of characters <b>" ## "</b> (without quotes). Also, you can add comments to the lists, for this the line must start with the <b>#</b> character. The name of the list that is displayed in the program corresponds to a file name without an extension.
