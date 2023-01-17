#include <MeteeKloud.h>

const char * x = "sdfas";
const char * y = "sdfas";

SMeteeKloudIOT mkloud;
void setup() {
  mkloud.begin(x, y);
}
void loop() {
  mkloud.analogRead("L1");
}