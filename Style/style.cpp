#ifndef STYLE_CPP
#define STYLE_CPP

#include <QString>

namespace style {

namespace me {

static QString none = "";
static QString playing = "* {"
                         "background-color: #B0D0F7;"
                         "color: #000000;"
                         "}";
static QString selected = "* {"
                          "background-color: #8AA4C7;"
                          "color: #000000;"
                          "}";
static QString all = "* {"
                     "background-color: #11386F;"
                     "color: #FFFFFF;"
                     "}";

} // namespace me

namespace theme {

static QString light = "QPushButton:hover {"
                       "background-color: #B0D0F7;"
                       "}"
                       "QSplitter::handle {"
                       "background-color: #DDDDDD;"
                       "}"
                       "QSplitter::handle:hover {"
                       "background-color: #B0D0F7;"
                       "}";
static QString dark = "* {"
                      "background-color: #454545;"
                      "color: #FFFFFF;"
                      "}"
                      "QPushButton:hover {"
                      "background-color: #B0D0F7;"
                      "}"
                      "QSplitter::handle {"
                      "background-color: #656565;"
                      "}"
                      "QSplitter::handle:hover {"
                      "background-color: #B0D0F7;"
                      "}";

} // namespace theme

} // namespace style

#endif // STYLE_CPP
