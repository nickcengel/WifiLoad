
#include <NEncoder.h>
#include <arduino.h>

const uint8_t pinA = 12;
const uint8_t pinB = 13;
const uint8_t buttonPin = 13;
const uint16_t encoderRangeA = 4095;
const uint16_t encoderRangeB = 3;
NEncoder encoder(pinA, pinB, buttonPin);
void rotationHandler() { encoder.rotateRoutine(); }
void buttonHandler() { encoder.buttonRoutine(); }

void setup() {
  encoder.init(encoderRangeA);
  attachInterrupt(pinA, rotationHandler, RISING);
  attachInterrupt(buttonPin, buttonHandler, CHANGE);
}

void loop() {
  uint8_t button = encoder.button();
  encoder.clearPosition();
  encoder.setRange(encoderRangeB);
}

void mainScreen() {}
void Iscreen() {}
void Vscreen() {}
void Pscreen() {}
void Lscreen() {}
void Sscreen() {}

uint8_t stepSize(uint16_t tick) {}
