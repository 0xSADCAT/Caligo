/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "radiolibrary.h"

RadioLibrary::RadioLibrary(Playlist *pls, QWidget *parent) : QWidget(parent)
{
    playlist = pls;
    radioPath = qApp->applicationDirPath() + QDir::separator() + "radio";
    mainLayout = new QVBoxLayout;
    lastClicked = nullptr;
    listWidget = new QListWidget;
    listWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    QHBoxLayout *header = new QHBoxLayout;
    QHBoxLayout *buttons = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    l->addLayout(header, 0);
    QScrollArea *sa = new QScrollArea;
    QWidget *w = new QWidget;
    QVBoxLayout *sal = new QVBoxLayout;
    sal->addLayout(mainLayout, 0);
    sal->addStretch(1);
    w->setLayout(sal);
    sa->setWidget(w);
    sa->setWidgetResizable(true);
    l->addWidget(sa, 1);

    header->addWidget(new QLabel(tr("Radio URL")), 0);
    header->addStretch(1);
    header->addWidget(new QLabel(tr("Radio name")), 0);
    header->addSpacing(10);

    QPushButton *scanDirButton = new QPushButton("");
    scanDirButton->setIcon(QIcon(":/img/scan"));
    scanDirButton->setToolTip(tr("Search radio lists"));
    connect(scanDirButton, &QPushButton::clicked, this, &RadioLibrary::scanLibrary);

    buttons->addSpacing(10);
    buttons->addStretch(1);
    buttons->addWidget(scanDirButton, 0);

    QHBoxLayout *ml = new QHBoxLayout;
    ml->addWidget(listWidget, 0);
    ml->addLayout(l, 1);

    QVBoxLayout *tabLayout = new QVBoxLayout;
    tabLayout->addLayout(buttons, 0);
    tabLayout->addSpacing(5);
    tabLayout->addLayout(ml, 1);
    setLayout(tabLayout);

    connect(listWidget, &QListWidget::itemClicked, this, &RadioLibrary::itemClicked);
}

void RadioLibrary::clear()
{
    foreach (RadioElement *e, list) {
        mainLayout->removeWidget(e);
        list.removeAll(e);
        e->~RadioElement();
    }
    selection.clear();
    lastClicked = nullptr;
}

void RadioLibrary::remove(RadioElement *e)
{
    mainLayout->removeWidget(e);
    list.removeAll(e);
    e->~RadioElement();

    selection.removeAll(e);
    if (lastClicked == e) {
        if (not selection.isEmpty()) {
            lastClicked = selection.back();
        }
        else {
            lastClicked = nullptr;
        }
    }
}

void RadioLibrary::remove(int index)
{
    if (list.count() - 1 > index)
        return;

    remove(list[index]);
}

void RadioLibrary::add(QString url, QString name)
{
    if (name.isEmpty())
        name = " ";

    RadioElement *e = new RadioElement(url, name);
    list << e;
    mainLayout->addWidget(e, 0);

    connect(e, &RadioElement::clicked, this, &RadioLibrary::elementClicked);
    connect(e, &RadioElement::doubleClicked, this, &RadioLibrary::elementDouble);
    connect(e, &RadioElement::ctrlClicked, this, &RadioLibrary::elementCtrl);
    connect(e, &RadioElement::shiftClicked, this, &RadioLibrary::elementShift);
    connect(e, &RadioElement::focus, this, &RadioLibrary::elementFocus);
}

QString RadioLibrary::getRadioPath() const
{
    return radioPath;
}

void RadioLibrary::setRadioPath(const QString &value)
{
    radioPath = value;
    scanLibrary();
}

void RadioLibrary::save(const QString &fileName)
{
    // InDev
    /* Hide warning */
    fileName.size();
}

void RadioLibrary::scanDir(QDir d)
{
    QApplication::processEvents();

    QStringList fl = d.entryList(QDir::Files);
    foreach (QString file, fl) {
        if (file.endsWith(".crl"))
            files << d.absoluteFilePath(file);
    }

    QStringList dirs = d.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QString dir, dirs) {
        scanDir(QDir(d.absoluteFilePath(dir)));
    }
}

void RadioLibrary::elementClicked()
{
    foreach (RadioElement *re, selection) {
        re->setSelected(false);
    }
    selection.clear();
    RadioElement *e = (RadioElement*) sender();
    selection << e;
    lastClicked = e;
    e->setSelected(true);
}

void RadioLibrary::elementDouble()
{
    RadioElement *e = (RadioElement*) sender();
    playlist->add(e->getUrl(), "[Radio] " + e->getName());

    lastClicked = e;
}

void RadioLibrary::elementCtrl()
{
    lastClicked = (RadioElement*) sender();
    if (selection.contains(lastClicked)) {
        lastClicked->setSelected(false);
        selection.removeAll(lastClicked);
        return;
    }
    else {
        selection << lastClicked;
        lastClicked->setSelected(true);
    }
}

void RadioLibrary::elementShift()
{
    if (list.count() < 2)
        return;

    RadioElement *from = lastClicked;
    if (from == nullptr) {
        from = lastClicked;
        if (from == nullptr) {
            return;
        }
    }

    lastClicked = (RadioElement*) sender();

    int iFrom = list.indexOf(from);
    int iTo = list.indexOf(lastClicked);

    if (iFrom == iTo)
        return;

    // XOR swap
    if (iFrom > iTo) {
        iFrom ^= iTo;
        iTo ^= iFrom;
        iFrom ^= iTo;
    }

    for (int i = iFrom; i <= iTo; ++i) {
        if (not selection.contains(list[i])) {
            selection << list[i];
            list[i]->setSelected(true);
        }
    }
}

void RadioLibrary::elementFocus()
{
    this->setFocus();
}

void RadioLibrary::setLibraryPath()
{
    QString str = QFileDialog::getExistingDirectory(0, tr("Select directory") + " # " + qApp->applicationName(), QDir::home().absolutePath());
    if (str.isEmpty())
        return;
    radioPath = str;
}

void RadioLibrary::scanLibrary()
{
    if (radioPath.isEmpty()) {
        setLibraryPath();
    }

    listWidget->clear();

    scanDir(QDir(radioPath));

    if (files.isEmpty())
        return;

    QString tmp;
    foreach (QString file, files) {
        QFileInfo fi(file);
        tmp = fi.fileName();
        tmp.remove(".crl");
        listWidget->addItem(tmp);
    }

    files.clear();
}

void RadioLibrary::itemClicked(QListWidgetItem *item)
{
    clear();
    QFile file(radioPath + QDir::separator() + item->text() + ".crl");

    QStringList li;
    if (file.open(QIODevice::ReadOnly)) {
        while (not file.atEnd()) {
            li << file.readLine();
        }
    }

    if (li.isEmpty())
        return;

    foreach (QString line, li) {
        line.remove("\n");
        if (line.isEmpty() or line.startsWith("#"))
            return;

        QStringList tmp = line.split(" ## ");
        if (tmp.count() == 1) {
            add(tmp[0]);
        }
        else {
            add(tmp[0], tmp[1]);
        }
    }

    file.close();
}
