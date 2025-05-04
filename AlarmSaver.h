#ifndef ALARMSAVER_H
#define ALARMSAVER_H

#include <QString>
#include <QList>
#include "listelementwidget.h"

class AlarmSaver {
public:
    static bool save_to_file(const QString &filename, const QList<ListElementWidget*> &elements);
};

#endif // ALARMSAVER_H
