#include "MyoWareSensor.h"
#include "Arduino.h"

MyoWareSensor::MyoWareSensor(int pin, int initThreshold){
  sensorPin = pin;
  threshold = initThreshold;
#ifdef DEBUG
  Serial.println("instantiated sensor");
#endif
}

bool MyoWareSensor::isAboveThreshold(){
  if(analogRead(sensorPin) > threshold){
    return true;
  }
  else{
    return false;
  }
}

void MyoWareSensor::updateThreshold(int newThreshold){
  threshold = newThreshold;
}

