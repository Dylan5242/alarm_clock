#include "dataeditor.h"
#include "listelementwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimeEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>

DataEditor::DataEditor(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout(this);

    label_week_now_ = new QLabel("Неделя: 1", this);
    time_edit_ = new QTimeEdit(QTime::currentTime(), this);
    week_spinbox_ = new QSpinBox(this);
    week_spinbox_->setRange(1, 4);
    week_spinbox_->setValue(1);

    check_monday_ = new QCheckBox("пн", this);
    check_tuesday_ = new QCheckBox("вт", this);
    check_wednesday_ = new QCheckBox("ср", this);
    check_thursday_ = new QCheckBox("чт", this);
    check_friday_ = new QCheckBox("пт", this);
    check_saturday_ = new QCheckBox("сб", this);
    check_sunday_ = new QCheckBox("вс", this);

    button_select_all_ = new QPushButton("Выбрать все", this);
    button_remove_all_ = new QPushButton("Снять выбор", this);

    connect(button_select_all_, &QPushButton::clicked, this, &DataEditor::onSelectAllDays);
    connect(button_remove_all_, &QPushButton::clicked, this, &DataEditor::onUnselectAllDays);
    connect(week_spinbox_, QOverload<int>::of(&QSpinBox::valueChanged), this, &DataEditor::onWeekChanged);

    mainLayout->addWidget(label_week_now_);
    mainLayout->addWidget(time_edit_);
    mainLayout->addWidget(week_spinbox_);
    mainLayout->addWidget(check_monday_);
    mainLayout->addWidget(check_tuesday_);
    mainLayout->addWidget(check_wednesday_);
    mainLayout->addWidget(check_thursday_);
    mainLayout->addWidget(check_friday_);
    mainLayout->addWidget(check_saturday_);
    mainLayout->addWidget(check_sunday_);
    mainLayout->addWidget(button_select_all_);
    mainLayout->addWidget(button_remove_all_);
    setLayout(mainLayout);
}

void DataEditor::loadFromElement(ListElementWidget *element) {
    if (!element) return;
    current_element_ = element;
    time_edit_->setTime(QTime::fromString(element->time(), "HH:mm"));
    week_spinbox_->setValue(element->week());
    setCheckboxesFromDays(element->day());
}

void DataEditor::applyToElement() {
    if (!current_element_) return;
    QStringList days = selectedDaysFromCheckboxes().values();
    QString daysString = days.join(" ");
    QString timeString = time_edit_->time().toString("HH:mm");
    int week = week_spinbox_->value();
    current_element_->setDay(daysString);
    current_element_->setTime(timeString);
    current_element_->setWeek(week);
    emit dataChanged();
}

void DataEditor::onSelectAllDays() {
    check_monday_->setChecked(true);
    check_tuesday_->setChecked(true);
    check_wednesday_->setChecked(true);
    check_thursday_->setChecked(true);
    check_friday_->setChecked(true);
    check_saturday_->setChecked(true);
    check_sunday_->setChecked(true);
}

void DataEditor::onUnselectAllDays() {
    check_monday_->setChecked(false);
    check_tuesday_->setChecked(false);
    check_wednesday_->setChecked(false);
    check_thursday_->setChecked(false);
    check_friday_->setChecked(false);
    check_saturday_->setChecked(false);
    check_sunday_->setChecked(false);
    if (current_element_) current_element_->setChecked(false);
}

void DataEditor::onWeekChanged(int newWeek) {
    current_week_ = newWeek;
    label_week_now_->setText(QString("Неделя: %1").arg(current_week_));
}

int DataEditor::currentWeek() const {
    return current_week_;
}

QSet<QString> DataEditor::selectedDaysFromCheckboxes() const {
    QSet<QString> days;
    if (check_monday_->isChecked()) days.insert("пн");
    if (check_tuesday_->isChecked()) days.insert("вт");
    if (check_wednesday_->isChecked()) days.insert("ср");
    if (check_thursday_->isChecked()) days.insert("чт");
    if (check_friday_->isChecked()) days.insert("пт");
    if (check_saturday_->isChecked()) days.insert("сб");
    if (check_sunday_->isChecked()) days.insert("вс");
    return days;
}

void DataEditor::setCheckboxesFromDays(const QString &daysText) {
    QStringList days = daysText.split(" ", Qt::SkipEmptyParts);
    check_monday_->setChecked(days.contains("пн"));
    check_tuesday_->setChecked(days.contains("вт"));
    check_wednesday_->setChecked(days.contains("ср"));
    check_thursday_->setChecked(days.contains("чт"));
    check_friday_->setChecked(days.contains("пт"));
    check_saturday_->setChecked(days.contains("сб"));
    check_sunday_->setChecked(days.contains("вс"));
}
