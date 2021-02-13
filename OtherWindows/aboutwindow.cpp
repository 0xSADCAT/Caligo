#include "aboutwindow.h"

AboutWindow::AboutWindow() : QWidget(nullptr)
{
    setWindowIcon(QIcon(":/img/icon"));

    bgImg = new QLabel;
    bgImg->setPixmap(QPixmap(":/img/aboutImage").scaledToWidth(qApp->desktop()->width() / 10));
    bgImg->setFixedWidth(qApp->desktop()->width() / 10);

    link = "https://github.com/Alex13kyky/Caligo";
    samLink = "https://www.artstation.com/twinshado";

    setWindowTitle(tr("About application") + " # " + qApp->applicationName());

    title = new QLabel;
    mainLabel = new QLabel;
    mainLabel->setWordWrap(true);
    gitHubLinkLabel = new QLabel;
    gitHubLinkLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    openInBrowser = new QPushButton(tr("GitHub"));
    openInBrowser->setToolTip(tr("Open in browser"));
    closeButton = new QPushButton(tr("Close"));
    closeButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    contactsLabel = new QLabel;
    contactsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    thanksLabel = new QLabel;
    samButton = new QPushButton(tr("ArtStation"));
    samButton->setToolTip(tr("Open in browser"));

    QHBoxLayout *hl = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;

    QHBoxLayout *gl = new QHBoxLayout;
    gl->addWidget(gitHubLinkLabel, 1);
    gl->addWidget(openInBrowser, 0);
    gl->setSpacing(0);
    gl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *cl = new QHBoxLayout;
    cl->addStretch(1);
    cl->addWidget(closeButton, 0);
    cl->setSpacing(0);
    cl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *samL = new QHBoxLayout;
    QLabel *samLabel = new QLabel;
    samLabel->setText("<b>SAM Art</b> " + tr("for art in this window") + "<br>ArtStation: " +
                      "<a href='" + samLink + "'>" + samLink + "</a>");
    samLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    samL->addWidget(samLabel, 1);
    samL->addWidget(samButton, 0);

    l->addWidget(title, 0);
    l->addWidget(mainLabel, 0);
    l->addStretch(1);
    l->addWidget(thanksLabel, 0);
    l->addLayout(samL, 0);
    l->addStretch(1);
    l->addLayout(gl, 0);
    l->addWidget(contactsLabel, 0);
    l->addLayout(cl, 0);

    hl->addWidget(bgImg, 0);
    hl->addLayout(l, 0);
    setLayout(hl);

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

    thanksLabel->setText(tr("<center><b><h4>Special thanks</h4></b></center>"));

    connect(openInBrowser, &QPushButton::clicked, this, &AboutWindow::oib);
    connect(closeButton, &QPushButton::clicked, this, &AboutWindow::clw);
    connect(samButton, &QPushButton::clicked, this, &AboutWindow::sam);
}

void AboutWindow::oib()
{
    QDesktopServices::openUrl(link);
}

void AboutWindow::clw()
{
    this->close();
}

void AboutWindow::sam()
{
    QDesktopServices::openUrl(samLink);
}
