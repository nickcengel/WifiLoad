
#include <NEncoder.h>
#include <arduino.h>

uint8_t pinA = 3;
uint8_t pinB = 1;

NEncoder encoder(pinA, pinB);
void handler() { encoder.routine(); }

void setup() {
  encoder.init();
  attachInterrupt(pinA, handler, CHANGE);
}

void loop() { int s = encoder.getChange(); }
