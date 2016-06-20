class MyoWareSensor{
public:
  MyoWareSensor(int pin, int initThreshold);
  bool isAboveThreshold();
  void updateThreshold(int newThreshold);
private:
  int sensorPin, threshold;
};

