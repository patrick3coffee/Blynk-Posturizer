#include <Arduino.h>

class Vibrator{
public:
  //constructor
  Vibrator(int pin, unsigned long duration);

  // if enabled check elapsed time and toggle vibrator
  void run();

  //enable or disable vibrator
  void enabled(bool setting);
  
private:
  bool enable;
  int vibePin;
  unsigned long timerStart, previousToggle, timerDuration;
  
  void toggleVibe(unsigned long currentTime);
  bool timeLimitReached(unsigned long currentTime);
};

