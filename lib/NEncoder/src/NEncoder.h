

#ifndef NEncoder_h
#define NEncoder_h

#include <Arduino.h>

#include <Ticker.h>

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
  static void Timing();

private:
  uint8_t pinA_;
  static uint8_t pinB_;
  static uint16_t encoderPosition;
  static uint16_t max_;
  static uint16_t rotationTicker;

  static uint8_t buttonPin_;
  static uint8_t buttonState;
  static uint16_t buttonTicker;
};

#endif
