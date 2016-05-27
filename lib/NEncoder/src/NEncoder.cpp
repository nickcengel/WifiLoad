

#include "NEncoder.h"
#include <Ticker.h>
#include <arduino.h>

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
  ticker.attach_ms(5, Timing);
};

uint16_t NEncoder::position() { return encoderPosition; };

void NEncoder::clearPosition() { encoderPosition = 0; };
void NEncoder::setRange(uint16_t max) { max_ = max; };

void NEncoder::rotateRoutine() {
  bool direction = GPIP(pinB_);
  uint8_t step = 0;
  uint16_t ticks = rotationTicker;
  if (rotationTicker > 3)
    step = 1 + 200 * exp(-.2 * rotationTicker);

  if (!direction && (encoderPosition <= (max_ - step))) {
    encoderPosition += step;
    rotationTicker = 0;
  } else if (direction && (encoderPosition >= step)) {
    encoderPosition -= step;
    rotationTicker = 0;
  }
};

uint8_t NEncoder::buttonPin_;
uint16_t NEncoder::buttonTicker;
uint8_t NEncoder::buttonState;

void NEncoder::buttonRoutine() {

  bool click = GPIP(buttonPin_);
  uint16_t ticks = buttonTicker;

  if (!click && (buttonState == ACKNOWLEDGED)) { // finger's on the button
    buttonTicker = 0;                            // restart the button timer
    buttonState = CLICKED; // set a flag to wait for button release
  } else if (click && (buttonState == CLICKED)) { // button has been released
    if (ticks > 16 && ticks < 125)                // one short click
      buttonState = ONECLICK;
    else if (buttonTicker < 500 && buttonTicker > 150) // took a while
      buttonState = LONGCLICK;
  }
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
