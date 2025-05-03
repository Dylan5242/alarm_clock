#ifndef LISTEDITOR_H
#define LISTEDITOR_H

#include <QWidget>
#include <QListWidget>

class ListEditor : public QWidget {
    Q_OBJECT
public:
    explicit ListEditor(QWidget *parent = nullptr);
    void addItem();
    QListWidget* listWidget() const;

private:
    QListWidget *listWidget_;
};

#endif // LISTEDITOR_H
