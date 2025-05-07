#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listelementwidget.h"
#include "alarmsaver.h"
#include "alarmloader.h"

#include <QListWidgetItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Загрузка при старте
    const auto alarms = AlarmLoader::load();
    for (const auto &a : alarms) {
        auto *item = new QListWidgetItem(ui->listWidget);
        auto *w = new ListElementWidget(a.day, a.time, a.week, ui->listWidget);
        w->setChecked(a.enabled);
        item->setSizeHint(w->sizeHint());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, w);
    }

    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_plus_clicked()
{
        auto *item = new QListWidgetItem(ui->listWidget);

        auto *widget = new ListElementWidget("пн", "13:00", 4, this);

        item->setSizeHint(widget->sizeHint());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, widget);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Сбор всех элементов из списка
    QList<ListElementWidget*> elements;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *item = ui->listWidget->item(i);
        if (auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(item))) {
            elements.append(w);
        }
    }

    // Сохраняем в файл
    if (!AlarmSaver::save_to_file("alarms.json", elements)) {
        qWarning() << "Не удалось сохранить будильники!";
    }

    // Вызываем базовый closeEvent чтобы окно закрывалось
    QMainWindow::closeEvent(event);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
        if (w)
            w->setSelected(ui->listWidget->item(i) == item);
    }
}


void MainWindow::on_pushButton_remove_all_clicked()
{

}


void MainWindow::on_pushButton_select_all_clicked()
{

}


void MainWindow::on_pushButton_delete_clicked()
{
    // Найти выбранный элемент
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *item = ui->listWidget->item(i);
        auto *widget = qobject_cast<ListElementWidget *>(ui->listWidget->itemWidget(item));
        if (widget && widget->isSelected()) {
            // Удалить виджет
            delete widget;

            // Удалить сам QListWidgetItem
            delete ui->listWidget->takeItem(i);
            break;  // удаляем только один выбранный
        }
    }
}


void MainWindow::on_pushButton_sort_list_elements_clicked()
{

}

