#ifndef STYLE_CPP
#define STYLE_CPP

#include <QString>

namespace style {

// MediaElement style
// me  -->  MediaElement
namespace me {

static QString none = "";
static QString playing = "* {"
                         "border: 2px solid #7F7F7F;"
                         "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #DDDDDD, stop:1 #AAAAAA);"
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

// Application theme
namespace theme {

static QString light = "QPushButton:hover {"
                            "background-color: #B0D0F7;"
                       "}"
                            "QSplitter::handle:hover {"
                            "background-color: #B0D0F7;"
                       "}"
                       "QPushButton {"
                            "border: none;"
                            "padding: 5px 5px 5px 5px;"
                            "border-radius: 5px;"
                       "}";

static QString dark = "* {"
                            "background-color: #606060;"
                            "color: #FFFFFF;"
                      "}"
                      "QPushButton {"
                            "border: none;"
                            "padding: 5px 5px 5px 5px;"
                            "border-radius: 5px;"
                      "}"
                      "QPushButton:hover {"
                            "background-color: #959595;"
                      "}"
                      "QMenu::item:selected {"
                            "background-color: #959595;"
                      "}"
                      "QSplitter::handle {"
                            "background-color: #656565;"
                      "}"
                      "QSplitter::handle:hover {"
                            "background-color: #959595;"
                      "}";

} // namespace theme

} // namespace style

#endif // STYLE_CPP
