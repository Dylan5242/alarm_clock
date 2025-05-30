#ifndef ALARMLOADER_H
#define ALARMLOADER_H

#include <QString>
#include <QList>

struct Alarm {
    QString day;
    QString time;
    int week;
    bool enabled;
};

// Глобальная переменная — номер текущей недели
extern int current_week;

class AlarmLoader {
public:
    static QList<Alarm> load(const QString &filename = "alarms.json");
    static void save(const QList<Alarm> &alarms, const QString &filename = "alarms.json");
};

#endif // ALARMLOADER_H
