#include "listeditor.h"
#include "listelementwidget.h"
#include <QVBoxLayout>

ListEditor::ListEditor(QWidget *parent)
    : QWidget(parent)
{
    listWidget_ = new QListWidget(this);
    listWidget_->setStyleSheet("QListWidget {"
                               "background-color: white;"
                               "border: 1px solid #ccc;"
                               "font-size: 16px;"
                               "}");
    listWidget_->setFixedSize(350, 600); // Фиксированный размер списка

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(listWidget_);
    layout->setContentsMargins(10, 10, 10, 10); // Отступы
    setLayout(layout);
}

void ListEditor::addItem()
{
    QListWidgetItem *item = new QListWidgetItem(listWidget_);
    ListElementWidget *widget = new ListElementWidget("Новый день", "00:00", listWidget_);
    item->setSizeHint(widget->sizeHint());
    listWidget_->addItem(item);
    listWidget_->setItemWidget(item, widget);
}

QListWidget* ListEditor::listWidget() const
{
    return listWidget_;
}
