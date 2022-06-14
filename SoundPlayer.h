#ifndef SOUND_PLAYER_H
  #define SOUND_PLAYER_H

  #include <Arduino.h>
  #include <SoftwareSerial.h>
  #include <DFPlayer_Mini_Mp3.h>

  class SoundPlayer {
    public:
      void init(HardwareSerial &serial);
      void init(SoftwareSerial &serial);
      void stop();
      void play(uint16_t songNumber);
      bool isPlaying();

    private:
      void init();
  };
#endif