#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "servicetable.h"

#include <QMainWindow>
#include <QTableWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void clearWorkspace();
    void addServiceDialog();
    void editServiceDialog();
    void removeService();
    void saveToFile();
    void loadFromFile();
    void aboutProgram();

private:
    ServiceTable *table;
    bool isModified;

    void setupMenu();
    void setupToolbar();
    bool validateFields(const QString &name, const QString &specialist, double price, const QTime &time);
    bool confirmSaveChanges();
};

#endif // MAINWINDOW_H
