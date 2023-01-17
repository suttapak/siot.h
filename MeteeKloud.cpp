#include "WString.h"
#include <sys/_intsup.h>
#include "HardwareSerial.h"
#include "WiFiClient.h"
#include <HTTPClient.h>
#include "MeteeKloud.h"
#include <map>


const char *SERVER_HOST = "https://api.rocket-translate.com/subpub/";

#define MQTT_SERVER_HOST "167.71.204.194"
#define MQTT_SERVER_PORT 1883

//********************************** JSON Document size **********************************//
const size_t JSON_DOCUMENT_SIZE = 2048;
WiFiClient wifiClient;



std::map<String, float> value;

//**********************************  **********************************//
SIOT::SIOT()
  : doc_(new DynamicJsonDocument(JSON_DOCUMENT_SIZE)), client(wifiClient) {
  this->isbeginErrorState = false;
  this->isConnectServerState = false;
  this->doc_->clear();
  this->wifiClient_ = wifiClient;
}

SIOT &SIOT::begin(std::string boxId, std::string secret) {
  HTTPClient http;
  // Send an HTTP GET request to the server
  String url = SERVER_HOST + String(boxId.c_str()) + "/" + String(secret.c_str());
  http.begin(url.c_str());    // specify the URL
  int httpCode = http.GET();  // send the request

  // Check the response status code
  if (httpCode > 0) {
    // HTTP request was successful
    Serial.println("HTTP request succeeded");
  } else {
    // HTTP request failed
    Serial.println("HTTP request failed");
  }
  String response = http.getString();
  // Disconnect from the server
  http.end();


  this->canSubPub = response.c_str();

  this->boxId = boxId;
  this->boxSecret = secret;

  String clientId = "SIOT-";
  clientId += String(random(0xffff), HEX);

  this->client.setServer(MQTT_SERVER_HOST, MQTT_SERVER_PORT);
  this->client.setCallback([&](char *topic, byte *payload, unsigned int length) {
    this->callback(topic, payload, length);
  });
  this->client.connect(clientId.c_str(), boxId.c_str(), boxSecret.c_str());

  const char *all = "/#";
  std::string sub(this->canSubPub);
  sub.append(all);

  Serial.println(sub.c_str());

  this->client.subscribe(sub.c_str());
  this->isReady = true;

  return *this;
}


void SIOT::callback(char *topic, byte *payload, unsigned int length) {
  // ...

  char *token = strtok(topic, "/");

  String res ;

  for (int i = 0; i < length; i++) {
    res += String((char)payload[i]);
  }

  float v = res.toFloat();
  token = strtok(NULL, "/");
  value[token] = v;


  // Serial.println("************************");
  // Serial.println(v);
  // Serial.println(value[token]);
  // Serial.println("************************");
}

void SIOT::run() {
  this->client.loop();
}

void SIOT::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (this->client.connect(clientId.c_str(), this->boxId.c_str(), this->boxSecret.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

float SIOT::analogRead(char *key) {
  float v = value[key];
  return v;
}

uint8_t SIOT::digitalRead(char *key) {
  uint8_t v = value[key];
  return v;
}

void SIOT::digitalWrite(char *key, uint8_t val) {
  if (val > 1)
    val = 1;
  std::string json = "{\"value\": " + std::to_string(val) + "}";

  // Convert the string to a const char*
  const char *json_cstr = json.c_str();

  std::string topic(this->canSubPub);
  topic.append("/");
  topic.append(key);

  this->client.publish(topic.c_str(), json_cstr);
}

boolean SIOT::isBeginError() {
  return this->isbeginErrorState;
}

void SIOT::analogWrite(char *key, float val) {
  std::string json = "{\"value\": " + std::to_string(val) + "}";

  // Convert the string to a const char*
  const char *json_cstr = json.c_str();

  std::string topic(this->canSubPub);
  topic.append("/");
  topic.append(key);

  this->client.publish(topic.c_str(), json_cstr);
}

bool SIOT::isConnectedServer() {
  return this->client.connected() && this->isReady;
}