#ifndef SIM900_H
  #define SIM900_H

  #include<Arduino.h>
  #include<SoftwareSerial.h>

  #define SIM900_DEFAULT_TIMEOUT 5000

  class Response {
    public:
      bool success;
      uint16_t status;
      String content;
  };

  class SIM900 {
    public:
      SIM900(String apn, String user, String password, uint16_t baudRate);
      void init(HardwareSerial &serial);
      void init(SoftwareSerial &serial);
      Response get(String url);
      Response post(String url, String body, String contentType);

    private:
      bool connect();
      bool disconnect();
      bool sendATCommand(String command);
      bool isConnected();
      void initHttp(String url);
      void termHttp();
      uint16_t getStatusCode();
      String getContent();
      Response waitForResponse(String validation, uint16_t timeout);

      String m_Apn;
      String m_User;
      String m_Password;
      uint16_t m_BaudRate;
      HardwareSerial *m_HardwareSerial = NULL;
      SoftwareSerial *m_SoftwareSerial = NULL;
  };
#endif