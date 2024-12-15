#include "ThemeManager.h"

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent), currentTheme_(Theme::Light) {}

void ThemeManager::setTheme(ThemeManager::Theme theme) {
    currentTheme_ = theme;
}
ThemeManager::Theme ThemeManager::currentTheme() const {
    return currentTheme_;
}

QString ThemeManager::styleSheetForMainWindow() const {
    if (currentTheme_ == Dark) {
        return "background-color: #1e1e1e; color: white;";
    } else {
        return "background-color: #f3f3f3; color: black;";
    }
}

QString ThemeManager::styleSheetForTable() const {
    if (currentTheme_ == Dark) {
        return "QTableWidget {"
               "    gridline-color: #4a4a4a;"
               "    color: white;"
               "    background-color: #2d2d2d;"
               "}"
               "QHeaderView::section {"
               "    background-color: #3c3c3c;"
               "    color: white;"
               "    border: 1px solid #4a4a4a;"
               "}"
               "QTableWidget::item:selected {"
               "    background-color: #454545;"
               "    color: white;"
               "}";
    } else {
        return "QTableWidget {"
               "    gridline-color: #d0d0d0;"
               "    color: black;"
               "    background-color: #fefefe;"
               "}"
               "QHeaderView::section {"
               "    background-color: #f6f6f6;"
               "    color: black;"
               "    border: 1px solid #d0d0d0;"
               "}"
               "QTableWidget::item:selected {"
               "    background-color: #d6d6d6;"
               "    color: black;"
               "}";
    }
}
QString ThemeManager::styleSheetForButtons() const {
    if (currentTheme_ == Dark) {
        return "QPushButton {"
               "    background-color: #3c3c3c;"
               "    color: white;"
               "    border: 1px solid #4a4a4a;"
               "    padding: 5px;"
               "}"
               "QPushButton:hover {"
               "    background-color: #505050;"
               "}";
    } else {
        return "QPushButton {"
               "    background-color: #fbfbfb;"
               "    color: black;"
               "    border: 1px solid #efefef;"
               "    padding: 5px;"
               "}"
               "QPushButton:hover {"
               "    background-color: #eaeaea;"
               "}";
    }
}

QString ThemeManager::styleSheetForMenuBar() const {
    if (currentTheme_ == Dark) {
        return "QMenuBar {"
               "    background-color: #1e1e1e;"
               "    color: white;"
               "}"
               "QMenuBar::item {"
               "    background-color: transparent;"
               "    color: white;"
               "}"
               "QMenuBar::item:selected {"
               "    background-color: #2b2b2b;"
               "}"
               "QMenu::item:selected {"
               "    background-color: #2b2b2b;"
               "    color: white;"
               "}"
               "QMenu {"
               "    background-color: #0f0f0f;"
               "    color: white;"
               "    border: 0.5px solid #171717;"
               "}";
    } else {
        return "QMenuBar {"
               "    background-color: #f3f3f3;"
               "    color: black;"
               "}"
               "QMenuBar::item {"
               "    background-color: transparent;"
               "    color: black;"
               "}"
               "QMenuBar::item:selected {"
               "    background-color: #eaeaea;"
               "}"
               "QMenu::item:selected {"
               "    background-color: #f6f6f6;"
               "    color: black;"
               "}"
               "QMenu {"
               "    background-color: #ffffff;"
               "    color: black;"
               "    border: 1px solid #7a7a7a;"
               "}";
    }
}

//не работает
QString ThemeManager::styleSheetForMessageBox() const {
    if (currentTheme_ == Dark) {
        return "QMessageBox {"
               "    background-color: #2d2d2d;"
               "    color: white;"
               "}"
               "QPushButton {"
               "    background-color: #454545;"
               "    color: white;"
               "    border: 1px solid #4a4a4a;"
               "    padding: 5px 10px;"
               "}"
               "QPushButton:hover {"
               "    background-color: #5a5a5a;"
               "}"
               "QPushButton:pressed {"
               "    background-color: #333333;"
               "}";
    } else {
        return "QMessageBox {"
               "    background-color: #fefefe;"
               "    color: black;"
               "}"
               "QPushButton {"
               "    background-color:#7a7a7a;"
               "    color: black;"
               "    border: 1px solid #7a7a7a;"
               "    padding: 5px 10px;"
               "}"
               "QPushButton:hover {"
               "    background-color: ##7a7a7a;"
               "}"
               "QPushButton:pressed {"
               "    background-color: #a0a0a0;"
               "}";
    }
}
