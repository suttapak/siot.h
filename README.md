# Matee Kloud

## example

การเชื่อมต่อ ESP32 กับ Matee Kloud

```c++
// นำเข้าไลบรารี้
#include "siot.h"
#include <WiFi.h>

const char* ssid = "your-ssid"; // ชื่อไวไฟ
const char* password = "your-password"; // รหัสไวไฟ

// ก็อปปี้มาจากหน้าเว็บ www.rocket-translate.com จะอยู่ใน box -> secret
const char* boxId = "your box id uuid"; // boxId จะได้รับเมื่อสร้าง box บนเว็บ
const char* boxSecret = "YOUR BOX SECRET"; // Secrete จะได้รับเมื่อสร้าง box บนเว็บ

MateeKloud mkloud;

void setup() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  mkloud.begin(boxId, boxSecret); // ตั่งค่าให้กับ Matee Kloud
}

void loop() {
  mkloud.run();
}

```

เปิดปิด LED 2 ดวง

```c++
// นำเข้าไลบรารี้
#include "siot.h"
#include <WiFi.h>

#define LEDPIN1 13
#define LEDPIN2 14

const char* ssid = "your-ssid"; // ชื่อไวไฟ
const char* password = "your-password"; // รหัสไวไฟ

// ก็อปปี้มาจากหน้าเว็บ www.rocket-translate.com จะอยู่ใน box -> secret
const char* boxId = "your box id uuid"; // boxId จะได้รับเมื่อสร้าง box บนเว็บ
const char* boxSecret = "YOUR BOX SECRET"; // Secrete จะได้รับเมื่อสร้าง box บนเว็บ


MateeKloud mkloud;

void setup() {
  pinMode(LEDPIN1,OUTPUT);
  pinMode(LEDPIN2,OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  mkloud.begin(boxId, boxSecret); // ตั่งค่าให้กับ Matee Kloud
}

void loop() {
  mkloud.run();
  if(mkloud.digitalRead("L1")){
    digitalWrite(LEDPIN1,HIGH);
  }else{
    digitalWrite(LEDPIN1,HIGH);
  }
   if(mkloud.digitalRead("L2")){
    digitalWrite(LEDPIN2,HIGH);
  }else{
    digitalWrite(LEDPIN2,HIGH);
  }
}

```

การรับข้อมูล เมื่อกดปุ่มหรือควบคุม Controls Widget บนเว็บสามารถรับข้อมูลที่ส่งมายัง ESP32 ได้ด้วยคำสั่งง่ายสองคำสั่ง `digitalRead` สำหรับอ่านค่า digital 0-1 จาก Matee Kloud `analogRead` สำหรับอ่านค่า analog floting number เลขจุดทศนิยม ตัวอย่าง

```c++
...
float key1 = mkloud.analogRead("KEY1"); // อ่านค่าจากตัวแปร KEY1 จาก Matee Kloud

bool key2 =  mkloud.digitalRead("KEY2"); // อ่านค่าจากตัวแปร KEY2 จาก Matee Kloud
...
```

การส่งข้อมูลจาก ESP32 ไปยัง Matee Kloud สามารถใช้คำสั่ง `digitalWrite` เพื่อส่งค่า digital 0-1 ไปยัง Matee Kloud และ `analogWrite` เพื่อส่งค่่าตัวเลขจุดทศนิยม ตัวอย่าง

```c++
...
mkloud.digitalWrite("KEY1",HIGH);

mkloud.analogWrite("KEY2",3.14159265359);

// เช็คการส่ง
bool succ = mkloud.digitalWrite("LED1",LOW);
if (succ) {
  Serial.println("Send data successfully");
}
...
```
