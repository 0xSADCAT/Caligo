/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <localsocket.h>

#include <QApplication>
#include <QString>
#include <QDebug>

#include <iostream>

int main(int argc, char *argv[])
{
    std::string ver = "1.2.1";

    if (argc > 1) {
        if (QString(argv[1]) == "--version") {
            std::cout << "Caligo version " + ver << std::endl;
            return 0;
        } else if (QString(argv[1]) == "--help") {
            std::cout << "Caligo - opensource multimedia player. Source code:\n"
                         "https://github.com/0xSADCAT/Caligo" << std::endl;
            return 0;
        }
    }

    QApplication q_app(argc, argv);

    q_app.setApplicationName("Caligo");
    q_app.setApplicationVersion(QString::fromStdString(ver));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

#ifdef Q_OS_WINDOWS
    a.setStyle("Fusion");
#endif

    QTranslator app_translator;
    app_translator.load(QString(":/tr/" + q_app.applicationName() + "_") + QLocale::system().name());
    q_app.installTranslator(&app_translator);

    QTranslator qt_translator;
    qt_translator.load(QString(":/tr/qt_") + QLocale::system().name());
    q_app.installTranslator(&qt_translator);

    QTranslator qt_base_translator;
    qt_base_translator.load(QString(":/tr/qtbase_") + QLocale::system().name());
    q_app.installTranslator(&qt_base_translator);

    QTranslator qt_help_translator;
    qt_help_translator.load(QString(":/tr/qt_help_") + QLocale::system().name());
    q_app.installTranslator(&qt_help_translator);

    QTranslator qt_location_translator;
    qt_location_translator.load(QString(":/tr/qtlocation_") + QLocale::system().name());
    q_app.installTranslator(&qt_location_translator);

    Application application;

    return q_app.exec();
}
