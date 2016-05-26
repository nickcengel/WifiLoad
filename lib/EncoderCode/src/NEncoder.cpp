

#include "NEncoder.h"
#include <arduino.h>

NEncoder::NEncoder(uint8_t pinA, uint8_t pinB) {
  pinA_ = pinA;
  pinB_ = pinB;
};

int *NEncoder::rotaryBuf;
uint8_t NEncoder::tail;
uint8_t NEncoder::head;
uint8_t NEncoder::pinB_;

void NEncoder::init() {
  pinMode(pinA_, INPUT_PULLUP);
  pinMode(pinB_, INPUT_PULLUP);
  Clear();
};

void NEncoder::rotateRoutine() {
  cli();
  if ((head + 1 == tail) || ((head + 1 == BUFL) && (tail == 0)))
    return; // no more room
  else {
    rotaryBuf[head] = GPIP(pinB_);
    head++;             // increment the head
    if (head == BUFL) { // check for wrap-around
      head = 0;
    }
  }
  sei();
};

int NEncoder::Read() {
  int p;
  if (tail != head) {    // see if any data is available
    p = rotaryBuf[tail]; // grab a byte from the buffer
    tail++;              // increment the tail
    if (tail == BUFL)    // check for wrap-around
      tail = 0;
  } else
    return 0;
  return p;
};

int NEncoder::value(int oldvalue, int scale) {
  cli();
  int sum = oldvalue;
  int bitsToAdd = head - tail;
  while (bitsToAdd--) {
    sum += (scale * Read());
  }
  return sum;
  sei();
};

void NEncoder::Clear() {
  cli();
  for (int i = 0; i < BUFL; i++) {
    rotaryBuf[i] = 0;
  }
  tail = 0;
  head = 0;
  sei();
};
