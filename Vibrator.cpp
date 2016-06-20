#include "Vibrator.h"

Vibrator::Vibrator(int pin, int duration){
  timerDuration = duration;
  
  // set Vibrator output
  vibePin = pin;
  pinMode(pin, OUTPUT); 
  
#ifdef DEBUG
  Serial.print("instantiated sensor on pin: ");
  Serial.println(pin);
#endif
}

void Vibrator::run(){
  if(enabled){
    unsigned long currentTime = millis();
    if(checkElapsedTime(currentTime)){
      toggleVibe(currentTime);
    }
  }
}

void Vibrator::enable(){
  enabled = true;
  digitalWrite(vibePin, HIGH);
  
}

void Vibrator::disable(){
  enabled = false;
  digitalWrite(vibePin, LOW);
  
}

bool Vibrator::checkElapsedTime(unsigned long currentTime){
  if((currentTime - previousToggle) > timerDuration){
    return true;
  }
  else{
    return false;
  }
}

void Vibrator::toggleVibe(unsigned long currentTime){
  byte toggle = !digitalRead(vibePin);
  digitalWrite(vibePin, toggle);
  previousToggle = currentTime;
}
