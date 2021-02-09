#include "widget.h"

#include <QApplication>

/* It works, but:
 *
 * On exit (Widget->closeEvent->[qApp->exit(0)]) throws 139 error code. I don't know why.
 *
 * Warning:
 *      QWidget::paintEngine: Should no longer be called
 * After implementing full-screen mode in Widget.
 * I don't know where it was, but all works currectly.
 * */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Caligo");
    a.setApplicationVersion("0.1");

#ifdef Q_OS_WINDOWS
    a.setStyle("Fusion");
#endif

    QTranslator t1;
    t1.load(QString(":/tr/qt_") + QLocale::system().name());
    a.installTranslator(&t1);

    QTranslator t2;
    t2.load(QString(":/tr/qtbase_") + QLocale::system().name());
    a.installTranslator(&t2);

    QTranslator t0;
    t0.load(QString(":/tr/" + a.applicationName() + "_") + QLocale::system().name());
    a.installTranslator(&t0);

    Widget w;
    w.show();
    return a.exec();
}
