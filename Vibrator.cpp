#include "Vibrator.h"

Vibrator::Vibrator(int pin, unsigned long duration){
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
  if(enable){
    unsigned long currentTime = millis();
    if(timeLimitReached(currentTime)){
      toggleVibe(currentTime);
    }
  }
}

void Vibrator::enabled(bool setting){
  enable = setting;
  digitalWrite(vibePin, setting);
  
}

bool Vibrator::timeLimitReached(unsigned long currentTime){
  if((previousToggle + timerDuration) < currentTime){
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
