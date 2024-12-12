#ifndef SERVICETABLE_H
#define SERVICETABLE_H

#include <QTableWidget>
#include <QTime>

class ServiceTable : public QTableWidget {
    Q_OBJECT

public:
    explicit ServiceTable(QWidget *parent = nullptr);

    void clearTable();
    void addServiceRow(const QString &name, const QString &specialist, double price, const QTime &time);
    void editServiceRow(int row, const QString &name, const QString &specialist, double price, const QTime &time);
    bool validateServiceRow(int row, QString &name, QString &specialist, double &price, QTime &time) const;
};

#endif // SERVICETABLE_H
