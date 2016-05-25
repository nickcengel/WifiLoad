/*
  motr.h - Library for controlling DC motors
*/
#ifndef NEncoder_h
#define NEncoder_h

// #include <Ticker.h>
#include <arduino.h>

const int BUFL = 256;

class NEncoder {
public:
  NEncoder(uint8_t pinA, uint8_t pinB);

  void init();
  void routine();
  uint8_t getChange();

private:
  static uint8_t *rotaryBuf;
  static uint8_t wIndex;
  uint8_t pinA_;
  uint8_t pinB_;
};

#endif
