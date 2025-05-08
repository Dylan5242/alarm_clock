#ifndef DATAEDITOR_H
#define DATAEDITOR_H

#include <QWidget>
#include <QSet>
#include <QTime>

class QTimeEdit;
class QSpinBox;
class QLabel;
class QCheckBox;
class QPushButton;
class ListElementWidget;

class DataEditor : public QWidget {
    Q_OBJECT
public:
    explicit DataEditor(QWidget *parent = nullptr);
    void loadFromElement(ListElementWidget *element);
    void applyToElement();

    int currentWeek() const;

signals:
    void dataChanged();  // может быть полезно для уведомления MainWindow

private slots:
    void onSelectAllDays();
    void onUnselectAllDays();
    void onWeekChanged(int newWeek);

private:
    void updateUiFromElement();
    QSet<QString> selectedDaysFromCheckboxes() const;
    void setCheckboxesFromDays(const QString &daysText);

    ListElementWidget *current_element_ = nullptr;
    int current_week_ = 1;

    QLabel *label_week_now_;
    QTimeEdit *time_edit_;
    QSpinBox *week_spinbox_;

    QCheckBox *check_monday_;
    QCheckBox *check_tuesday_;
    QCheckBox *check_wednesday_;
    QCheckBox *check_thursday_;
    QCheckBox *check_friday_;
    QCheckBox *check_saturday_;
    QCheckBox *check_sunday_;

    QPushButton *button_select_all_;
    QPushButton *button_remove_all_;
};

#endif // DATAEDITOR_H
