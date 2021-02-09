QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Inside/metascaner.cpp \
    OtherWindows/aboutwindow.cpp \
    OtherWindows/helpwindow.cpp \
    OtherWindows/settingswindow.cpp \
    Style/style.cpp \
    Widgets/controls.cpp \
    Widgets/image.cpp \
    Widgets/mediaelement.cpp \
    Widgets/playinfo.cpp \
    Widgets/playlist.cpp \
    Widgets/playlistcontrols.cpp \
    Widgets/timeslider.cpp \
    Widgets/videowidget.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Inside/metascaner.h \
    OtherWindows/aboutwindow.h \
    OtherWindows/helpwindow.h \
    OtherWindows/settingswindow.h \
    Widgets/controls.h \
    Widgets/image.h \
    Widgets/mediaelement.h \
    Widgets/playinfo.h \
    Widgets/playlist.h \
    Widgets/playlistcontrols.h \
    Widgets/timeslider.h \
    Widgets/videowidget.h \
    widget.h

TRANSLATIONS += \
    Caligo_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = Res/icon.ico
