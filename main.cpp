#include <QApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>

#include "mainwindow.h"
#include "wake_up_massange.h"
#include <QProcess>

/*
void startJavaBackgroundChecker() {
    QProcess *process = new QProcess();
    process->start("java", QStringList() << "-cp" << "path/to/your/java/class" << "AlarmBackground");

    // Можно проверять статус
    QObject::connect(process, &QProcess::finished, [](int exitCode) {
        qDebug() << "Java process finished with code:" << exitCode;
    });
}


bool shouldTriggerAlarmFromJson(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл:" << filePath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Ошибка разбора JSON:" << error.errorString();
        return false;
    }

    QJsonObject root = doc.object();
    return root.value("alarm_trigger").toBool(false);
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//   startJavaBackgroundChecker();

//    if (shouldTriggerAlarmFromJson("alarms.json")) {
//        auto w = std::make_unique<WakeUpMassange>();
//        w->show();
//        return a.exec(); // завершаем выполнение здесь
//    } else {
        MainWindow w;
        w.show();
        return a.exec();
//    }
}
