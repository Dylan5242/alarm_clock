#include "alarmsaver.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

bool AlarmSaver::save_to_file(const QString &filename, const QList<ListElementWidget*> &elements) {
    QJsonArray alarm_array;

    for (const auto &elem : elements) {
        QJsonObject alarm_obj;
        alarm_obj["day"] = elem->day();
        alarm_obj["time"] = elem->time();
        alarm_obj["active"] = elem->isChecked();
        alarm_array.append(alarm_obj);
    }

    QJsonObject root;
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
