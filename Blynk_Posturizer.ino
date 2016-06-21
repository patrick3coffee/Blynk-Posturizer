//#define BLYNK_PRINT Serial    // Comment out debugs to disable prints and save space
//#define BLYNK_DEBUG 1
//#define DEBUG 1
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
#include "Vibrator.h"

////////////////////    The BlynkAuth, Wifi Name, and Wifi Password are 
// Blynk Settings //    stored in a separate file and excluded from GitHub
////////////////////    commits to protect my privacy. 
#include "secretSettings.h"
/*
char BlynkAuth[] = "yourBlynkAuthKey";
char WiFiNetwork[] = "Your WiFi SSID";
char WiFiPassword[] = "YourWiFiPassword";
*/

///////////////////////
// Hardware Settings //
///////////////////////
#define WS2812_PIN 4 // Pin connected to WS2812 LED
#define BUTTON_PIN 0
#define VIBE_PIN   5

Adafruit_NeoPixel rgb = Adafruit_NeoPixel(1, WS2812_PIN, NEO_GRB + NEO_KHZ800);
Vibrator vibe(VIBE_PIN, 200);

unsigned long timeLimit = 10000;
unsigned long lastMuscleActivity;
int sensorReading,threshold;

/*BLYNK_WRITE(V0) // Handle RGB from the zeRGBa
{
  if (param.getLength() < 5)
    return;

  byte red = param[0].asInt();
  byte green = param[1].asInt();
  byte blue = param[2].asInt();

  uint32_t rgbColor = rgb.Color(red, green, blue);
  rgb.setPixelColor(0, rgbColor);
  rgb.show();
}*/

BLYNK_WRITE(V8){
  threshold = param.asInt();
}

BLYNK_WRITE(V9){
  timeLimit = param.asInt() * 1000;
}

void setup()
{
  // Initialize hardware
#ifdef BLYNK_PRINT
  Serial.begin(9600); // Serial
#endif
  
  rgb.begin(); // RGB LED
  
  pinMode(BUTTON_PIN, INPUT); // Button input
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), checkConnection, FALLING);

  // Initialize Blynk
  Blynk.begin(BlynkAuth, WiFiNetwork, WiFiPassword);
}

void loop()
{
  Blynk.run(); 
  vibe.run();
  
  sensorReading = analogRead(A0);
  Blynk.virtualWrite(V10, sensorReading);
  
  if(sensorReading > threshold){
    vibe.enabled(false);
    lastMuscleActivity = millis();
  }
  else if(timeLimitReached()){
    vibe.enabled(true);
  }
}

bool timeLimitReached(){
  if(lastMuscleActivity + timeLimit < millis()){
    return true;
  }
  else{
    return false;
  }
}

void checkConnection(){
#ifdef DEBUG
  Serial.print("checkConnection()");
#endif
  
  if(Blynk.connected()){
    //Display green if connected
    rgb.setPixelColor(0, 0x00FF00);
    rgb.show();
#ifdef DEBUG
    Serial.println(" - connected");
#endif
  }
  else{
    //Display red if not connected
    rgb.setPixelColor(0, 0xFF0000);
    rgb.show();
#ifdef DEBUG
    Serial.println(" - not connected");
#endif
  }
  
  //wait and turn off
  delayMicroseconds(1000000);
  rgb.setPixelColor(0, 0x000000);
  rgb.show();
}

