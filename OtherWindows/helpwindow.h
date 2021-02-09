#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QtWidgets>

class HelpWindow : public QWidget
{
    Q_OBJECT
public:
    HelpWindow();

private slots:
    void openGitHub();
    void openArtStation();
};

#endif // HELPWINDOW_H
