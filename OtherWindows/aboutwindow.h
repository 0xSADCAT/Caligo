#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets>

class AboutWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWindow();

private:
    QLabel *bgImg;

    QLabel *title;

    QLabel *mainLabel;

    QLabel *thanksLabel;
    QPushButton *samButton;

    QLabel *gitHubLinkLabel;

    QLabel *contactsLabel;

    QPushButton *openInBrowser;
    QPushButton *closeButton;

    QString link;
    QString samLink;

private slots:
    void oib();
    void clw();
    void sam();
};

#endif // ABOUTWINDOW_H
