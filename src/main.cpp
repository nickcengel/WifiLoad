#include <NEncoder.h>
#include <arduino.h>

uint8_t pinA = 12;
uint8_t pinB = 13;
int oldA = 0;
int oldB = 4;

NEncoder encoder(pinA, pinB);
void rotationhandler() { encoder.rotateRoutine(); }

void setup() {
  encoder.init();
  attachInterrupt(pinA, rotationhandler, RISING);
}

void loop() { int g = encoder.value(oldA, 3); }
