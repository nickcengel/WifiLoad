
#include <Arduino.h>
#include <EncoderCode.h>

void setup() {
  setupEncoder();
  Serial.begin(19200);
}

void loop() {
  delay(75);
  Serial.println(encoderPos);
}
