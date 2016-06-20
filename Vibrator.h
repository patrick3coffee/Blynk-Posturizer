#include <Arduino.h>

class Vibrator{
public:
  //constructor
  Vibrator(int pin, int duration);

  // if enabled check elapsed time and toggle vibrator
  void run();

  //enable or disable vibrator
  void enable();
  void disable();
  
private:
  bool enabled;
  int vibePin;
  unsigned long timerStart, previousToggle, timerDuration;
  
  void toggleVibe(unsigned long currentTime);
  bool checkElapsedTime(unsigned long currentTime);
};

