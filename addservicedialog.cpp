#include "addservicedialog.h"
#include <QMessageBox>
#include <QStyledItemDelegate>
#include <QRegularExpressionValidator>

AddServiceDialog::AddServiceDialog(QWidget *parent) : QDialog(parent) {
    setFixedSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Название услуги");
    nameEdit->setMaxLength(100);

    specialistEdit = new QLineEdit(this);
    specialistEdit->setPlaceholderText("Наименование специалиста");
    specialistEdit->setMaxLength(50);
    QRegularExpression regex("^[a-zA-Zа-яА-ЯёЁ\\s]+$");
    QValidator* validator = new QRegularExpressionValidator(regex, specialistEdit);
    specialistEdit->setValidator(validator);

    priceEdit = new QDoubleSpinBox(this);
    priceEdit->setRange(0, 100000);
    priceEdit->setPrefix("₽ ");

    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("HH:mm");

    layout->addWidget(nameEdit);
    layout->addWidget(specialistEdit);
    layout->addWidget(priceEdit);
    layout->addWidget(timeEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        if (nameEdit->text().isEmpty() || specialistEdit->text().isEmpty() || !timeEdit->time().isValid()) {
            QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены корректно.");
        } else {
            accept();
        }
    });
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString AddServiceDialog::getName() const {
    return nameEdit->text();
}

QString AddServiceDialog::getSpecialist() const {
    return specialistEdit->text();
}

double AddServiceDialog::getPrice() const {
    return priceEdit->value();
}

QTime AddServiceDialog::getTime() const {
    return timeEdit->time();
}

void AddServiceDialog::setValues(const QString &name, const QString &specialist, double price, const QTime &time) {
    nameEdit->setText(name);
    specialistEdit->setText(specialist);
    priceEdit->setValue(price);
    timeEdit->setTime(time);
}
