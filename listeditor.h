#ifndef LISTEDITOR_H
#define LISTEDITOR_H

#include <QWidget>
#include <QListWidget>
#include "listelementwidget.h"

class ListEditor : public QWidget {
    Q_OBJECT
public:
    explicit ListEditor(QWidget *parent = nullptr);
    void addItem();
    QListWidget* listWidget() const;
    QList<ListElementWidget*> get_all_list_elements() const;

private:
    QListWidget *listWidget_;

};

#endif // LISTEDITOR_H
