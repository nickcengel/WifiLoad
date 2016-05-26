

#include "NEncoder.h"
#include <arduino.h>

NEncoder::NEncoder(uint8_t pinA, uint8_t pinB) {
  pinA_ = pinA;
  pinB_ = pinB;
};

uint16_t NEncoder::encoderPosition;

uint8_t NEncoder::pinB_;
uint16_t NEncoder::max_;

void NEncoder::init(uint16_t max) {
  pinMode(pinA_, INPUT_PULLUP);
  pinMode(pinB_, INPUT_PULLUP);
  max_ = max;
};

void NEncoder::rotateRoutine() {
  cli();
  bool click = GPIP(pinB_);
  if (click && (encoderPosition < max_))
    encoderPosition++;
  else if (!click && (encoderPosition > 0))
    encoderPosition--;
  sei();
};

uint16_t NEncoder::position() { return encoderPosition; };
