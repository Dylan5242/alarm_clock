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
        auto *w = new ListElementWidget(a.day, a.time, ui->listWidget);
        w->setChecked(a.enabled);
        item->setSizeHint(w->sizeHint());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, w);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_plus_clicked()
{
    auto *item = new QListWidgetItem(ui->listWidget);
    auto *widget = new ListElementWidget("Понедельник", "13:00", ui->listWidget);
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
