#include "NEncoder.h"
#include <arduino.h>

NEncoder::NEncoder(uint8_t pinA, uint8_t pinB) {
  pinA_ = pinA;
  pinB_ = pinB;
};

uint8_t NEncoder::rotaryBuf[BUFL];
uint8_t NEncoder::*pbuf;

void NEncoder::init() {
  pinMode(pinA_, INPUT);
  pinMode(pinB_, INPUT);
  pbuf = &rotaryBuf[0];
};

void NEncoder::routine() { *pbuf++ = ((GPIP(pinB_)) ? -1 : 1); };
uint8_t NEncoder::Read() { return *pbuf; };
void NEncoder::Clear() {
  *pbuf = 0;
  pbuf = &rotaryBuf[0];
};
