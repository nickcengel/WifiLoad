/*
  motr.h - Library for controlling DC motors
*/
#ifndef EncoderCode_h
#define EncoderCode_h

#include <Ticker.h>
#include <arduino.h>

const uint8_t pinA = 12; // Encoder A and B pins
const uint8_t pinB = 13;
const uint8_t encoderButtonPin = 11;

volatile uint16_t encoderPos = 0;     // stores current value of encoder
volatile uint16_t encoderRange = 256; // max value, min is zer
volatile uint16_t encoderTime = 0;    // stores elapsed time between movements
const uint16_t maxTime = 100; // max time we're interested in (in 5's of ms)
Ticker Rticker;               // 'Ticker' object for encoder switch time

/// Encoder Button
volatile uint8_t buttonCounter = 0; // how many times the button's been pressed
volatile uint8_t maxClicks = 5;
volatile uint8_t buttonTime = 0; // elapsed time between press and release
volatile bool doubleClick = 0;   // Flag to track double clicks
Ticker Bticker;                  // 'Ticker' object for button hold time

void encoderButton() {
  cli();
  if (!GPIP(encoderButtonPin)) // if pin is Low, interrupt was triggered by fall
    buttonTime = 0;            // restart the button timer and leave
  else if (buttonTime) {       // pin is high, check to see some time has passed
    if (buttonTime > 250)      // time > 2.5s
      buttonCounter = 255;     // set 255, code for button hold
    else if (buttonTime > 75 && buttonTime < 150) { // single click timing
      if (buttonCounter < maxClicks)
        buttonCounter++; // increment or reset
      else
        buttonCounter = 0;
    }

    else if (buttonTime < 75) { // if was shorter...
      if (doubleClick) {     // and we already recorded half of a double click
        buttonCounter = 128; // set 128, code for double click
        doubleClick = 0;     // clear double click flag
      } else                 // this is the first half of double click
        doubleClick = 1;     // set double click flag
    }
  }
  sei();
}
void buttonTiming() {
  if (buttonTime < 255)
    buttonTime++;
}

void encoderA() {               // Call on rising pinA
  cli();                        // Clear interrupts
  uint8_t reading = GPIP(pinB); // check pinB state

  uint8_t increment =
      maxTime - (encoderTime / maxTime); // make increment prop. to time
  if (!reading &&
      (encoderPos <
       encoderRange)) {      // B is low when A rises, encoder is below max
    encoderPos += increment; //  CW
    encoderTime = 0;
  } else if (reading &&
             (encoderPos >
              0)) { // B is high when A rises, encoderpos greater than 0
    encoderPos -= increment; // CCW
    encoderTime = 0;
  }
  sei(); // set interrupts
}

void encoderTiming() { // increment encoderTime until it reaches maxTime
  if (encoderTime < maxTime)
    encoderTime++;
}

void setupEncoder() {
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(encoderButtonPin, INPUT);

  attachInterrupt(pinA, encoderA, RISING); // Call PinA when pinA rises
  Rticker.attach_ms(5, encoderTiming);     // Call 'EncoderTiming' every 5ms

  attachInterrupt(encoderButtonPin, encoderButton,
                  CHANGE); // Call encoderButton on EncoderbuttonPin change
  Bticker.attach_ms(10, buttonTiming); // Call buttonTiming every 10ms
}
#endif
