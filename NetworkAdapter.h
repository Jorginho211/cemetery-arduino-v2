#ifndef NETWORK_ADAPTER_H
  #define NETWORK_ADAPTER_H

  #include<SoftwareSerial.h>

  class Response {
    public:
      bool success;
      uint16_t status;
      String content;
  };

  class NetworkAdapter {
    public:
      virtual void init(HardwareSerial &serial);
      virtual void init(SoftwareSerial &serial);
      virtual Response get(String url);
      virtual Response post(String url, String body, String contentType);
  };
#endif