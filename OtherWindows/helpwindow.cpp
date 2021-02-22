#include "helpwindow.h"

HelpWindow::HelpWindow() : QWidget(nullptr)
{
    setWindowIcon(QIcon(":/img/icon"));

    setWindowTitle(tr("Help") + " # " + qApp->applicationName());

    QTabWidget *tabs = new QTabWidget;
    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(tabs);
    setLayout(l);
    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);

    QWidget *usageTab = new QWidget;
    QScrollArea *saUsage = new QScrollArea;
    saUsage->setWidget(usageTab);
    saUsage->setWidgetResizable(true);
    QWidget *hotkeyTab = new QWidget;
    QScrollArea *saHotkey = new QScrollArea;
    saHotkey->setWidget(hotkeyTab);
    saHotkey->setWidgetResizable(true);

    /* From author tab */
    QLabel *authorLabel = new QLabel(tr("<center><b>From the author</b></center> Why is the default directory selected for music? Nowadays, "
                                        "most people use such programs specifically for music, if you are not comfortable - you can change "
                                        "the path in the settings.<br>At the moment, errors are known:<br><ol>"
                                        "<li>Due to an imperfect algorithm for parsing the metadata of media "
                                        "files, the path to the file may be displayed in the playlist instead of the name of the music. "
                                        "The behavior is random, and work is being done to eliminate it. It does not affect the performance."
                                        "You can start force update metadata by clicking on button on playlist control panel."
                                        "</li>"
                                        "<li><b>Couldn't open the file. </b>The player does not provide additional multimedia codecs, but "
                                        "uses the ones installed in the system. You can solve the problem by installing them. For example, "
                                        "for Linux it is <b>GStreamer</b>, for Windows - <b>K-Lite Codec Pack</b>. Codecs can be found freely "
                                        "available on the Internet. Which codec to choose is up to you.</li></ol>"));
    authorLabel->setWordWrap(true);
    authorLabel->setAlignment(Qt::AlignJustify);
    authorLabel->setStyleSheet("QLabel {margin: 5px 5px 5px 5px;}");
    QScrollArea *saAuthor = new QScrollArea;
    saAuthor->setWidget(authorLabel);
    saAuthor->setWidgetResizable(true);

    tabs->addTab(saUsage, tr("Usage"));
    tabs->addTab(saHotkey, tr("Hotkeys"));
    tabs->addTab(saAuthor, tr("From author"));

    /* usage tab */
    QVBoxLayout *usageLayout = new QVBoxLayout;
    usageTab->setLayout(usageLayout);
    QLabel *playlistLabel = new QLabel(tr("<center>Playlists</center><br>The application can save and load user-created playlists by "
                                          "clicking on the corresponding playlist control buttons.<br>Playlists are in the *.cpl "
                                          "(Caligo playlist) format and are simple plain text files containing paths to multimedia "
                                          "files. <b>Not recommended </b> to manually change the playlist in a text editor without "
                                          "understanding the process.<br>List format: <b>The first line is required</b> for the application "
                                          "to recognize the playlist, then contains the file paths, each in its own line. It is possible "
                                          "to add comments, for this you need to put the <b>#</b> character at the beginning of the line, so "
                                          "that the application ignores this line when reading and proceeds to the next one.<br>"));
    playlistLabel->setWordWrap(true);
    playlistLabel->setAlignment(Qt::AlignJustify);
    QLabel *pathLabel = new QLabel(tr("<center>Path Settings</center><br>In the settings, you can specify the paths for storing multimedia "
                                      "files and playlists.<br><b>Music location</b> - the path that will open by default when you click "
                                      "on the button to add multimedia files to the playlist. By default, in Windows, this is the My Music "
                                      "folder, on Linux - /home/user/music. The name of the directories may differ depending on your OS, "
                                      "the directory corresponds to the standard location of music in the OS.<br><b>Playlist Location</b> "
                                      "- The path for storing playlists *. cpl. By default, this is the playlists directory located in the"
                                      " application directory. You can change the directory if necessary.<br>The open media files button "
                                      "is able to recognize the *.cpl playlist, but the functions were intentionally separated, since music"
                                      " and playlists can be stored in different directories.<br>"));
    pathLabel->setWordWrap(true);
    pathLabel->setAlignment(Qt::AlignJustify);
    QLabel *dragLabel = new QLabel(tr("<center>Drag and Drop</center><br>The app supports Drag and Drop functionality. To add media files "
                                      "or playlists *. cpl, simply drag the files and / or folders with them from the file manager to the "
                                      "application window. The player will automatically filter out files that are not multimedia and simply "
                                      "ignore them. Errors can occur when transferring files with a non-binary extension (for example, a "
                                      "text file with the *.mp3 extension) or a corrupted playlist to the player.<br>"));
    dragLabel->setWordWrap(true);
    dragLabel->setAlignment(Qt::AlignJustify);
    QLabel *videoLabel = new QLabel(tr("<center>Video playback</center><br>At the moment, the function works, but it is in the testing phase. "
                                       "The transition to full-screen mode can be performed by double-clicking the LMB on the video, the "
                                       "corresponding control button or a hotkey. If the next item in the playlist is not a video, it will "
                                       "automatically exit the full-screen mode.<br>"));
    videoLabel->setWordWrap(true);
    videoLabel->setAlignment(Qt::AlignJustify);

    usageLayout->addWidget(playlistLabel, 0);
    usageLayout->addWidget(pathLabel, 0);
    usageLayout->addWidget(dragLabel, 0);
    usageLayout->addWidget(videoLabel, 0);
    usageLayout->addStretch(1);

    /* hotkey tab */
    QVBoxLayout *hotkeyLayout = new QVBoxLayout;
    hotkeyTab->setLayout(hotkeyLayout);

    QLabel *hkcl = new QLabel("<center><b>" + tr("Controls") + "</b></center>");
    hotkeyLayout->addWidget(hkcl);
    QFrame *hkControls = new QFrame;
    hkControls->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    hotkeyLayout->addWidget(hkControls);

    QLabel *hkpl = new QLabel("<center><b>" + tr("Playlist") + "</b></center>");
    hotkeyLayout->addWidget(hkpl);
    QFrame *hkPlaylist = new QFrame;
    hkPlaylist->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    hotkeyLayout->addWidget(hkPlaylist);

    QLabel *hkol = new QLabel("<center><b>" + tr("Other") + "</b></center>");
    hotkeyLayout->addWidget(hkol);
    QFrame *hkOther = new QFrame;
    hkOther->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    hotkeyLayout->addWidget(hkOther);
    hotkeyLayout->addStretch(1);

    QGridLayout *controlsGrid = new QGridLayout;
    hkControls->setLayout(controlsGrid);
    QLabel *toggleFSkey = new QLabel("F");
    QLabel *toggleFSdes = new QLabel(tr("Toggle full screen mode (video only)"));
    controlsGrid->addWidget(toggleFSkey, 0, 0);
    controlsGrid->addWidget(toggleFSdes, 0, 1);
    QLabel *exitFSkey = new QLabel("Esc");
    QLabel *exitFSdes = new QLabel(tr("Exit full screen mode (video only)"));
    controlsGrid->addWidget(exitFSkey, 1, 0);
    controlsGrid->addWidget(exitFSdes, 1, 1);
    QLabel *nextKey = new QLabel("N");
    QLabel *nextDes = new QLabel(tr("Next track"));
    controlsGrid->addWidget(nextKey, 2, 0);
    controlsGrid->addWidget(nextDes, 2, 1);
    QLabel *prevKey = new QLabel("B");
    QLabel *prevDes = new QLabel(tr("Previous track"));
    controlsGrid->addWidget(prevKey, 3, 0);
    controlsGrid->addWidget(prevDes, 3, 1);
    QLabel *muteKey = new QLabel("Ctrl+M");
    QLabel *muteDes = new QLabel(tr("Mute"));
    controlsGrid->addWidget(muteKey, 4, 0);
    controlsGrid->addWidget(muteDes, 4, 1);
    QLabel *stopKey = new QLabel("S");
    QLabel *stopDes = new QLabel(tr("Stop playing"));
    controlsGrid->addWidget(stopKey, 5, 0);
    controlsGrid->addWidget(stopDes, 5, 1);
    QLabel *playKey = new QLabel("P");
    QLabel *playDes = new QLabel(tr("Play / Pause"));
    controlsGrid->addWidget(playKey, 6, 0);
    controlsGrid->addWidget(playDes, 6, 1);
    QLabel *plusKey = new QLabel("Num+");
    QLabel *plusDes = new QLabel(tr("Increase volume"));
    controlsGrid->addWidget(plusKey, 7, 0);
    controlsGrid->addWidget(plusDes, 7, 1);
    QLabel *minKey = new QLabel("Num-");
    QLabel *minDes = new QLabel(tr("Decrease volume"));
    controlsGrid->addWidget(minKey, 8, 0);
    controlsGrid->addWidget(minDes, 8, 1);

    QGridLayout *playlistGrid = new QGridLayout;
    hkPlaylist->setLayout(playlistGrid);
    QLabel *openMusKey = new QLabel("Ctrl+O");
    QLabel *openMusDes = new QLabel(tr("Open music"));
    playlistGrid->addWidget(openMusKey, 0, 0);
    playlistGrid->addWidget(openMusDes, 0, 1);
    QLabel *urlKey = new QLabel("Ctrl+U");
    QLabel *urlDes = new QLabel(tr("Open URL"));
    playlistGrid->addWidget(urlKey, 1, 0);
    playlistGrid->addWidget(urlDes, 1, 1);
    QLabel *openPlaKey = new QLabel("Shift+O");
    QLabel *openPlaDes = new QLabel(tr("Open playlist"));
    playlistGrid->addWidget(openPlaKey, 2, 0);
    playlistGrid->addWidget(openPlaDes, 2, 1);
    QLabel *saveKey = new QLabel("Ctrl+Shift+S");
    QLabel *saveDes = new QLabel(tr("Save playlist"));
    playlistGrid->addWidget(saveKey, 3, 0);
    playlistGrid->addWidget(saveDes, 3, 1);
    QLabel *clearKey = new QLabel("Ctrl+Shift+C");
    QLabel *clearDes = new QLabel(tr("Clear playlist"));
    playlistGrid->addWidget(clearKey, 4, 0);
    playlistGrid->addWidget(clearDes, 4, 1);
    QLabel *forceKey = new QLabel("Shift+U");
    QLabel *forceDes = new QLabel(tr("Update playlist metadata"));
    playlistGrid->addWidget(forceKey, 5, 0);
    playlistGrid->addWidget(forceDes, 5, 1);

    QGridLayout *otherGrid = new QGridLayout;
    hkOther->setLayout(otherGrid);
    QLabel *helpKey = new QLabel("Ctrl+H");
    QLabel *helpDes = new QLabel(tr("Open this window"));
    otherGrid->addWidget(helpKey, 0, 0);
    otherGrid->addWidget(helpDes, 0, 1);
}

void HelpWindow::openGitHub()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Alex13kyky/Caligo"));
}
