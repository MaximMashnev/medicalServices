#include "mainwindow.h"
#include "servicetable.h"
#include "addservicedialog.h"

#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isModified(false) {
    resize(1024, 768);

    table = new ServiceTable(this);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setCentralWidget(table);

    setupMenu();
    setupToolbar();
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenu() {
    QMenu *fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction("Новая таблица", [this]() { clearWorkspace(); });
    fileMenu->addAction("Открыть таблицу", this, &MainWindow::loadFromFile);
    fileMenu->addAction("Сохранить таблицу", this, &MainWindow::saveToFile);
    fileMenu->addSeparator();
    fileMenu->addAction("Выход", this, &QMainWindow::close);

    QMenu *helpMenu = menuBar()->addMenu("Справка");
    helpMenu->addAction("О программе", this, &MainWindow::aboutProgram);
}

void MainWindow::setupToolbar() {
    QToolBar *toolbar = addToolBar("Управление услугами");

    QPushButton *addButton = new QPushButton("Добавить услугу");
    QPushButton *editButton = new QPushButton("Изменить услугу");
    QPushButton *removeButton = new QPushButton("Удалить услугу");

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addServiceDialog);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editServiceDialog);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeService);

    toolbar->addWidget(addButton);
    toolbar->addWidget(editButton);
    toolbar->addWidget(removeButton);
}

void MainWindow::clearWorkspace() {
    if (confirmSaveChanges()) {
        table->clearTable();
        isModified = false;
    }
}

void MainWindow::addServiceDialog() {
    AddServiceDialog dialog(this);
    dialog.setWindowTitle("Добавление услуги");
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        QString specialist = dialog.getSpecialist();
        double price = dialog.getPrice();
        QTime time = dialog.getTime();

        if (validateFields(name, specialist, price, time)) {
            table->addServiceRow(name, specialist, price, time);
            isModified = true;
        }
    }
}

void MainWindow::editServiceDialog() {
    int row = table->currentRow();
    if (row >= 0) {
        QString name, specialist;
        double price;
        QTime time;

        if (table->validateServiceRow(row, name, specialist, price, time)) {
            AddServiceDialog dialog(this);
            dialog.setWindowTitle("Редактирование услуги");
            dialog.setValues(name, specialist, price, time);
            if (dialog.exec() == QDialog::Accepted) {
                if (validateFields(dialog.getName(), dialog.getSpecialist(), dialog.getPrice(), dialog.getTime())) {
                    table->editServiceRow(row, dialog.getName(), dialog.getSpecialist(), dialog.getPrice(), dialog.getTime());
                    isModified = true;
                }
            }
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу для редактирования.");
    }
}

void MainWindow::removeService() {
    int row = table->currentRow();
    if (row >= 0) {
        auto reply = QMessageBox::question(this, "Удаление",
                                           "Вы действительно хотите безвозвратно удалить эту услугу?",
                                           QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            table->removeRow(row);
            isModified = true;
        } else if (reply == QMessageBox::No) {
            isModified = false;
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу для удаления.");
    }
}

void MainWindow::saveToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Таблицы (*.csv)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            for (int i = 0; i < table->rowCount(); ++i) {
                QStringList rowData;
                for (int j = 0; j < table->columnCount(); ++j) {
                    rowData << table->item(i, j)->text();
                }
                out << rowData.join(",") << "\n";
            }
            file.close();
            isModified = false;
        }
    }
}

void MainWindow::loadFromFile() {
    if (confirmSaveChanges()) {
        QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Таблицы (*.csv)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly)) {
                table->clearTable();
                QTextStream in(&file);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    QStringList rowData = line.split(",");
                    if (rowData.size() == table->columnCount()) {
                        table->addServiceRow(rowData[0], rowData[1], rowData[2].toDouble(), QTime::fromString(rowData[3], "HH:mm"));
                    }
                }
                file.close();
                isModified = false;
            }
        }
    }
}

void MainWindow::aboutProgram() {
    QFile file("/CBP/medicalServices/about.txt");
    QString aboutText;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        aboutText = file.readAll();
        file.close();
    } else {
        aboutText = "Не удалось загрузить информацию о программе.";
    }

    QMessageBox::information(this, "О программе", aboutText);
}


void MainWindow::closeEvent(QCloseEvent *event) {
    if (isModified) {
        auto reply = QMessageBox::question(this, "Выход", "Вы хотите сохранить изменения перед выходом?");
        if (reply == QMessageBox::Yes) {
            saveToFile();
        } else if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }
    event->accept();
}

bool MainWindow::validateFields(const QString &name, const QString &specialist, double price, const QTime &time) {
    if (name.isEmpty() || specialist.isEmpty() || price < 0 || !time.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены корректно.");
        return false;
    }
    return true;
}

bool MainWindow::confirmSaveChanges() {
    if (isModified) {
        auto reply = QMessageBox::question(this, "Сохранение",
                                           "У вас есть несохраненные изменения. Хотите сохранить их перед продолжением?",
                                           QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            saveToFile();
        } else if (reply == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}
