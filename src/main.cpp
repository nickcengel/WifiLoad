
#include <Arduino.h>

#include <EncoderCode.h>

void setup() {
  setupEncoder();
  Serial.begin(115200);
}

void loop() {
  delay(50);
  Serial.println(encoderPos);
}
