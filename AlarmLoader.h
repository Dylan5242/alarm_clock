#ifndef ALARMLOADER_H
#define ALARMLOADER_H

#include <QString>
#include <QList>

struct AlarmInfo {
    QString day;
    QString time;
    bool enabled;
};

class AlarmLoader {
public:
    /// Загружает список будильников из файла filename (по умолчанию "alarms.json").
    /// Возвращает пустой список, если файл не удалось открыть или разобрать.
    static QList<AlarmInfo> load(const QString &filename = "alarms.json");
};

#endif // ALARMLOADER_H
