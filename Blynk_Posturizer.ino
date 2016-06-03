//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

////////////////////
// Blynk Settings //
////////////////////
#include "secretSettings.h"

///////////////////////
// Hardware Settings //
///////////////////////
#define WS2812_PIN 4 // Pin connected to WS2812 LED
#define BUTTON_PIN 0
#define LED_PIN    5
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(1, WS2812_PIN, NEO_GRB + NEO_KHZ800);
int sensorThreshold = 512;
int timeLimit = 10;

BLYNK_WRITE(V0) // Handle RGB from the zeRGBa
{
  if (param.getLength() < 5)
    return;

  byte red = param[0].asInt();
  byte green = param[1].asInt();
  byte blue = param[2].asInt();

  uint32_t rgbColor = rgb.Color(red, green, blue);
  rgb.setPixelColor(0, rgbColor);
  rgb.show();
}

bool checkToggle()
{
  if(digitalRead(12) == HIGH){
    return true;
  }
  else{
    return false;
  }
}

BLYNK_WRITE(V8){
  sensorThreshold = param.asInt();
}

BLYNK_WRITE(V9){
  timeLimit = param.asInt();
}

void setup()
{
  // Initialize hardware
#ifdef BLYNK_DEBUG
  Serial.begin(9600); // Serial
#endif
  rgb.begin(); // RGB LED
  pinMode(BUTTON_PIN, INPUT); // Button input
  pinMode(LED_PIN, OUTPUT); // LED output

  // Initialize Blynk
  Blynk.begin(BlynkAuth, WiFiNetwork, WiFiPassword);
}

void loop()
{
  // Execute Blynk.run() as often as possible during the loop
  Blynk.run(); 
}

