//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
#include <SimpleTimer.h>
#define WIFINETWORKS 3

////////////////////    The BlynkAuth, Wifi Name, and Wifi Password are 
// Blynk Settings //    stored in a separate file and excluded from GitHub
////////////////////    commits to protect my privacy. 
#include "secretSettings.h"
/*
char BlynkAuth[] = yourBlynkAuthKey

*/

///////////////////////
// Hardware Settings //
///////////////////////
#define WS2812_PIN 4 // Pin connected to WS2812 LED
#define BUTTON_PIN 0
#define VIBE_PIN   5
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(1, WS2812_PIN, NEO_GRB + NEO_KHZ800);
SimpleTimer Timer;
int sensorThreshold = 512;
unsigned long timeLimit = 10000;
byte interruptPin = 0;

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

BLYNK_WRITE(V8){
  sensorThreshold = param.asInt() * 1000;
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
  pinMode(VIBE_PIN, OUTPUT); // Vibrator output

  // Initialize Blynk
  Blynk.begin(BlynkAuth, WiFiNetwork[0], WiFiPassword[0]);
  Timer.setInterval(10000L,enforce);
  Timer.setInterval(200L,toggleVibe);
  attachInterrupt(digitalPinToInterrupt(interruptPin), connectWifi, FALLING);
}

void loop()
{
  // Execute Blynk.run() as often as possible during the loop
  Blynk.run(); 
  verify();
  Timer.run();
}

void verify(){
  if(readSensor()){
    digitalWrite(VIBE_PIN, LOW);
    Timer.restartTimer(0);
  };
}

bool readSensor()
{
  if(analogRead(A0) > sensorThreshold){
    return true;
  }
  else{
    return false;
  }
}

void enforce(){
  digitalWrite(VIBE_PIN, HIGH);
  delay(200);
  digitalWrite(VIBE_PIN, LOW);
  delay(100);
}

void toggleVibe(){
  
}

void connectWifi(){
  for(int i=0;i<WIFINETWORKS;i++){
    //Display yellow
    rgb.setPixelColor(0, 0xAAAA00);
    rgb.show();
    
    //Try connecting to a WiFi network
    Blynk.connectWifi(BlynkAuth, WiFiNetwork[i], WiFiPassword[i])
    
    //Try connecting to Blynk server
    Blynk.connect(10);
    
    if(Blynk.connected()){
      //Display green and end the loop
      rgb.setPixelColor(0, 0x00FF00);
      rgb.show();
      break;
    }
    else{
      //Display red and try next wifi network
      rgb.setPixelColor(0, 0xFF0000);
      rgb.show();
    }
  }
}

