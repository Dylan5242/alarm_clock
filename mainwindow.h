#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_plus_clicked();

private:
    void addAlarmItem(const QString &day, const QString &time, bool enabled); // Добавляем объявление
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
