

#include <NEncoder.h>
#include <Ticker.h>
#include <arduino.h>

const uint8_t pinA = 12;
const uint8_t pinB = 13;
const uint8_t buttonPin = 14;
const uint16_t encoderRangeA = 4095;
NEncoder encoder(pinA, pinB, buttonPin);
static uint16_t oldg = 0;
void rotationHandler();
void buttonHandler();

void setup() {
  Serial.begin(115200);

  encoder.init(encoderRangeA);
  attachInterrupt(pinA, rotationHandler, RISING);
  attachInterrupt(buttonPin, buttonHandler, CHANGE);
}

void loop() {
  uint16_t g = encoder.position();
  if (g != oldg)
    Serial.println(g);
  oldg = g;
  uint8_t butt = encoder.button();
  if (butt)
    Serial.println(butt);
}
//
void rotationHandler() { encoder.rotateRoutine(); }
void buttonHandler() { encoder.buttonRoutine(); }

//
// void mainScreen() {}
// void Iscreen() {}
// void Vscreen() {}
// void Pscreen() {}
// void Lscreen() {}
// void Sscreen() {}
//
// uint8_t stepSize(uint16_t tick) {}
