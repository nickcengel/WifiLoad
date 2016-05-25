#include "NEncoder.h"
#include <arduino.h>

NEncoder::NEncoder(uint8_t pinA, uint8_t pinB) {
  pinA_ = pinA;
  pinB_ = pinB;
};

uint8_t *NEncoder::rotaryBuf;

void NEncoder::init() {
  pinMode(pinA_, INPUT);
  pinMode(pinB_, INPUT);
};

void NEncoder::routine() { *rotaryBuf = ((GPIP(pinB_)) ? -1 : 1); };
uint8_t NEncoder::getChange() { return *rotaryBuf; };
