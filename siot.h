#ifndef SIOT_LIBRARY_H
#define SIOT_LIBRARY_H

#include "Arduino.h"
#include "iostream"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <string>

class SIOT
{
private:
  DynamicJsonDocument *doc_;
  PubSubClient client;
  WiFiClient wifiClient_;
  void reconnect();
  bool isbeginErrorState;
  bool isConnectServerState;
  bool isReady;
  // conf
  char *ssid;
  char *password;

  std::string boxId;
  std::string boxSecret;

  const char *canSubPub;
  int lengthOfKey = 0;
  int tempOfkey = 0;


public:
  void callback(char *topic, byte *payload, unsigned int length);
  SIOT();
  SIOT &begin(std::string boxId, std::string secret);
  boolean isBeginError();
  boolean isConnectedServer();
  void run();
  uint8_t digitalRead(char *key);
  float analogRead(char *key);
  void digitalWrite(char *key, uint8_t val);
  void analogWrite(char *key, float val);
};

#endif // SIOT_LIBRARY_H
