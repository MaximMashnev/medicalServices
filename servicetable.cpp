#include "servicetable.h"
#include <QTableWidgetItem>
#include <QTime>
#include <QKeyEvent>

ServiceTable::ServiceTable(QWidget *parent) : QTableWidget(parent) {
    setColumnCount(4);
    setHorizontalHeaderLabels({"Название услуги", "Специалист", "Стоимость", "Время"});
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ServiceTable::addServiceRow(const QString &name, const QString &specialist, double price, const QTime &time) {
    int row = rowCount();
    insertRow(row);
    setItem(row, 0, new QTableWidgetItem(name));
    setItem(row, 1, new QTableWidgetItem(specialist));
    setItem(row, 2, new QTableWidgetItem(QString::number(price, 'f', 2)));
    setItem(row, 3, new QTableWidgetItem(time.toString("HH:mm")));
}

void ServiceTable::editServiceRow(int row, const QString &name, const QString &specialist, double price, const QTime &time) {
    if (row >= 0 && row < rowCount()) {
        item(row, 0)->setText(name);
        item(row, 1)->setText(specialist);
        item(row, 2)->setText(QString::number(price, 'f', 2));
        item(row, 3)->setText(time.toString("HH:mm"));
    }
}

bool ServiceTable::validateServiceRow(int row, QString &name, QString &specialist, double &price, QTime &time) const {
    if (row >= 0 && row < rowCount()) {
        name = item(row, 0)->text();
        specialist = item(row, 1)->text();
        price = item(row, 2)->text().toDouble();
        time = QTime::fromString(item(row, 3)->text(), "HH:mm");
        return !name.isEmpty() && !specialist.isEmpty() && price >= 0 && time.isValid();
    }
    return false;
}

void ServiceTable::clearTable() {
    setRowCount(0);
}
