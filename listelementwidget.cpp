#include "listelementwidget.h"
#include <QHBoxLayout>
#include <QDebug>  // Добавляем для qDebug()

ListElementWidget::ListElementWidget(const QString &day, const QString &time, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    dayLabel = new QLabel(day, this);
    timeLabel = new QLabel(time, this);
    toggle = new ToggleSwitch(this);

    dayLabel->setFixedSize(150, 40);
    timeLabel->setFixedSize(100, 40);
    toggle->setFixedSize(100, 40);

    dayLabel->setStyleSheet("font-size: 16px;");
    timeLabel->setStyleSheet("font-size: 16px;");

    layout->addWidget(dayLabel);
    layout->addWidget(timeLabel);
    layout->addWidget(toggle);
    layout->setContentsMargins(10, 10, 10, 10);

    // Добавляем соединение сигналов здесь - после создания всех виджетов
    connect(toggle, &ToggleSwitch::toggled, [this](bool checked) {
        qDebug() << "Toggle state changed for" << dayLabel->text()
        << timeLabel->text() << ":" << checked;
        // Здесь можно добавить сохранение состояния
    });
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
    return QSize(340, 50);
}

void ListElementWidget::setChecked(bool checked) {
    toggle->setChecked(checked);
}

