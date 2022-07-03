#include "SIM900.h"

SIM900::SIM900(String apn, String user, String password, uint16_t baudRate) {
  this->m_User = user;
  this->m_Password = password;
  this->m_Apn = apn;
  this->m_BaudRate = baudRate;
}

void SIM900::init(HardwareSerial &serial) {
  this->m_HardwareSerial = &serial;
  this->m_HardwareSerial->begin(9600);
}

void SIM900::init(SoftwareSerial &serial) {
  this->m_SoftwareSerial = &serial;
}

bool SIM900::sendATCommand(String command) {
  unsigned long startTime;

  startTime = millis();
  if(this->m_HardwareSerial != NULL) {
    this->m_HardwareSerial->println(command);
    this->m_HardwareSerial->flush();
    while (!this->m_HardwareSerial->available() && millis() - startTime > SIM900_DEFAULT_TIMEOUT);
  }
  else if(this->m_SoftwareSerial != NULL) {
    this->m_SoftwareSerial->print(command);
    this->m_SoftwareSerial->flush();
    while (!this->m_SoftwareSerial->available() && millis() - startTime > SIM900_DEFAULT_TIMEOUT);
  }

  if (millis() - startTime > 5000) {
    return false;
  }

  return true;
}

Response SIM900::waitForResponse(String validation, uint16_t timeout) {
  Response response;
  response.success = false;
  response.content = "";

  unsigned long startTime = millis();
  uint16_t validationIndex = 0;
  bool readed = false;

  do {
    readed = false;
    char c;

    if(this->m_HardwareSerial != NULL && this->m_HardwareSerial->available() > 0) {
      c = this->m_HardwareSerial->read();
      readed = true;
    }
    else if(this->m_SoftwareSerial != NULL && this->m_SoftwareSerial->available() > 0) {
      c = this->m_SoftwareSerial->read();
      readed = true;
    }
    delay(1);

    // Solo se leen caracteres imprimibles y el retorno de carro \r\n
    if((c < 32 && (c != 10 && c != 13)) || c > 125)
      continue;

    if (readed) {
      if(!response.success) {
        if (c == validation[validationIndex]) {
          validationIndex++;
        }
        else if (validationIndex < validation.length()) {
          validationIndex = 0;
        }

        if(validationIndex == validation.length())
          response.success = true;
      }

      response.content += c;

      startTime = millis();
    }
  } while((millis() - startTime < timeout && !response.success) || readed);

  return response;
}

bool SIM900::connect() {
  bool res = false;
  Response response;

  if(this->isConnected()) return true;

  res = this->sendATCommand("AT+CREG=1");
  if(!res) return false;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return false;

  delay(5000);
  // Se comprueba si esta registrada a una red
  res = this->sendATCommand("AT+CREG?");
  if(!res) return false;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return false;
  if(response.content.indexOf("+CREG: 1,1") == -1) return false;

  //Se configura los parametros de conexion
  res = this->sendATCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  if(!res) return false;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return false;

  res = this->sendATCommand("AT+SAPBR=3,1,\"USER\",\"" + this->m_User + "\"");
  if(!res) return false;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return false;

  res = this->sendATCommand("AT+SAPBR=3,1,\"PWD\",\"" + this->m_Password + "\"");
  if(!res) return false;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return false;

  res = this->sendATCommand("AT+SAPBR=3,1,\"APN\",\"" + this->m_Apn + "\"");
  if(!res) return false;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return false;

  // Se realiza la conexion
  res = this->sendATCommand("AT+SAPBR=1,1");
  if(!res) return false;
  response = this->waitForResponse("OK", 10000);
  if(!response.success) return false;

  // Se espera por la conexion unos 5 segundos.
  unsigned long startMillis = millis();
  while(!this->isConnected() && millis() - startMillis < SIM900_DEFAULT_TIMEOUT);

  return this->isConnected();
}

bool SIM900::isConnected() {
  bool res = this->sendATCommand("AT+SAPBR=2,1");
  if(!res) return false;
  Response response = this->waitForResponse("OK", 1000);
  if(!response.success) return false;
  if(response.content.indexOf("+SAPBR: 1,1") == -1) return false;

  return true;
}

