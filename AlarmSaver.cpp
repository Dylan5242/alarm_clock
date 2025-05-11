#include "alarmsaver.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDate>
#include <QDebug>

bool AlarmSaver::save_to_file(const QString &filename, const QList<ListElementWidget*> &elements)
{
    QJsonArray alarm_array;
    int max_week = 1;

    for (const auto *elem : elements) {
        QJsonObject alarm_obj;
        alarm_obj["day"]    = elem->day();
        alarm_obj["time"]   = elem->time();
        alarm_obj["week"]   = elem->week();
        alarm_obj["active"] = elem->isChecked();

        if (elem->week() > max_week)
            max_week = elem->week();

        alarm_array.append(alarm_obj);
    }

    QJsonObject root;
    root["alarm_trigger"] = false;

    // Вычисление last_monday на момент сохранения
    QDate today = QDate::currentDate();
    int days_to_subtract = (today.dayOfWeek() + 6) % 7;
    QDate last_monday = today.addDays(-days_to_subtract);

    root["week"] = max_week;
    root["last_monday"] = last_monday.toString(Qt::ISODate);
    root["alarms"] = alarm_array;

    QJsonDocument doc(root);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Failed to open file for writing:" << filename;
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}
