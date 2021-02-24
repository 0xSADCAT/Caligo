/* This file is path of the Caligo multimedia player
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef STYLE_CPP
#define STYLE_CPP

#include <QString>

namespace style {

// MediaElement style
namespace me {

static QString none = "";
static QString playing = "* {"
                         "border: 2px solid #DDDDDD;"
                         "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #D7EBF4, stop:1 #A4D0F4);"
                         "color: #000000;"
                         "}";
static QString selected = "* {"
                          "background-color: #11386F;"
                          "color: #FFFFFF;"
                          "}";
static QString all = "* {"
                     "background-color: #11386F;"
                     "color: #FFFFFF;"
                     "border: 2px solid #000000"
                     "}";

} // namespace me

// LibraryElement style
namespace le {

static QString none = "";
static QString selected = "* {"
                          "background-color: #11386F;"
                          "color: #FFFFFF;"
                          "}";

} // namespace le

// RadioElement style
namespace re {

static QString none = "";
static QString selected = "* {"
                          "background-color: #11386F;"
                          "color: #FFFFFF;"
                          "}";

} // namespace re

// Application theme
namespace theme {

static QString light = "* {"
                            "background-color: #F7F7F7;"
                            "color: #000000;"
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
