#include <Servo.h>
#include <Arduino.h>

class Shooter : Servo
{
private:
    const float releaseAngle;
    const float shootAngle;

public:
    explicit Shooter(const unsigned int pin);

    void reset();

    void shoot();
};