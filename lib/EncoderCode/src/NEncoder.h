

/*
 motr.h - Library for controlling DC motors
*/
#ifndef NEncoder_h
#define NEncoder_h

// #include <Ticker.h>
#include <arduino.h>
#include <ticker.h>

#define ACKNOWLEDGED 0
#define CLICKED 5
#define ONECLICK 1
#define LONGCLICK 2

class NEncoder {
public:
  NEncoder(uint8_t pinA, uint8_t pinB, uint8_t buttonPin);

  void init(uint16_t max);
  static void rotateRoutine();

  uint16_t position();
  void clearPosition();
  void setRange(uint16_t max);

  static void buttonRoutine();
  uint8_t button();
  static void buttonTiming();

private:
  static uint16_t encoderPosition;
  static uint16_t max_;
  uint8_t pinA_;
  static uint8_t pinB_;

  static uint8_t buttonPin_;
  static uint8_t buttonState;
  static uint16_t buttonTicker;
};

#endif
