#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listelementwidget.h"
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_plus_clicked()
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ListElementWidget *widget = new ListElementWidget("Понедельник", "13:00", ui->listWidget);
    item->setSizeHint(widget->sizeHint());
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);
}
