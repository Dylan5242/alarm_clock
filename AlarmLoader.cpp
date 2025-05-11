#include "alarmloader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDate>

int current_week = 1;

QList<Alarm> AlarmLoader::load(const QString &filename)
{
    QList<Alarm> result;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "AlarmLoader: cannot open file" << filename;
        return result;
    }

    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "AlarmLoader: JSON parse error:" << parseError.errorString();
        return result;
    }

    if (!doc.isObject()) {
        qWarning() << "AlarmLoader: JSON root is not an object";
        return result;
    }

    QJsonObject root = doc.object();

    // === Подсчёт текущей недели ===
    current_week = root.value("week").toInt(1);  // <= сохраняем глобально
      // default = 1
    QString last_monday_str = root.value("last_monday").toString();
    QDate last_monday = QDate::fromString(last_monday_str, Qt::ISODate);
    QDate today = QDate::currentDate();

    // Определяем ближайший прошедший понедельник для today
    int days_since_monday = (today.dayOfWeek() + 6) % 7;
    QDate this_monday = today.addDays(-days_since_monday);

    if (last_monday.isValid()) {
        int days_between = last_monday.daysTo(this_monday);
        int weeks_passed = days_between / 7;

        if (weeks_passed > 0) {
            current_week = ((current_week - 1 + weeks_passed) % 4) + 1;

            // Обновим root
            root["week"] = current_week;
            root["last_monday"] = this_monday.toString(Qt::ISODate);

            // Перезапись файла
            QJsonDocument updated_doc(root);
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                file.write(updated_doc.toJson(QJsonDocument::Indented));
                file.close();
            }
        }
    } else {
        // Первичная инициализация
        root["week"] = current_week;
        root["last_monday"] = this_monday.toString(Qt::ISODate);

        QJsonDocument updated_doc(root);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            file.write(updated_doc.toJson(QJsonDocument::Indented));
            file.close();
        }
    }

    // === Загрузка будильников ===
    QJsonArray alarmsArray = root.value("alarms").toArray();
    for (const QJsonValue &val : alarmsArray) {
        if (!val.isObject()) continue;
        QJsonObject obj = val.toObject();

        Alarm info;
        info.day     = obj.value("day").toString();
        info.time    = obj.value("time").toString();
        info.week    = obj.value("week").toInt();
        info.enabled = obj.value("active").toBool();

        result.append(info);
    }

    return result;
}
