#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listelementwidget.h"
#include "alarmloader.h"
#include "alarmsaver.h"
#include "wake_up_massange.h"
#include "alarmloader.h"



#include <QListWidgetItem>
#include <QCloseEvent>
#include <QTime>
#include <QMap>
#include <QDate>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , current_element_(nullptr)
{
    ui->setupUi(this);

    // 1) Загрузка при старте
    const auto alarms = AlarmLoader::load();
    for (const auto &a : alarms) {
        addAlarmItem(a.day, a.time, a.week, a.enabled);
    }

    // 2) Подключаем сигналы
    connect(ui->listWidget, &QListWidget::itemClicked,
            this, &MainWindow::on_listWidget_itemClicked);
    connect(ui->pushButton_apply, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_apply_clicked);

    ui->label_week_now->setText(QString("неделя: %1").arg(current_week));


    // 3) Запускаем таймер для проверки времени каждую минуту
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkAndTriggerAlarms);
    timer->start(60000); // 60 секунд = 1 минута

}

void MainWindow::checkAndTriggerAlarms()
{
    const QList<Alarm> alarms = AlarmLoader::load();
    const QTime now = QTime::currentTime();
    const QDate today = QDate::currentDate();
    const int week = current_week;

    QString day_str = QLocale(QLocale::Russian).dayName(today.dayOfWeek(), QLocale::ShortFormat); // "пн", "вт" и т.д.

    for (const Alarm &alarm : alarms) {
        if (!alarm.enabled)
            continue;

        if (!alarm.day.contains(day_str))
            continue;

        if (alarm.week != week)
            continue;

        QTime alarm_time = QTime::fromString(alarm.time, "HH:mm");

        if (!alarm_time.isValid())
            continue;

        // если сейчас точно совпадает с временем будильника
        if (now.hour() == alarm_time.hour() && now.minute() == alarm_time.minute()) {
            WakeUpMassange *message = new WakeUpMassange();
            message->setAttribute(Qt::WA_DeleteOnClose);
            message->show();
            return;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addAlarmItem(const QString &day,
                              const QString &time,
                              int week,
                              bool enabled)
{
    auto *item = new QListWidgetItem(ui->listWidget);
    auto *w = new ListElementWidget(day, time, week, ui->listWidget);
    w->setChecked(enabled);
    item->setSizeHint(w->sizeHint());
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, w);
}

void MainWindow::on_pushButton_plus_clicked()
{
    // При добавлении по умолчанию: текущее время + 5 мин, текущий день и неделя = 1
    QTime t = QTime::currentTime().addSecs(5 * 60);
    QString timeStr = t.toString("HH:mm");

    int dow = QDate::currentDate().dayOfWeek();
    QString dayShort = QLocale(QLocale::Russian, QLocale::Russia).dayName(dow, QLocale::ShortFormat); // пн, вт, ...
    int week = 1;

    addAlarmItem(dayShort, timeStr, week, true);
}

void MainWindow::on_pushButton_remove_all_clicked()
{
    // Снять выбор со всех чекбоксов правой панели
    ui->checkBox_monday->setChecked(false);
    ui->checkBox_thuesday->setChecked(false);
    ui->checkBox_wednesday->setChecked(false);
    ui->checkBox_thursday->setChecked(false);
    ui->checkBox_friday->setChecked(false);
    ui->checkBox_saturday->setChecked(false);
    ui->checkBox_sunday->setChecked(false);

    if (current_element_)
        current_element_->setChecked(false);
}

void MainWindow::on_pushButton_select_all_clicked()
{
    // Отметить все дни
    ui->checkBox_monday->setChecked(true);
    ui->checkBox_thuesday->setChecked(true);
    ui->checkBox_wednesday->setChecked(true);
    ui->checkBox_thursday->setChecked(true);
    ui->checkBox_friday->setChecked(true);
    ui->checkBox_saturday->setChecked(true);
    ui->checkBox_sunday->setChecked(true);
}

void MainWindow::on_pushButton_delete_clicked()
{
    // Удалить выделенный элемент в списке
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *item = ui->listWidget->item(i);
        auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(item));
        if (w && w->isSelected()) {
            delete ui->listWidget->takeItem(i);
            break;
        }
    }
    // После удаления может поменяться «текущая неделя» в твоей логике
}

void MainWindow::on_pushButton_sort_list_elements_clicked()
{
    // Сортировка всех элементов по времени (HH:mm) возрастанию
    struct Entry { QString time; QListWidgetItem *item; ListElementWidget *w; };

    QList<Entry> list;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *item = ui->listWidget->item(i);
        auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(item));
        if (w) {
            list.append({ w->time(), item, w });
        }
    }
    std::sort(list.begin(), list.end(), [](auto &a, auto &b){
        return QTime::fromString(a.time, "HH:mm") < QTime::fromString(b.time, "HH:mm");
    });

    // Переносим в новый порядок
    ui->listWidget->clear();
    for (auto &e : list) {
        ui->listWidget->addItem(e.item);
        ui->listWidget->setItemWidget(e.item, e.w);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // 1) Выделяем только один элемент
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
        if (w)
            w->setSelected(ui->listWidget->item(i) == item);
    }

    // 2) Запоминаем текущий и загружаем данные в правую панель
    auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(item));
    if (!w) return;

    current_element_ = w;

    // время
    QTime tt = QTime::fromString(w->time(), "HH:mm");
    if (tt.isValid()) ui->timeEdit->setTime(tt);

    // неделя
    int correct_week = w->week();
    if (correct_week > 4){
        correct_week = 4;
    }
    else if (correct_week < 1){
        correct_week = 1;
    }
    ui->spinBox_number_week->setValue(correct_week);

    // дни недели
    QStringList days = w->day().split(' ', Qt::SkipEmptyParts);
    ui->checkBox_monday->setChecked(days.contains("пн"));
    ui->checkBox_thuesday->setChecked(days.contains("вт"));
    ui->checkBox_wednesday->setChecked(days.contains("ср"));
    ui->checkBox_thursday->setChecked(days.contains("чт"));
    ui->checkBox_friday->setChecked(days.contains("пт"));
    ui->checkBox_saturday->setChecked(days.contains("сб"));
    ui->checkBox_sunday->setChecked(days.contains("вс"));
}

void MainWindow::on_pushButton_apply_clicked()
{
    if (!current_element_) return;

    // применяем время
    QString timeStr = ui->timeEdit->time().toString("HH:mm");
    current_element_->setTime(timeStr);

    // применяем неделю
    int week = ui->spinBox_number_week->value();
    if (week > 4){
        week = 4;
    }
    else if (week < 1){
        week = 1;
    }
    current_element_->setWeek(week);

    // применяем дни
    QStringList sel;
    if (ui->checkBox_monday->isChecked())    sel << "пн";
    if (ui->checkBox_thuesday->isChecked())  sel << "вт";
    if (ui->checkBox_wednesday->isChecked()) sel << "ср";
    if (ui->checkBox_thursday->isChecked())  sel << "чт";
    if (ui->checkBox_friday->isChecked())    sel << "пт";
    if (ui->checkBox_saturday->isChecked())  sel << "сб";
    if (ui->checkBox_sunday->isChecked())    sel << "вс";
    current_element_->setDay(sel.join(" "));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Сохраняем все будильники в JSON
    QList<ListElementWidget*> elems;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto *item = ui->listWidget->item(i);
        if (auto *w = qobject_cast<ListElementWidget*>(ui->listWidget->itemWidget(item))) {
            elems.append(w);
        }
    }
    AlarmSaver::save_to_file("alarms.json", elems);

    QMainWindow::closeEvent(event);
}
