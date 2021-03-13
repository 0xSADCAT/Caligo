/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <widget.h>

#include <QApplication>
#include <QString>
#include <QDebug>

#include <iostream>

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
  std::string ver = "1.0.0";

  if (argc > 1) {
      if (QString(argv[1]) == "--version") {
          std::cout << "Caligo version " + ver << std::endl;
          return 0;
        }
      if (QString(argv[1]) == "--help") {
          std::cout << "Caligo - opensource multimedia player. Source code:\n"
                       "https://github.com/Alex13kyky/Caligo" << std::endl;
          return 0;
        }
    }

  QApplication a(argc, argv);

  a.setApplicationName("Caligo");
  a.setApplicationVersion(QString::fromStdString(ver));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

#ifdef DEBUG_OUTPUT
  qDebug() << a.applicationName() << a.applicationVersion() << "debug version.";
#endif

#ifdef Q_OS_WINDOWS
  a.setStyle("Fusion");
#endif

  QTranslator t1;
  t1.load(QString(":/tr/qt_") + QLocale::system().name());
  a.installTranslator(&t1);

  QTranslator t2;
  t2.load(QString(":/tr/qtbase_") + QLocale::system().name());
  a.installTranslator(&t2);

  QTranslator t3;
  t3.load(QString(":/tr/qt_help_") + QLocale::system().name());
  a.installTranslator(&t3);

  QTranslator t4;
  t4.load(QString(":/tr/qtlocation_") + QLocale::system().name());
  a.installTranslator(&t4);

  QTranslator t0;
  t0.load(QString(":/tr/" + a.applicationName() + "_") + QLocale::system().name());
  a.installTranslator(&t0);

  Widget w;
  w.show();
  return a.exec();
}
