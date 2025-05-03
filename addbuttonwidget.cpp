#include "addbuttonwidget.h"
#include <QVBoxLayout>

AddButtonWidget::AddButtonWidget(QWidget *parent)
    : QWidget(parent)
{
    button = new QPushButton("+", this);
    button->setFixedSize(80, 80);      // Фиксированный размер кнопки
    button->setStyleSheet("font-size: 24px;"); // Увеличенный шрифт

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, &AddButtonWidget::onButtonClicked);
}

void AddButtonWidget::onButtonClicked()
{
    emit addRequested(); // Сигнал добавления элемента
}
