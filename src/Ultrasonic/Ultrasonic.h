#include <Arduino.h>

class Ultrasonic
{
private:
    void pulse(const int microseconds);
    float microsecondsToCM(const long microseconds);

public:
    float getDistance();
};