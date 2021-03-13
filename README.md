<!--
SPDX-License-Identifier: LGPL-3.0-or-later
-->

# Caligo
Simple multimedia player.

## Introduction
Caligo - simple multimedia player. The idea of the project is to implement a minimal set of tools for playing various multimedia formats, including Internet radio. The minimalism of the interface and functionality allows you to achieve a relatively low resource consumption.
![Screenshot Caligo now playing](https://i.ibb.co/bWn66T1/1-en.png)
![Screenshot Caligo media library](https://i.ibb.co/yh5v1SK/2-en.png)
![Screenshot Caligo settings](https://i.ibb.co/zGfXY8P/3-en.png)
![Screenshot Caligo minimal view](https://i.ibb.co/k1S2rxq/4-en.png)
The functionality includes scanning the selected directory for the presence of multimedia files and compiling a media library. It is also possible to create and save playlists and Internet radio lists by category.

## Playlists formats
Playlists must have the extension *.cpl (Caligo playlist).
Playlist is a plain text document that contains a file path or a link to a stream. By default, the ./playlists directory is used for playlists. If you need to add a name, then after the path to the file or the link to the stream, write the name, separated by a combination of characters <b>" ## "</b> (without quotes). Also, you can add comments to the lists, for this the line must start with the <b>#</b> character. The name of the list that is displayed in the program corresponds to a file name without an extension.
