#ifndef MATEEKLOUD_LIBRARY_H
#define MATEEKLOUD_LIBRARY_H

#include "Arduino.h"
#include <WiFi.h>
#include <PubSubClient.h>

class MateeKloud
{
private:
  PubSubClient client;
  void reconnect();
  bool isbeginErrorState;
  bool isConnectServerState;
  bool isReadyState;
  // conf
  const char *ssid;
  const char *password;
  const char *boxId;
  const char *boxSecret;
  const char *canSubPub;

public:
  MateeKloud();
  MateeKloud &begin(const char *boxId, const char *secret);
  bool isBeginError();
  bool isConnectedServer();
  bool isReady();
  void callback(char *topic, byte *payload, unsigned int length);
  void run();
  uint8_t digitalRead(const char *key);
  float analogRead(const char *key);
  bool digitalWrite(const char *key, uint8_t val);
  bool analogWrite(const char *key, float val);
};

#endif // MateeKloud_LIBRARY_H