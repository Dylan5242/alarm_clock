#ifndef WAKE_UP_MASSANGE_H
#define WAKE_UP_MASSANGE_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
//для звука
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QCoreApplication>



class WakeUpMassange : public QDialog {
    Q_OBJECT

public:
    explicit WakeUpMassange(QWidget *parent = nullptr);

signals:
    void dismissed();

private slots:
    void onDismissClicked();

private:
    QLabel *label;
    QPushButton *dismissButton;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif // WAKE_UP_MASSANGE_H
