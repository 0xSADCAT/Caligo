# This file is part of the Caligo multimedia player
# https://github.com/0xSADCAT/Caligo
# SPDX-License-Identifier: GPL-3.0-or-later

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Inside/librarymetascaner.cpp \
    Inside/metascaner.cpp \
    OtherWindows/aboutwindow.cpp \
    OtherWindows/helpwindow.cpp \
    OtherWindows/settingswindow.cpp \
    Widgets/controls.cpp \
    Widgets/image.cpp \
    Widgets/libraryelement.cpp \
    Widgets/libraryplaylists.cpp \
    Widgets/mediaelement.cpp \
    Widgets/medialibrary.cpp \
    Widgets/playinfo.cpp \
    Widgets/playlist.cpp \
    Widgets/playlistcontrols.cpp \
    Widgets/playlistelement.cpp \
    Widgets/timeslider.cpp \
    Widgets/videowidget.cpp \
    localsocket.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Inside/librarymetascaner.h \
    Inside/metascaner.h \
    OtherWindows/aboutwindow.h \
    OtherWindows/helpwindow.h \
    OtherWindows/settingswindow.h \
    Widgets/controls.h \
    Widgets/image.h \
    Widgets/libraryelement.h \
    Widgets/libraryplaylists.h \
    Widgets/mediaelement.h \
    Widgets/medialibrary.h \
    Widgets/playinfo.h \
    Widgets/playlist.h \
    Widgets/playlistcontrols.h \
    Widgets/playlistelement.h \
    Widgets/timeslider.h \
    Widgets/videowidget.h \
    localsocket.h \
    mainwindow.h

TRANSLATIONS += \
    Caligo_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = Res/icon.ico

# Uncomment next line for show qDebug() output
# DEFINES += DEBUG_OUTPUT
