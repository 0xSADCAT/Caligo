/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef STYLE_CPP
#define STYLE_CPP

#include <QString>

namespace style {

  /// MediaElement style
  namespace me {

    static QString none = "* {"
                          "margin-right: 5px;"
                          "}";
    static QString playing = "* {"
                             "border: 2px solid #DDDDDD;"
                             "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #D7EBF4, stop:1 #A4D0F4);"
                             "color: #000000;"
                             "margin-right: 5px;"
                             "}";
    static QString selected = "* {"
                              "background-color: #11386F;"
                              "color: #FFFFFF;"
                              "margin-right: 5px;"
                              "}";
    static QString all = "* {"
                         "background-color: #11386F;"
                         "color: #FFFFFF;"
                         "border: 2px solid #000000"
                         "margin-right: 5px;"
                         "}";

  } // namespace me

  /// LibraryElement style
  namespace le {

    static QString none = "";
    static QString selected = "* {"
                              "background-color: #11386F;"
                              "color: #FFFFFF;"
                              "}";

  } // namespace le

  /// Application theme
  namespace theme {

    static QString light = "* {"
                           "color: #000000;"
                           "}"
                           "#AlphaBG {"
                           "background-color: rgba(230, 230, 230, 150);"
                           "border-radius: 5px;"
                           "margin-left: 3px;"
                           "}"
                           "#FullAlpha {"
                           "background-color: rgba(230, 230, 230, 0);"
                           "}"
                           "QToolTip {"
                           "background-color: #EEEEEE;"
                           "}"
                           "QLineEdit {"
                           "background-color: #FEFEFE;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: #B0D0F7;"
                           "}"
                           "QSplitter::handle:hover {"
                           "background-color: #B0D0F7;"
                           "}"
                           "QPushButton {"
                           "background-color: #EFEFEF;"
                           "border: 1px solid black;"
                           "padding: 5px 5px 5px 5px;"
                           "border-radius: 5px;"
                           "}";

  } // namespace theme

} // namespace style

#endif // STYLE_CPP
