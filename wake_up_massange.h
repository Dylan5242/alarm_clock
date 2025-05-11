#ifndef WAKEUPMASSANGE_H
#define WAKEUPMASSANGE_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>

class WakeUpMassange : public QDialog
{
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

#endif // WAKEUPMASSANGE_H
