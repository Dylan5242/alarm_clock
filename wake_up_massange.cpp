#include "wake_up_massange.h"

WakeUpMassange::WakeUpMassange(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Будильник");
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint); // сначала флаги
    resize(300, 200); // затем размер окна отдельно


    label = new QLabel("⏰ Будильник сработал!", this);
    dismissButton = new QPushButton("Выключить", this);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(dismissButton);

    connect(dismissButton, &QPushButton::clicked, this, &WakeUpMassange::onDismissClicked);

    // Создание плеера и аудиовыхода
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // Установка источника аудио
    QString audioPath = "qrc:/system_sounds/I_drive.mp3";
    player->setSource(QUrl(audioPath));
    audioOutput->setVolume(0.3);
    player->play();

    // Проверка на файл Drive и установка кастомного фона
  //  if (audioPath.contains("I_drive.mp3")) {
  //      setStyleSheet("background-image: url(:/pictures/driver.jpg);"
  //                    "background-repeat: no-repeat;"
  //                    "background-position: center;"
  //                    "background-size: cover;");

  //      label->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");

  //      dismissButton->setStyleSheet(
  //          "QPushButton {"
  //          "  background-color: white;"
  //          "  color: black;"
  //          "  font-weight: bold;"
  //          "  border: none;"
  //          "  padding: 8px 16px;"
  //          "  border-radius: 5px;"
  //          "  opacity: 1;"              // <– на всякий случай
  //          "}"
  //          "QPushButton:hover {"
  //          "  background-color: #e0e0e0;"
  //          "}"
  //          );

    //}

}

void WakeUpMassange::onDismissClicked() {
    if (player) {
        player->stop();
    }
    emit dismissed();
    close();
}
