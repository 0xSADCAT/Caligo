#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets>

class AboutWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWindow();

private:
    QLabel *title;

    QLabel *mainLabel;

    QLabel *gitHubLinkLabel;

    QLabel *contactsLabel;

    QPushButton *openInBrowser;

    QString link;

private slots:
    void oib();
};

#endif // ABOUTWINDOW_H
