#include <Servo.h>
#include <Arduino.h>

class Shooter : Servo
{
private:
    static const float releaseAngle;
    static const float shootAngle;

public:
    Shooter(const int pin);

    void shoot();
};