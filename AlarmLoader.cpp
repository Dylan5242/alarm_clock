#include "alarmloader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

QList<AlarmInfo> AlarmLoader::load(const QString &filename)
{
    QList<AlarmInfo> result;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "AlarmLoader: cannot open file" << filename;
        return result;
    }

    const QByteArray bytes = file.readAll();
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
    QJsonArray alarmsArray = root.value("alarms").toArray();
    for (const QJsonValue &val : alarmsArray) {
        if (!val.isObject()) continue;
        QJsonObject obj = val.toObject();

        AlarmInfo info;
        info.day     = obj.value("day").toString();
        info.time    = obj.value("time").toString();
        info.enabled = obj.value("active").toBool();

        result.append(info);
    }

    return result;
}
