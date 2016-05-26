

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

  void init();
  static void rotateRoutine();
  int Read();
  void Clear();
  int value(int oldvalue, int scale);

private:
  static int *rotaryBuf;
  static uint8_t tail;
  static uint8_t head;
  static int count;

  uint8_t pinA_;
  static uint8_t pinB_;
};

#endif
