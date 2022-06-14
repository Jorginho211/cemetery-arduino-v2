#include "SoundPlayer.h"

void SoundPlayer::init(HardwareSerial &serial) {
    serial.begin(9600);
    mp3_set_serial(serial);
    this->init();
}

void SoundPlayer::init(SoftwareSerial &serial) {
    serial.begin(9600);
    mp3_set_serial(serial);
    this->init();
}

void SoundPlayer::init() {
  mp3_set_volume(30);
  mp3_single_loop(false);
  mp3_set_EQ(2);
}

void SoundPlayer::play(uint16_t songNumber) {
  mp3_play(songNumber);
}

void SoundPlayer::stop() {
  mp3_stop();
}

bool SoundPlayer::isPlaying() {
  mp3_get_state();
  Serial.println("AQUI3");
  int state = mp3_wait_state();
  Serial.println("AQUI4");
  Serial.println(String(state));
  return state != 255;
}