// #include "Adafruit_ST7735.h"
// #include <ADS1115.h>
// #include <Adafruit_GFX.h>
// #include <DallasTemperature.h>
// #include "MCP4725.h"
// #include <BH1750.h>
// #include <Losant.h>

// #include <OneWire.h>
#include <arduino.h>
// #include <esp8266WiFi.h>
// #include <spi.h>

// static const uint8_t MISO  = 12;
// static const uint8_t MOSI  = 13;/
// static const uint8_t SCK   = 14;/
// static const uint8_t SS    = 15;

// static const uint8_t SDA = 4;
// static const uint8_t SCL = 5;
//

// #define TFT_CS 15
// #define TFT_RST 0
// #define TFT_DC 2
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
//
// ADS1115 adc(ADS1115_DEFAULT_ADDRESS);
// MCP4725 dac;
// BH1750 lightMeter;

void PinA();
//
// float getVoltage();
// float getCurrent();

const uint8_t pinA = 2;
const uint8_t pinB = 3;
volatile bool Flag = 0;

volatile uint8_t buttonCounter = 0;
volatile uint8_t buttonRange = 0;

// void PinB();
volatile uint16_t encoderPos = 0;
volatile uint8_t reading = 0;
volatile uint16_t time = 0;
#define maxTime 500
void PinA();
void ButtonPin();
uint8_t encoderRange = 20;
// void accel();
//
// uint16_t currentControl = 0;

const uint8_t PGA[] = {0x01, 0x02, 0x03, 0x04, 0x05};
// const char *WIFI_SSID = "WIFI_SSID";
// const char *WIFI_PASS = "WIFI_PASS";
//
// const char *LOSANT_DEVICE_ID = "my-device-id";
// const char *LOSANT_ACCESS_KEY = "my-app-key";
// const char *LOSANT_ACCESS_SECRET = "my-app-secret";
//
// WiFiClient client;
//
// LosantDevice device(LOSANT_DEVICE_ID);
//
// StaticJsonBuffer<100> data;
// JsonObject &state = data.createObject();
//
// void connect() {
//   WiFi.begin(WIFI_SSID, WIFI_PASS);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     // Serial.print(".");
//   }
//   device.connectSecure(client, LOSANT_ACCESS_KEY, LOSANT_ACCESS_SECRET);
//   while (!device.connected()) {
//     delay(500);
//   }
// }
//
// void handleCommand(LosantCommand *command) {
//   // Serial.print("Command received: ");
//   // Serial.println(command->name);
//
//   if (strcmp(command->name, "name") == 0) {
//     // dosomething();
//   }
// }

void setup() {
  // tft.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
  // tft.setTextWrap(0);        // Allow text to run off right edge
  // tft.fillScreen(ST7735_WHITE);
  //
  // tft.setTextColor(ST7735_BLACK);
  // tft.setTextSize(2);
  //
  // tft.setCursor(4, 40);
  // tft.print("V:");
  //
  // tft.setCursor(4, 64);
  // tft.print("I:");
  //
  // tft.setCursor(4, 88);
  // tft.print("P:");
  //
  // tft.setCursor(4, 112);
  // tft.print("R:");
  //
  // tft.setCursor(4, 136);
  // tft.print("L:");
  // Wire.begin();
  // adc.initialize(); // initialize ADS1115 16 bit A/D chip
  // adc.setMode(ADS1115_MODE_SINGLESHOT);
  // adc.setRate(0x00);
  //
  // dac.begin(0x60);
  // lightMeter.begin(BH1750_CONTINUOUS_LOW_RES_MODE);
  //   device.onCommand(&handleCommand);
  //   connect();
  attachInterrupt(12, PinA, RISING);
  attachInterrupt(11, ButtonPin, FALLING);
  // attachInterrupt(0, PinA(), FALLING);
}

void loop() {
  //
  // float Current = getCurrent();
  // float Voltage = getVoltage();

  // lux = lightMeter.readLightLevel();
  // dac.setVoltage(4094, false);

  // tft.setTextColor(ST7735_BLACK);
  // tft.setTextSize(2);
  //
  // tft.fillRect(32, 40, 70, 15, ST7735_WHITE);
  // tft.setCursor(32, 40);
  // tft.print(Voltage, 3);
  //
  // tft.fillRect(32, 64, 70, 15, ST7735_WHITE);
  // tft.setCursor(32, 64);
  // tft.print(Current, 3);

  // tft.fillRect(32, 88, 70, 15, ST7735_WHITE);
  // tft.setCursor(32, 88);
  // tft.print(Voltage * Current);
  //
  // tft.fillRect(32, 112, 70, 15, ST7735_WHITE);
  // tft.setCursor(32, 112);
  // tft.print(Voltage / Current);
  //
  // tft.fillRect(32, 136, 70, 15, ST7735_WHITE);
  // tft.setCursor(32, 136);
  // tft.print(lux);

  // tft.setCursor(0, 32);
  // tft.print("Power: ");
  // tft.print(Voltage * Current);
  // tft.setCursor(0, 48);
  // tft.print("Resistance: ");
  // tft.print(Voltage / Current);
  // tft.setCursor(0, 64);
  // tft.print("Lux: ");
  // tft.print(lux);

  //   device.loop();
  //
  //   state["temperature"] = 1;
  //
  //   StaticJsonBuffer<100> data;
  //   JsonObject &state = data.createObject();
  //   device.sendState(state);
}
//
// float getCurrent() {
//   adc.setGain(PGA[1]);
//   adc.setMultiplexer(0x06);
//   uint16_t I = adc.getConversion(1);
//   uint8_t j = 1;
//   while (1) {
//     if (I < 4096) {
//       j = 4;
//       break;
//     }
//     if (I < 8192) {
//       j = 3;
//       break;
//     }
//     if (I < 16384) {
//       j = 2;
//       break;
//     }
//     break;
//   }
//   adc.setGain(PGA[j]);
//
//   return (adc.getConversion(1) / (8000.00 * pow(2, j)));
// }
//
// float getVoltage() {
//   adc.setGain(PGA[1]);
//   adc.setMultiplexer(0x07);
//   uint16_t V = adc.getConversion(1);
//   uint8_t j = 1;
//   while (1) {
//
//     if (V < 4096) {
//       j = 4;
//       break;
//     }
//     if (V < 8192) {
//       j = 3;
//       break;
//     }
//     if (V < 16384) {
//       j = 2;
//       break;
//     }
//     break;
//   }
//   adc.setGain(PGA[j]);
//
//   return (adc.getConversion(1) / (682.667 * pow(2, j)));
// }

void PinA() {
  cli();
  reading = GPIP(pinB);
  time = timer0_read();
  if (time > maxTime) {
    time = maxTime;
  }
  uint8_t increment = maxTime - (time / maxTime);
  if (!reading && (encoderPos < encoderRange)) {
    encoderPos += increment;
  } else if (reading && (encoderPos > 0))
    encoderPos -= increment;
  sei();
}

void ButtonPin() {
  buttonCounter++;
  if (buttonCounter > buttonRange)
    buttonCounter = 0;
}
