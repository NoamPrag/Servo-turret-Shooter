#include <Servo.h>
#include <Arduino.h>

class Shooter : Servo
{
private:
    const float releaseAngle;
    const float shootAngle;

public:
    Shooter(const int pin);

    void shoot();
};