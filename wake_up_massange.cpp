#include "wake_up_massange.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsOpacityEffect>

WakeUpMassange::WakeUpMassange(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Будильник");
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    resize(300, 200);

    // Чистый фон
    this->setStyleSheet("background-color: black;");

    // Слой с фоном (без влияния на кнопки)
    QLabel *backgroundLabel = new QLabel(this);
    //backgroundLabel->setPixmap(QPixmap(":/pictures/driver.jpg").scaled(size(), Qt::KeepAspectRatioByExpanding));
    backgroundLabel->setGeometry(0, 0, width(), height());
    backgroundLabel->lower(); // на задний план

    label = new QLabel("⏰ Будильник сработал!", this);
    label->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");
    label->setAlignment(Qt::AlignCenter);

    dismissButton = new QPushButton("Выключить", this);
    dismissButton->setFixedHeight(40);
    dismissButton->setStyleSheet(
        "QPushButton {"
        "  background-color: white;"
        "  color: black;"
        "  font-weight: bold;"
        "  border-radius: 6px;"
        "  border: 1px solid gray;"
        "}"
        "QPushButton:hover {"
        "  background-color: #f0f0f0;"
        "}"
        );

    auto *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(label);
    layout->addWidget(dismissButton);
    layout->addStretch();

    connect(dismissButton, &QPushButton::clicked, this, &WakeUpMassange::onDismissClicked);

    // Аудио
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/system_sounds/I_drive.mp3"));
    audioOutput->setVolume(0.3);
    player->play();
}

void WakeUpMassange::onDismissClicked()
{
    if (player) {
        player->stop();
    }
    emit dismissed();
    close();
}
