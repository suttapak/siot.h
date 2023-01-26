# Matee Kloud

## example

การเชื่อมต่อ ESP32 กับ Matee Kloud

```c++
// นำเข้าไลบรารี้
#include "siot.h"
#include <WiFi.h>

#define LEDPIN1 13
#define LEDPIN2 14

const char* ssid = "your-ssid";
const char* password = "your-password";

const char* boxId = "your box id uuid";
const char* boxSecret = "YOUR BOX SECRET";

SIOT siot;

void setup() {
  pinMode(LEDPIN1,OUTPUT);
  pinMode(LEDPIN2,OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  siot.begin(boxId, boxSecret);
}

void loop() {
  if(siot.digitalRead("L1")){
    digitalWrite(LEDPIN1,HIGH);
  }else{
    digitalWrite(LEDPIN1,HIGH);
  }
   if(siot.digitalRead("L2")){
    digitalWrite(LEDPIN2,HIGH);
  }else{
    digitalWrite(LEDPIN2,HIGH);
  }
}

```
