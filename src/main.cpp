
// HEADERS
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "MCP4725.h"
#include <ADS1115.h>
#include <Arduino.h>
#include <BH1750.h>
#include <DallasTemperature.h>
#include <NEncoder.h>
#include <OneWire.h>
#include <Ticker.h>

// OLED I2C DISPLAY
#define SSD1306_128_64 // 128x64 Pixel Display
Adafruit_SSD1306 display(1);

// ENCODER DECLARATIONS
const uint8_t pinA = 12;              // encoder pin A
const uint8_t pinB = 13;              // encoder pin B
const uint8_t buttonPin = 14;         // encoder button pin
static uint16_t encoderRangeA = 4095; // maximum encoder value, can be changed
//// INSTANCE
NEncoder encoder(pinA, pinB, buttonPin);
//// GLOBAL ENCODER METHODS
void rotationHandler() { encoder.rotateRoutine(); }
void buttonHandler() { encoder.buttonRoutine(); }
void encoderSetup() {
  encoder.init(encoderRangeA);
  attachInterrupt(pinA, rotationHandler, RISING);
  attachInterrupt(buttonPin, buttonHandler, CHANGE);
}
static uint16_t oPosiition = 0; // the encoder's  previous position

// ANALOG OUT
MCP4725 dac;

// LUX
BH1750 lightMeter;

// 1- WIRE and TEMPERATURE
#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

// ADC
ADS1115 adc(ADS1115_DEFAULT_ADDRESS);
const uint8_t PGA[] = {0x01, 0x02, 0x03, 0x04, 0x05};
const uint8_t alertReadyPin = 10;
float getVoltage();
float getCurrent();
void pollAlertReadyPin();

/////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200); // For debugging

  // ENCODER
  encoder.init(encoderRangeA);
  attachInterrupt(pinA, rotationHandler, RISING);
  attachInterrupt(buttonPin, buttonHandler, CHANGE);

  // I2C
  Wire.begin();

  // ADC
  adc.initialize();
  adc.setMode(ADS1115_MODE_SINGLESHOT);
  adc.setRate(0x04);
  pinMode(alertReadyPin, INPUT_PULLUP);
  adc.setConversionReadyPinMode();

  // DAC
  dac.begin(0x60);

  // LUX
  lightMeter.begin(BH1750_CONTINUOUS_LOW_RES_MODE);

  // DISPLAY
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // TEMPERATURE
  sensors.begin();
  oneWire.reset_search();
  oneWire.search(insideThermometer);
  sensors.setResolution(insideThermometer, 12);
}

void loop() {
  //// encoder testing routine
  //   uint16_t g = encoder.position();
  //   if (g != oldg)
  //     Serial.println(g);
  //   oldg = g;
  //   uint8_t butt = encoder.button();
  //   if (butt) {
  //     Serial.println(butt);
  //     if (butt == 2) {
  //       encoder.clearPosition();
  //       oldg = 0;
  //     }
  //   }
  //   cli();
  //   int r = random(1, 300);
  //   delay(r);
  //   sei();

  switch (int page = 4) {
  case 0:
    break;

  case 1:
    break;

  case 4:
    break;
  }
}

// ADC RANGE and MEASUREMENT
float getCurrent() {
  adc.setGain(PGA[0]);
  adc.setMultiplexer(0x05);
  adc.triggerConversion();
  pollAlertReadyPin();
  uint16_t I = adc.getConversion(0);
  uint8_t j = 0;
  while (1) {
    if (I < 2048) {
      j = 4;
      break;
    }
    if (I < 4096) {
      j = 3;
      break;
    }
    if (I < 8192) {
      j = 2;
      break;
    }
    if (I < 16384) {
      j = 1;
      break;
    }
    break;
  }
  adc.setGain(PGA[j]);
  adc.triggerConversion();
  pollAlertReadyPin();
  return (adc.getConversion(0) / (16000 * pow(2, j)));
}
float getVoltage() {
  adc.setGain(PGA[0]);
  adc.setMultiplexer(0x04);
  adc.triggerConversion();
  pollAlertReadyPin();
  uint16_t I = adc.getConversion(0);
  uint8_t j = 0;
  while (1) {
    if (I < 2048) {
      j = 4;
      break;
    }
    if (I < 4096) {
      j = 3;
      break;
    }
    if (I < 8192) {
      j = 2;
      break;
    }
    if (I < 16384) {
      j = 1;
      break;
    }
    break;
  }
  adc.setGain(PGA[j]);
  adc.triggerConversion();
  pollAlertReadyPin();
  return (adc.getConversion(0) / (1333.33 * pow(2, j)));
}
void pollAlertReadyPin() {
  for (uint16_t i = 0; i < 10000; i++)
    if (!digitalRead(alertReadyPin))
      return;
}
