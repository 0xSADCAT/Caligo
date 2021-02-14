#ifndef STYLE_CPP
#define STYLE_CPP

#include <QString>

namespace style {

// MediaElement style
// me  -->  MediaElement
namespace me {
// #B0D0F7
static QString none = "";
static QString playing = "* {"
                         "background-color: rgba(150, 200, 255, 150);"
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

// Application theme
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
                            "background-color: #505050;"
                            "color: #FFFFFF;"
                      "}"
                      "QPushButton:hover {"
                            "background-color: #2F4165;"
                      "}"
                      "QMenu::item:selected {"
                            "background-color: #2F4165;"
                      "}"
                      "QSplitter::handle {"
                            "background-color: #656565;"
                      "}"
                      "QSplitter::handle:hover {"
                            "background-color: #2F4165;"
                      "}";

} // namespace theme

} // namespace style

#endif // STYLE_CPP
