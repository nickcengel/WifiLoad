

#include "NEncoder.h"
#include <arduino.h>
#include <ticker.h>

Ticker ticker;
NEncoder::NEncoder(uint8_t pinA, uint8_t pinB, uint8_t buttonPin) {
  pinA_ = pinA;
  pinB_ = pinB;
  buttonPin_ = buttonPin;
};
uint8_t NEncoder::pinB_;
uint16_t NEncoder::encoderPosition;
uint16_t NEncoder::max_;
uint16_t NEncoder::rotationTicker;

void NEncoder::init(uint16_t max) {
  pinMode(pinA_, INPUT_PULLUP);
  pinMode(pinB_, INPUT_PULLUP);
  max_ = max;
  pinMode(buttonPin_, INPUT_PULLUP);
  ticker.attach_ms(10, Timing);
};

uint16_t NEncoder::position() { return encoderPosition; };

void NEncoder::clearPosition() { encoderPosition = 0; };
void NEncoder::setRange(uint16_t max) { max_ = max; };

void NEncoder::rotateRoutine() {
  cli();
  bool direction = GPIP(pinB_);
  uint16_t ticks = rotationTicker;
  uint8_t step = 0;
  if (ticks > 500)
    step = 1;
  else if ((ticks < 500) && (ticks > 50))
    step = 10;
  else if ((ticks < 50) && (ticks > 1))
    step = 100;
  if (!direction && (encoderPosition <= (max_ - step))) {
    encoderPosition += step;
    rotationTicker = 0;
  } else if (direction && (encoderPosition >= step)) {
    encoderPosition -= step;
    rotationTicker = 0;
  }
  sei();
};

uint8_t NEncoder::buttonPin_;
uint16_t NEncoder::buttonTicker;
uint8_t NEncoder::buttonState;

void NEncoder::buttonRoutine() {
  cli();
  bool click = GPIP(buttonPin_);
  if (!click && (buttonState == ACKNOWLEDGED)) { // finger's on the button
    buttonTicker = 0;                            // restart the button timer
    buttonState = CLICKED; // set a flag to wait for button release
  } else if (click && (buttonState == CLICKED)) { // button has been released
    if (buttonTicker < 10)                        // one short click
      buttonState = ONECLICK;
    else if (buttonTicker > 100) // took a while
      buttonState = LONGCLICK;
  }
  sei();
};

uint8_t NEncoder::button() {
  if (buttonState != CLICKED) {  // we're not still waiting on the button
    uint8_t state = buttonState; // so pass along the new button state
    buttonState = ACKNOWLEDGED;  // and we're done
    return state;
  } else
    return 0; // still waiting on the button
};

void NEncoder::Timing() {
  rotationTicker++;
  if (rotationTicker > 4094)
    rotationTicker = 4094;

  buttonTicker++;               // increment the button timer
  if (buttonTicker > 4094) {    // make sure it doesn't overflow
    if (buttonState == CLICKED) // we're still waiting on the button
      buttonTicker = 4094;      // so don't zero
    else
      buttonTicker = 0; // otherwise, reset an idle counter
  }
};
