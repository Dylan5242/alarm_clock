#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listelementwidget.h"
#include "alarmsaver.h"
#include "alarmloader.h"
#include "dataeditor.h"

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

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
        if (w)
            w->setSelected(ui->listWidget->item(i) == item);
    }

    auto *widget = qobject_cast<ListElementWidget *>(ui->listWidget->itemWidget(item));
    if (!widget)
        return;

    //current_element_ = widget; //сохранить текущий выбранный элемент

    // Установка времени
    QTime time = QTime::fromString(widget->time(), "HH:mm");
    if (time.isValid())
        ui->timeEdit->setTime(time);

    // Установка недели
    ui->spinBox_number_week->setValue(widget->week());

    // Сброс чекбоксов
    QList<QCheckBox*> checkboxes = {
        ui->checkBox_monday,
        ui->checkBox_thuesday,
        ui->checkBox_wednesday,
        ui->checkBox_thursday,
        ui->checkBox_friday,
        ui->checkBox_saturday,
        ui->checkBox_sunday
    };
    for (QCheckBox *cb : checkboxes)
        cb->setChecked(false);

    // Установка чекнутых дней
    QStringList dayShort = widget->day().split(' ', Qt::SkipEmptyParts);
    QMap<QString, QCheckBox*> map = {
        { "пн", ui->checkBox_monday },
        { "вт", ui->checkBox_thuesday },
        { "ср", ui->checkBox_wednesday },
        { "чт", ui->checkBox_thursday },
        { "пт", ui->checkBox_friday },
        { "сб", ui->checkBox_saturday },
        { "вс", ui->checkBox_sunday }
    };
    for (const QString &d : dayShort) {
        if (map.contains(d))
            map[d]->setChecked(true);
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




void MainWindow::on_pushButton_apply_clicked()
{

}