bool SIM900::disconnect() {
  this->sendATCommand("AT+SAPBR=0,1");
  return true;
}

void SIM900::initHttp(String url) {
  bool res = false;
  Response response;

  res = this->sendATCommand("AT+HTTPINIT");
  if(!res) return;
  response = this->waitForResponse("OK", 1000);
  if(!response.success && response.content.indexOf("ERROR")) return;

  res = this->sendATCommand("AT+HTTPPARA=\"CID\",1");
  if(!res) return;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return;

  res = this->sendATCommand("AT+HTTPPARA=\"URL\",\"" + url + "\"");
  if(!res) return;
  response = this->waitForResponse("OK", 1000);
  if(!response.success) return;
}

void SIM900::termHttp() {
  this->sendATCommand("AT+HTTPTERM");
}

uint16_t SIM900::getStatusCode() {
  Response response = this->waitForResponse("+HTTPACTION: 0,", 30000);
  if(!response.success || response.content.indexOf("+HTTPACTION: 0,") == -1) {
    return 0;
  }

  int startStatusIndex = response.content.indexOf(",") + 1;
  return response.content.substring(startStatusIndex, startStatusIndex + 3).toInt();
}

String SIM900::getContent() {
  bool res = this->sendATCommand("AT+HTTPREAD");
  if(!res)
    return "";

  /* Formato de resposta correcta:
    +HTTPREAD: <size_body>
    <body>
    OK
  */

  Response response = this->waitForResponse("+HTTPREAD", 10000);

  // Collese o indice e omitese ata o <size_body>
  int startIndex = response.content.indexOf("+HTTPREAD: ") + String("+HTTPREAD: ").length();
  String content = response.content.substring(startIndex);

  // Collese ata o final de linea para extraer o tamaño do body
  int endIndex = content.indexOf("\r\n");
  int bodyLenght = content.substring(0, endIndex).toInt();  

  // Usando o tamaño do body extraese so o contido do body omitindo os \r\n
  endIndex += 2;
  content = content.substring(endIndex, endIndex + bodyLenght);

  return content;
}

Response SIM900::get(String url) {
  bool res = false;
  Response response;
  Response ret;
  ret.success = false;

  if(!this->connect()) return ret;
  this->initHttp(url);

  // GET
  res = this->sendATCommand("AT+HTTPACTION=0");
  if(!res) {
    this->termHttp();
    this->disconnect();
    return ret;
  }
  response = this->waitForResponse("OK", 30000);
  if(!response.success) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  
  ret.status = this->getStatusCode();
  if(ret.status == 0) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  ret.content = this->getContent();

  this->termHttp();
  this->disconnect();

  ret.success = true;
  return ret;
}

Response SIM900::post(String url, String body, String contentType) {
  bool res = false;
  Response response;
  Response ret;
  ret.success = false;

  if(!this->connect()) return ret;
  this->initHttp(url);

  res = this->sendATCommand("AT+HTTPPARA=\"CONTENT\",\"" + contentType + "\"");
  if(!res) {
    this->termHttp();
    this->disconnect();
    return ret;
  }
  response = this->waitForResponse("OK", 1000);
  if(!response.success) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  res = this->sendATCommand("AT+HTTPDATA=" + String(body.length()) + ",10000");
  if(!res) {
    this->termHttp();
    this->disconnect();
    return ret;
  }
  response = this->waitForResponse("DOWNLOAD", 1000);
  if(!response.success) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  res = this->sendATCommand(body);
  if(!res) {
    this->termHttp();
    this->disconnect();
    return ret;
  }
  response = this->waitForResponse("OK", 1000);
  if(!response.success) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  // POST
  res = this->sendATCommand("AT+HTTPACTION=1");
  if(!res) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  response = this->waitForResponse("OK", 30000);
  if(!response.success) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  ret.status = this->getStatusCode();
  if(ret.status == 0) {
    this->termHttp();
    this->disconnect();
    return ret;
  }

  ret.content = this->getContent();

  this->termHttp();
  this->disconnect();

  ret.success = true;
  return ret;
}
