#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QString>
#include <QObject>

class ThemeManager : public QObject {
    Q_OBJECT

public:
    enum Theme {
        Light,
        Dark
    };
    explicit ThemeManager(QObject* parent = nullptr);
    void setTheme(Theme theme);
    Theme currentTheme() const;

    QString styleSheetForMainWindow() const;
    QString styleSheetForTable() const;
    QString styleSheetForButtons() const;
    QString styleSheetForMenuBar() const;
    QString styleSheetForMessageBox() const;

private:
    Theme currentTheme_;
};

#endif // THEMEMANAGER_H
