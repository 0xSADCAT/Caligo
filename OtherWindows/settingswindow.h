#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtWidgets>

#include <Widgets/playlistcontrols.h>
#include <Style/style.cpp>

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QSettings *s, PlaylistControls *pc);

private:
    QSettings *settings;
    PlaylistControls *listControls;

    void setState();

    QVBoxLayout *l;

    QLabel *pathMusicLabel;
    QLabel *pathMusicValue;
    QPushButton *setPathMusicButton;
    QPushButton *setDefaultPathMusicButton;

    QLabel *pathListLabel;
    QLabel *pathListValue;
    QPushButton *setPathListButton;
    QPushButton *setDefaultPathListButton;

    QCheckBox *clearBeforeOpenPlaylistCheck;

    QCheckBox *loadOldCheck;

    QCheckBox *darkThemeCheck;

private slots:
    void pathMusic();
    void pathMusicDefault();

    void pathList();
    void pathListDefault();

    void clearBeforeOpen(bool v);

    void loadOld(bool v);

    void darkTheme(bool v);
};

#endif // SETTINGSWINDOW_H
