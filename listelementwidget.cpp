#include "listelementwidget.h"
#include "dataeditor.h"

#include <QHBoxLayout>
#include <QVBoxLayout>  // Не забываем!
#include <QDebug>

ListElementWidget::ListElementWidget(const QString &day, const QString &time, int week, QWidget *parent)
    : QWidget(parent), week_(week)  // Инициализируем поле недели
{
    auto *main_layout = new QVBoxLayout(this); // Главный вертикальный layout

    // Верхняя строка: время, неделя и переключатель
    auto *top_layout = new QHBoxLayout();

    timeLabel = new QLabel(time, this);
    weekLabel = new QLabel(QString("неделя %1").arg(week), this);
    toggle = new ToggleSwitch(this);

    timeLabel->setStyleSheet("font-size: 16px; color: black;");
    weekLabel->setStyleSheet("font-size: 16px; color: black;");

    timeLabel->setFixedWidth(70);
    weekLabel->setFixedWidth(100);
    toggle->setFixedSize(80, 30);

    top_layout->addWidget(timeLabel);
    top_layout->addWidget(weekLabel);
    top_layout->addStretch();
    top_layout->addWidget(toggle);

    // Нижняя строка: дни недели
    dayLabel = new QLabel(day, this);
    dayLabel->setStyleSheet("font-size: 14px; color: black;");
    dayLabel->setAlignment(Qt::AlignLeft);

    // Сборка слоёв
    main_layout->addLayout(top_layout);
    main_layout->addWidget(dayLabel);
    main_layout->setContentsMargins(10, 10, 10, 10);

    connect(toggle, &ToggleSwitch::toggled, [this](bool checked) {
        qDebug() << "Toggle state changed for" << dayLabel->text()
        << timeLabel->text() << ":" << checked;
    });
}

void ListElementWidget::setSelected(bool selected)
{
    is_selected_ = selected;
    setStyleSheet(selected ? "background-color: lightgray;" : "");
}

QString ListElementWidget::day() const {
    return dayLabel->text();
}

QString ListElementWidget::time() const {
    return timeLabel->text();
}

bool ListElementWidget::isChecked() const {
    return toggle->isChecked();
}

QSize ListElementWidget::sizeHint() const {
    return QSize(200, 70);  // увеличил ширину
}

void ListElementWidget::setChecked(bool checked) {
    toggle->setChecked(checked);
}

int ListElementWidget::week() const {
    return week_;
}

void ListElementWidget::setDay(const QString &day) {
    dayLabel->setText(day);
}

void ListElementWidget::setTime(const QString &time) {
    timeLabel->setText(time);
}

void ListElementWidget::setWeek(int week) {
    week_ = week;
    weekLabel->setText(QString("неделя %1").arg(week));
}
