
#include <NEncoder.h>
#include <arduino.h>

const uint8_t pinA = 12;
const uint8_t pinB = 13;
const uint8_t buttonPin = 13;
const uint16_t encoderRange = 1000;
NEncoder encoder(pinA, pinB, buttonPin);
void rotationHandler() { encoder.rotateRoutine(); }
void buttonHandler() { encoder.buttonRoutine(); }

void setup() {
  encoder.init(encoderRange);
  attachInterrupt(pinA, rotationHandler, RISING);
  attachInterrupt(buttonPin, buttonHandler, CHANGE);
}

void loop() { uint8_t button = encoder.button(); }

void mainScreen() {}
void Iscreen() {}
void Vscreen() {}
void Pscreen() {}
void Lscreen() {}
void Sscreen() {}
