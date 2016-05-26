

/*
 motr.h - Library for controlling DC motors
*/
#ifndef NEncoder_h
#define NEncoder_h

// #include <Ticker.h>
#include <arduino.h>

const int BUFL = 64;

class NEncoder {
public:
  NEncoder(uint8_t pinA, uint8_t pinB);

  void init(uint16_t max);
  static void rotateRoutine();
  uint16_t position();

private:
  static uint16_t encoderPosition;
  static uint16_t max_;
  uint8_t pinA_;
  static uint8_t pinB_;
};

#endif
