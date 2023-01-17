#ifndef SIOT_LIBRARY_H
#define SIOT_LIBRARY_H

#include "Arduino.h"
#include <WiFi.h>
#include <PubSubClient.h>

class SIOT {
private:
  PubSubClient client;
  void reconnect();
  bool isbeginErrorState;
  bool isConnectServerState;
  bool isReady;
  // conf
  const char *ssid;
  const char *password;
  const char *boxId;
  const char *boxSecret;
  const char *canSubPub;


public:
  SIOT();
  SIOT &begin(const char *boxId, const char *secret);
  boolean isBeginError();
  boolean isConnectedServer();
  void callback(char *topic, byte *payload, unsigned int length);
  void run();
  uint8_t digitalRead(const char *key);
  float analogRead(const char *key);
  bool digitalWrite(const char *key, uint8_t val);
  bool analogWrite(const char *key, float val);
};

#endif  // SIOT_LIBRARY_H