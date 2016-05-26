#include <NEncoder.h>
#include <arduino.h>

uint8_t pinA = 12;
uint8_t pinB = 13;
const uint16_t encoderRange = 1000;
NEncoder encoder(pinA, pinB);
void rotationhandler() { encoder.rotateRoutine(); }

void setup() {
  encoder.init(encoderRange);
  attachInterrupt(pinA, rotationhandler, RISING);
}

void loop() { int position = encoder.position(); }
