#include "aboutwindow.h"

AboutWindow::AboutWindow() : QWidget(nullptr)
{
    setWindowIcon(QIcon(":/img/icon"));

    link = "https://github.com/Alex13kyky/Caligo";

    setWindowTitle(tr("About application") + " # " + qApp->applicationName());

    title = new QLabel;
    mainLabel = new QLabel;
    mainLabel->setWordWrap(true);
    gitHubLinkLabel = new QLabel;
    gitHubLinkLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    openInBrowser = new QPushButton(tr("GitHub"));
    openInBrowser->setIcon(QIcon(":/img/github"));
    openInBrowser->setToolTip(tr("Open in browser"));
    setStyleSheet("QPushButton {border: 1px solid black;}");
    contactsLabel = new QLabel;
    contactsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QHBoxLayout *hl = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;

    QHBoxLayout *gl = new QHBoxLayout;
    gl->addWidget(gitHubLinkLabel, 1);
    gl->addWidget(openInBrowser, 0);
    gl->setSpacing(0);
    gl->setContentsMargins(0, 0, 0, 0);

    QPushButton *aboutQtButton = new QPushButton(tr("About Qt"));
    aboutQtButton->setIcon(QIcon(":/img/qt"));
    connect(aboutQtButton, &QPushButton::clicked, qApp, &QApplication::aboutQt);
    aboutQtButton->setStyleSheet("QPushButton {padding: 10px 10px 10px 10px; border: 1px solid black;}");

    QHBoxLayout *cl = new QHBoxLayout;
    cl->addStretch(1);
    cl->addWidget(aboutQtButton, 0);
    cl->addStretch(1);
    cl->setSpacing(0);
    cl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *samL = new QHBoxLayout;
    QLabel *samLabel = new QLabel;
    samLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    samL->addWidget(samLabel, 1);

    l->addWidget(title, 0);
    l->addWidget(mainLabel, 0);
    l->addStretch(1);
    l->addLayout(samL, 0);
    l->addStretch(1);
    l->addLayout(gl, 0);
    l->addWidget(contactsLabel, 0);
    l->addLayout(cl, 0);

    hl->addLayout(l, 0);
    QScrollArea *sa = new QScrollArea;
    QWidget *w = new QWidget;
    w->setLayout(hl);
    sa->setWidget(w);
    sa->setWidgetResizable(true);
    QVBoxLayout *la = new QVBoxLayout;
    la->addWidget(sa);
    setLayout(la);

    title->setText(
                "<center><h3>" + qApp->applicationName() + " version " + qApp->applicationVersion() +
                "</h3><br><h4>" + tr("About application") + "</h4></center>"
                );

    gitHubLinkLabel->setText(tr("Source code") + ": <a href='" + link + "'>" + link + "</a>");

    contactsLabel->setText(
                tr("Contacts") + ":<br>"
                                 "Email: alexsaltykow@gmail.com"
                );

    mainLabel->setText(
                tr("<b>Caligo</b> - is an open source multimedia player.<br>"
                "At the moment, testing is taking place on Linux and Windows, no testing has been conducted on OSX, "
                "iOS and Android are not currently supported. The source code is available at the link below.<br>"
                "The idea of the application is to implement the minimum - necessary components of a multimedia player with "
                "an emphasis on performance.<br>"
                "Help in using it is available in the corresponding menu.<br>"
                "Development is currently being conducted by one person, some functions have not yet been implemented. "
                "Development assistance would be welcome.<br>")
                );
    mainLabel->setAlignment(Qt::AlignJustify);

    connect(openInBrowser, &QPushButton::clicked, this, &AboutWindow::oib);
}

void AboutWindow::oib()
{
    QDesktopServices::openUrl(link);
}
