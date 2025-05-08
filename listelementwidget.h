#ifndef LISTELEMENTWIDGET_H
#define LISTELEMENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "toggleswitch.h"

class ListElementWidget : public QWidget {
    Q_OBJECT
public:
    ListElementWidget(const QString &day, const QString &time, int week, QWidget *parent = nullptr);

    QSize sizeHint() const override;

    // Методы доступа
    QString day() const;
    QString time() const;
    bool isChecked() const;

    // Метод установки состояния переключателя
    void setChecked(bool checked);
    void setSelected(bool selected);
    bool isSelected() const { return is_selected_; }

    int week() const;
    void setDay(const QString &day);
    void setTime(const QString &time);
    void setWeek(int week);

private:
    QLabel *dayLabel;
    QLabel *timeLabel;
    QLabel *weekLabel;
    ToggleSwitch *toggle;
    QLabel* display_label;
    bool is_selected_ = false;
    int week_;

};

#endif // LISTELEMENTWIDGET_H
