#ifndef LISTELEMENTWIDGET_H
#define LISTELEMENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "toggleswitch.h"

class ListElementWidget : public QWidget {
    Q_OBJECT
public:
    explicit ListElementWidget(const QString &day, const QString &time, QWidget *parent = nullptr);
    QSize sizeHint() const override;

    // Добавляем методы доступа
    QString day() const;
    QString time() const;
    bool isChecked() const;

private:
    QLabel *dayLabel;
    QLabel *timeLabel;
    ToggleSwitch *toggle;
};

#endif // LISTELEMENTWIDGET_H
