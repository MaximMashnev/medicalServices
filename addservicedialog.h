#ifndef ADDSERVICEDIALOG_H
#define ADDSERVICEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QTimeEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class AddServiceDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddServiceDialog(QWidget *parent = nullptr);

    QString getName() const;
    QString getSpecialist() const;
    double getPrice() const;
    QTime getTime() const;

    void setValues(const QString &name, const QString &specialist, double price, const QTime &time);
private:
    QLineEdit *nameEdit;
    QLineEdit *specialistEdit;
    QDoubleSpinBox *priceEdit;
    QTimeEdit *timeEdit;
};

#endif // ADDSERVICEDIALOG_H
